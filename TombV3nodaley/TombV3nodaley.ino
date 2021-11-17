//This sketch provides an example of a simple system of 6 digital inputs for PIRs and 1 channel for envirnomental light.
//This data is sent every 10seconds across a serial (USB) connection, as a comma-separated string of values.
// The sketch is written longhand, in an attempt to improve clarity.  Use of arrays for values and counters to improve brevity and flexibility:
// http://arduino.cc/en/Reference/For  for details on arrays  and  
// http://arduino.cc/en/Reference/While  for other timing options
#include <SPI.h>
#include <SparkFunDS3234RTC.h>

// Comment out the line below if you want date printed before month.
// E.g. October 31, 2016: 10/31/16 vs. 31/10/16
#define PRINT_USA_DATE

//////////////////////////////////
// Configurable Pin Definitions //
//////////////////////////////////
#define DS13074_CS_PIN 8 // DeadOn RTC Chip-select pin
//#define INTERRUPT_PIN 2 // DeadOn RTC SQW/interrupt pin (optional)


#define WHITELED 10  // LED White
#define REDLED 9  // LED REd
#define PIR1 2
#define LDR1 A0
#define PIR2 3
#define LDR2 A1
#define PIR3 4
#define LDR3 A2
#define PIR4 5
#define LDR4 A3
#define PIR5 6
#define LDR5 A4
#define PIR6 7
#define LDR6 A5

// Tomb number. Make sure to enter the correct tomb number before programing the MCU
int TOMB = 1;

// Military Hour Used 00:00 - 23:59
// SET up variables:
long HourWHITEON = 0;  // hour where White LED will be ON
long MinuteWHITEON = 0; //minute where White LED will be ON
long HourREDON = 0;     //hour where Red LED will be ON
long MinuteREDON = 0;   //minute where Red LED will be ON
long SecREDON = 0;
long SecWHITEON =30;
 
int RintensityHIGH=255; // REDLED PWM duty cycle change 100% = 255 and 0 = OFF
int RintensityLOW=0;
int WintensityHIGH=255; // WHITELED PWM duty cycle change 100% = 255 and 0 = OFF
int WintensityLOW=0;



//Don't change any of these variables below:
const char deviceCALLID[16] ={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};

const char deviceSendID[16] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};


//(sec,min,hour,weekday,day,month,year)
int RTC[7] ={0,0,0,1,1,1,2000};

char recvchars[32];
boolean newdata=false;
int p=0;
static int parameters[65];
int ASize=736;                   //Size of LED configuration array
static int LEDparameters[736];  //LED configuration array
int LEDvalues =0; //just a flag
int PIRCounter1 = 0;  //acitivty counter for PIR1
int PIRCounter2 = 0;  //acitivty counter for PIR2
int PIRCounter3 = 0;  //acitivty counter for PIR3
int PIRCounter4 = 0;  //acitivty counter for PIR4
int PIRCounter5 = 0;  //acitivty counter for PIR5
int PIRCounter6 = 0;  //acitivty counter for PIR6
int LoopCounter = 0; //loopcounter for activity

int WHITEREDDAY = 1;  // 1 if White will be ON during the day. example from 7 to 20
                      // 0 if RED will be ON during the day. 
  /* In other words if the WHITE LED will be ON during the Night, crossing the 
     midnight(12am of 24 in military time) to 1am please change the WHITEREDDAY variable to 0. 
    
     The same for the RED LED. IF RED LED will be ON during the the crossing time from 
     midnight(12 am or 24 in military time) to 1 am plaese change the WHITEREDDAY variable to 1. 
*/
//don't change this
long secREDON = (((HourREDON*60) + MinuteREDON)*60) + SecREDON;
long secWHITEON = (((HourWHITEON*60) + MinuteWHITEON)*60) + SecWHITEON;
long minuteflag = 1;   // if variable MinuteREDON>0 && MinuteWHITEON>0 minuteflag is 1
long secondsflag = 1;   // if variable SecREDON>0 && SecWHITEON>0secondflag is 1
long hoursflag = 1;   // if variable HourREDON>0 && HourWHITEON>0 hoursflag is 1

void setup() {
  
  if ((HourREDON==0) && (HourWHITEON==0)){
    hoursflag = 0;
  }
  else{
    hoursflag = 1;
  }

  
  if ((MinuteREDON==0) && (MinuteWHITEON==0)){
    minuteflag = 0;
  }
  else{
    minuteflag = 1;
  }


  if ((SecREDON==0) && (SecWHITEON==0)){
    secondsflag = 0;
  }
  else{
    secondsflag = 1;
  }
  
  if(secWHITEON > secREDON){
    WHITEREDDAY = 0;
  }
  else{
    WHITEREDDAY = 1;
  }
  Serial.begin(57600);
  rtc.begin(DS13074_CS_PIN);
  pinMode(WHITELED,OUTPUT); //PIN 10
  pinMode(REDLED,OUTPUT); //PIN 11
  
  pinMode(LDR1,INPUT);
  pinMode(LDR2,INPUT);
  pinMode(LDR3,INPUT);
  pinMode(LDR4,INPUT);
  pinMode(LDR5,INPUT);
  pinMode(LDR6,INPUT);
  
  pinMode(PIR1,INPUT);
  pinMode(PIR2,INPUT);
  pinMode(PIR3,INPUT);
  pinMode(PIR4,INPUT);
  pinMode(PIR5,INPUT);
  pinMode(PIR6,INPUT);
  
  analogWrite(REDLED,LOW);
  analogWrite(WHITELED,LOW);
  
  
  //rtc.autoTime();
  // Or you can use the rtc.setTime(s, m, h, day, date, month, year)
  // function to explicitly set the time:
  // e.g. 7:32:16 | Monday October 31, 2016:
  //(sec,min,hour,weekday,day,month,year)
  //<0,45,5,5,16,9,21>
  //rtc.setTime(0, 36, 12, 3, 13, 7, 21);  // Uncomment to manually set time
  // give time for startup
  //delay(1000);
  // provide data labels for serial monitor on the computer, separated by commas. commented out as this is better included in Processing sketch
  //Serial.println("Time,ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR");

 
}

// This next section is the one that runs in a loop constantly, taking readings every tenth of a second 


void loop() {
LEDcontrol();
if(Serial.available()){
  char value=Serial.read();
  if(value == deviceCALLID[TOMB-1]){
    //send HEADER indicating data follows
      String dev = String(deviceSendID[TOMB-1]);
      Serial.print(dev);
      Serial.print(",");
      //Serial.print('\n');
      //printTime();
    // separate with a comma
      //Serial.print(",");
    // send total activity for PIR counters, separated by commas
      Serial.print(digitalRead(PIR1));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(digitalRead(PIR2));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(digitalRead(PIR3));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(digitalRead(PIR4));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(digitalRead(PIR5));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(digitalRead(PIR6));
      Serial.print(",");
      //Serial.print('\n');
   // read Light-dependant resistor (LDR) connected to analog pin 2 and send resulting number
      Serial.print(analogRead(LDR1));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(analogRead(LDR2));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(analogRead(LDR3));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(analogRead(LDR4));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(analogRead(LDR5));
      Serial.print(",");
      //Serial.print('\n');
      Serial.print(analogRead(LDR6));
      Serial.print('\n'); // new line (linefeed) character 
  }
  if(value =='W'){
      for(int x=0; x<ASize; x++){
       Serial.println(LEDparameters[x]);
      }
  }
  if(value == 'T'){
    //delay(100);
    //Serial.println("change rtc time");
    //delay(100);
    //Serial.println(" ");
    //clearparameters();
    recvdata();
    
    //(sec,min,hour,weekday,day,month,year)
  rtc.setTime(parameters[0], parameters[1], parameters[2], parameters[3]+1, parameters[4], parameters[5], parameters[6]);  // Uncomment to manually set time
//  delay(200*TOMB);
//      Serial.print("tomb "); 
//      Serial.print(TOMB);
//      Serial.print(" rtc time: ");
//      Serial.print('\n');
//      printTime();
//      Serial.print('\n');
      clearparameters();
  }

  if(value == 'Z'){
   while(LEDvalues==0){
    if(Serial.available()){
     char value=Serial.read();
     if (value =='X'){
      LEDvalues=1;
     }
     if(value == deviceCALLID[TOMB-1]){
//       delay(10);
//       Serial.print("change led time in tomb ");
//       Serial.println(TOMB);
       clearLEDparameters();
       LEDrecvdata();
//       HourWHITEON = parameters[0];  // hour where White LED will be ON
//       MinuteWHITEON = parameters[1]; //minute where White LED will be ON
//       SecWHITEON =parameters[2];
//       HourREDON = parameters[3];     //hour where Red LED will be ON
//       MinuteREDON = parameters[4];   //minute where Red LED will be ON
//       SecREDON = parameters[5];
//       /*
//       RintensityHIGH = parameters[6]; // REDLED PWM duty cycle change 100% = 255 and 0 = OFF
//       RintensityLOW = parameters[7];
//       WintensityHIGH = parameters[8]; // WHITELED PWM duty cycle change 100% = 255 and 0 = OFF
//       WintensityLOW = parameters[9];
//       */
//       secREDON = HourREDON*60*60 + MinuteREDON*60 + SecREDON;
//       secWHITEON = HourWHITEON*60*60 + MinuteWHITEON*60 + SecWHITEON;
        /*
 Serial.println(secREDON);
 Serial.println(secWHITEON);
 */
       //clearparameters();
       
       LEDvalues=1;
       /*
        if ((HourREDON==0) && (HourWHITEON==0)){
          hoursflag = 0;
        }
        else{
          hoursflag = 1;
        }
      
        
        if ((MinuteREDON==0) && (MinuteWHITEON==0)){
          minuteflag = 0;
        }
        else{
          minuteflag = 1;
        }
      
      
        if ((SecREDON==0) && (SecWHITEON==0)){
          secondsflag = 0;
        }
        else{
          secondsflag = 1;
        }

       
       if(secWHITEON > secREDON){
         WHITEREDDAY = 0;
       }
       else{
        WHITEREDDAY = 1;
       }
       /*
       Serial.print("WHITEREDDAY: ");
       Serial.println(WHITEREDDAY);
       Serial.print("secWHITEON: ");
       Serial.println(secWHITEON);
       Serial.print("secREDON: ");
       Serial.println(secREDON);
       */
      }
     }
    }
    LEDvalues=0;
  }
 }
//LEDcontrol();     
}

void LEDcontrol(){
  // Call rtc.update() to update all rtc.seconds(), rtc.minutes(),
  // etc. return functions.
  
  rtc.update();
  /*
  Serial.print("rtc.hour(): ");
  Serial.println(rtc.hour());
  Serial.print("rtc.minute(): ");
  Serial.println(rtc.minute());
  Serial.print("rtc.second(): ");
  Serial.println(rtc.second());
  */
  long TimeSec = long(rtc.hour())*60*60*hoursflag + long(rtc.minute())*60*minuteflag + long(rtc.second())*secondsflag;
  /*
  Serial.print("TimeSec: ");
  Serial.println(TimeSec);
  Serial.print("WHITEREDDAY: ");
  Serial.println(WHITEREDDAY);
  Serial.print("secWHITEON: ");
  Serial.println(secWHITEON);
  Serial.print("secREDON: ");
  Serial.println(secREDON);
 */
  
 if(WHITEREDDAY == 1){
  if (TimeSec>=secWHITEON && TimeSec<secREDON){  //whiteON
    analogWrite(REDLED,RintensityLOW);
    analogWrite(WHITELED,WintensityHIGH);
    //digitalWrite(13,LOW);
  }
  else{  // REDON
    analogWrite(REDLED,RintensityHIGH);
    analogWrite(WHITELED,WintensityLOW);
    //digitalWrite(13,HIGH);
  }
 }

 if(WHITEREDDAY == 0){
  if (TimeSec>=secREDON && TimeSec<secWHITEON){  //REDON
    analogWrite(REDLED,RintensityHIGH);
    analogWrite(WHITELED,WintensityLOW);
    //digitalWrite(13,HIGH);
  }
  else{  // WhiteON
    
    analogWrite(REDLED,RintensityLOW);
    analogWrite(WHITELED,WintensityHIGH);
    //digitalWrite(13,LOW);
  }
 }
}

void printTime()
{
  rtc.update();
  Serial.print("(");
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10)
    Serial.print('0'); // Print leading '0' for minute
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10)
    Serial.print('0'); // Print leading '0' for second
  Serial.print(String(rtc.second())); // Print second
  
  Serial.print("|");

  // Few options for printing the day, pick one:
  Serial.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
  Serial.print("-");
#ifdef PRINT_USA_DATE
  Serial.print(String(rtc.month()) + "/" +   // Print month
                 String(rtc.date()) + "/");  // Print date
#else
  Serial.print(String(rtc.date()) + "/" +    // (or) print date
                 String(rtc.month()) + "/"); // Print month
#endif
  Serial.print(String(rtc.year()));        // Print year
  Serial.print(")");
  Serial.print('\n');     
}
