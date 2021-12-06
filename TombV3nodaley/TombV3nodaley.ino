// <MH> Add the header
//This sketch provides an example of a simple system of 6 digital inputs for PIRs and 6 channel for environmental light LDR.
#include <SPI.h>
#include <SparkFunDS3234RTC.h>

//////////////////////////////////
// Configurable Pin Definitions //
//////////////////////////////////
#define DS13074_CS_PIN 8 // DeadOn RTC Chip-select pin

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

// **** This line used only in PGM mode, index to assign the letter to the tomb in 
// the array below called deviceCALLID[] 
// Tomb number. Make sure to enter the correct tomb number before programing the MCU
int TOMB = 2;

//Don't change any of these variables below

// Military Hour Used 00:00 - 23:59
// init variables for the RTC
int Day = 0;
int Month = 0;
int Year = 0;
int Hour = 0;
int Minute = 0;
int Sec = 0;
int RtcDay = 0;
int DayS = 0;

//*** Variables to compare time from files and RTC
// Limit is Feb 07 2106 --> 32bit u_long value
unsigned long LEDUnix = 0;
unsigned long RTCUnix = 0;

// Red LED intensity values 
// White LED intensity values  
int Rintensity=0; // REDLED PWM duty cycle change 100% = 255 and 0 = OFF
int Wintensity=0;

short NextLEDConfiflag = 0; // flag if 1 the LED time variables are going to be updated with the next 8 variables
short IFLEDParameterReceived = 0; //flag  1 if after LED parameters are received for the first time.
short laspara=0; // flag to know if last parameter was made 

// Python tomb name calling for PIR and LDR values in that particular instant
const char deviceCALLID[16] ={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};

// Python tomb name to respond back to the python query for a given tomb in a particular instant 
const char deviceSendID[16] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};

String dev = String(deviceSendID[TOMB-1]);

char recvchars[32];
boolean newdata=false;
int p=0;

#define BSize 7  //RTC update array size parameters
#define ASize 456 //Size in bytes of the LED configuration array

static int parameters[BSize];  // RTC parameter array
static int LEDparameters[ASize];  //LED configuration array

int LEDpointer = 0; // Index to point to LED config text items for LEDparameters[ASize]
int LEDvalues = 0; // Flag to indicate the receipt of the values

void setup() {
  Serial.begin(57600); // Verify speed with the worst case: 16 tombs and comm with the last one

  // verify the RTC is alive
  rtc.begin(DS13074_CS_PIN);

  //Define pin status
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
  
  // <MH> This where we left of the Code Review 
  // Check if the Arduino tomb received parameters
  if (IFLEDParameterReceived == 1){
    LEDcontrol();
  }
if(Serial.available()){
  char value=Serial.read();
  if(value == deviceCALLID[TOMB-1]){
    //send HEADER indicating data follows
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
  
  //just for throubleshooting. this if can be eliminated later
  if(value =='W'){
      delay(500*TOMB);
      Serial.print(dev);
      printTime();

      rtc.update();
     RtcDay = (unsigned long)rtc.date();
     RtcDay += (rtc.year()+2000-1970)*365.2422;    
    if((rtc.year() % 4)==0){
     RtcDay += 1;
    }
    if(rtc.month()==2){
     RtcDay += 31;
    }
    if(rtc.month()==3){
     RtcDay += 59 ;
    }
    if(rtc.month()==4){
     RtcDay += 90;
    }
    if(rtc.month()==5){
     RtcDay += 120;
    }
    if(rtc.month()==6){
     RtcDay += 151;
    }
    if(rtc.month()==7){
     RtcDay += 181;
    }
    if(rtc.month()==8){
     RtcDay += 212;
    }
    if(rtc.month()==9){
     RtcDay += 243;
    }
    if(rtc.month()==10){
     RtcDay += 273;
    }
    if(rtc.month()==11){
     RtcDay += 304;
    }
    if(rtc.month()==12){
     RtcDay += 334;
    }  
    RTCUnix = (unsigned long)RtcDay*86400 + (unsigned long)rtc.hour()*3600 + (unsigned long)rtc.minute()*60 + (unsigned long)rtc.second();

      
      Serial.print("rtcunix:");
      Serial.println(RTCUnix);
      Serial.print("ledunix:");
      Serial.println(LEDUnix);
      Serial.print("ledpointer:");
      Serial.println(LEDpointer);
      Serial.print("day:");
      Serial.println(Day);
      Serial.print("month:");
      Serial.println(Month);
      Serial.print("year:");
      Serial.println(Year);
      Serial.print("hour:");
      Serial.println(Hour);
      Serial.print("minute:");
      Serial.println(Minute);
      Serial.print("sec:");
      Serial.println(Sec);
      Serial.print("wintensity:");
      Serial.println(Wintensity);
      Serial.print("rintensity:");
      Serial.println(Rintensity);
      Serial.print("lastparameter?:");
      Serial.println(laspara);
      
  }
  
  if(value == 'T'){
    //delay(100);
    //Serial.println("change rtc time");
    //delay(100);
    //Serial.println(" ");
    //clearparameters();
    recvdata();
    
    //(sec,min,hour,weekday,day,month,year)
  rtc.setTime(parameters[0], parameters[1], parameters[2], parameters[3]+1, parameters[4], parameters[5], parameters[6]); 
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
       clearLEDparameters();
       LEDrecvdata();
       LEDpointer = 0;
       Day = LEDparameters[LEDpointer];
       Month = LEDparameters[++LEDpointer];
       Year = LEDparameters[++LEDpointer];
       Hour = LEDparameters[++LEDpointer];  
       Minute = LEDparameters[++LEDpointer]; 
       Sec = LEDparameters[++LEDpointer];
       Wintensity = LEDparameters[++LEDpointer];
       Rintensity = LEDparameters[++LEDpointer];
       DayS=Day;
       DayS += (Year-1970)*365.2422;     
      if((Year % 4)==0){
        DayS += 1;
      }
      if(Month==2){
      DayS += 31;
      }
      if(Month==3){
      DayS += 59 ;
      }
      if(Month==4){
      DayS += 90;
      }
      if(Month==5){
      DayS += 120;
      }
      if(Month==6){
      DayS += 151;
      }
      if(Month==7){
      DayS += 181;
      }
      if(Month==8){
      DayS += 212;
      }
      if(Month==9){
      DayS += 243;
      }
      if(Month==10){
      DayS += 273;
      }
      if(Month==11){
      DayS += 304;
      }
      if(Month==12){
      DayS += 334;
      }
      
       LEDUnix = (unsigned long)DayS*86400 + (unsigned long)Hour*3600 +(unsigned long)Minute*60 + (unsigned long)Sec ;
       IFLEDParameterReceived = 1;
       laspara=0;
       
       LEDvalues=1; 
      }
     }
    }
    LEDvalues=0;
  }
 }     
}


void LEDcontrol(){
  // Call rtc.update() to update all rtc.seconds(), rtc.minutes(),
  // etc. return functions.
  
  rtc.update();
   RtcDay = (unsigned long)rtc.date();
   RtcDay += (rtc.year()+2000-1970)*365.2422;    
  if((rtc.year() % 4)==0){
   RtcDay += 1;
  }
  if(rtc.month()==2){
   RtcDay += 31;
  }
  if(rtc.month()==3){
   RtcDay += 59 ;
  }
  if(rtc.month()==4){
   RtcDay += 90;
  }
  if(rtc.month()==5){
   RtcDay += 120;
  }
  if(rtc.month()==6){
   RtcDay += 151;
  }
  if(rtc.month()==7){
   RtcDay += 181;
  }
  if(rtc.month()==8){
   RtcDay += 212;
  }
  if(rtc.month()==9){
   RtcDay += 243;
  }
  if(rtc.month()==10){
   RtcDay += 273;
  }
  if(rtc.month()==11){
   RtcDay += 304;
  }
  if(rtc.month()==12){
   RtcDay += 334;
  }  
  RTCUnix = (unsigned long)RtcDay*86400 + (unsigned long)rtc.hour()*3600 + (unsigned long)rtc.minute()*60 + (unsigned long)rtc.second();
  

  if (RTCUnix>=LEDUnix){  
    analogWrite(REDLED,Rintensity);
    analogWrite(WHITELED,Wintensity);
    NextLEDConfiflag=1;
  }

  if(NextLEDConfiflag==1){
      if(LEDparameters[++LEDpointer]==32){
        //end of array
        // setting LED to 0
        analogWrite(REDLED,0);
        analogWrite(WHITELED,0);
        IFLEDParameterReceived = 0;
        laspara=1;
        goto Last;
      }
       Day = LEDparameters[LEDpointer];
       Month = LEDparameters[++LEDpointer];
       Year = LEDparameters[++LEDpointer];
       Hour = LEDparameters[++LEDpointer];  
       Minute = LEDparameters[++LEDpointer]; 
       Sec = LEDparameters[++LEDpointer];
       Wintensity = LEDparameters[++LEDpointer];
       Rintensity = LEDparameters[++LEDpointer];
       DayS=Day;
       DayS += (Year-1970)*365.2422;    
      if((Year % 4)==0){
        DayS += 1;
      }
      if(Month==2){
      DayS += 31;
      }
      if(Month==3){
      DayS += 59 ;
      }
      if(Month==4){
      DayS += 90;
      }
      if(Month==5){
      DayS += 120;
      }
      if(Month==6){
      DayS += 151;
      }
      if(Month==7){
      DayS += 181;
      }
      if(Month==8){
      DayS += 212;
      }
      if(Month==9){
      DayS += 243;
      }
      if(Month==10){
      DayS += 273;
      }
      if(Month==11){
      DayS += 304;
      }
      if(Month==12){
      DayS += 334;
      }
      
       LEDUnix = (unsigned long)DayS*86400 + (unsigned long)Hour*3600 + (unsigned long)Minute*60 + (unsigned long)Sec ;
       NextLEDConfiflag = 0;
  }
Last:
NextLEDConfiflag = 0;

}

void printTime()
{
  rtc.update();
  Serial.print("(");
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10){
    Serial.print('0'); // Print leading '0' for minute
  }
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10){
    Serial.print('0'); // Print leading '0' for second
  }
  Serial.print(String(rtc.second())); // Print second
  
  Serial.print("|");

  // Few options for printing the day, pick one:
  //Serial.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
  Serial.print("-");
//#ifdef PRINT_USA_DATE
  Serial.print(String(rtc.month()) + "/" +   // Print month
                 String(rtc.date()) + "/");  // Print date
//#else
//  Serial.print(String(rtc.date()) + "/" +    // (or) print date
//                 String(rtc.month()) + "/"); // Print month
//#endif
  Serial.print(String(rtc.year()));        // Print year
  Serial.println(")");    
}
