
//------------------Alex basic code---------------------------
//import processing.serial.*;

//Serial myPort;  // The serial port

//void setup() {
//  // List all the available serial ports:
//  printArray(Serial.list());
//  // Open the port you are using at the rate you want:
//  myPort = new Serial(this, Serial.list()[2], 57600);
//}

//void draw() {
//  delay(2000);
//  myPort.write('A');
// if (myPort.available() > 0) {
//    String inBuffer = myPort.readString();   
//    if (inBuffer != null) {
//      println(inBuffer);
//    }
//  }
//}




//-----------------------Alex modified Code from Reddy------------------------------------

// Processing Sketch for storing and plotting data
/*
* Receiving a simple string of values from the arduino and saving to a text file with a UTC (iso8601) encoding
* Light data are mapped to a background and the activity of each channel displayed as histograms.
* Press 'x' to stop logging and save file
*/

import processing.serial.*;
import java.util.Date;
import java.text.SimpleDateFormat;

PrintWriter output;
SimpleDateFormat fnameFormat= new SimpleDateFormat("yyMMdd_HHmm"); // define date and time formatfor filename
SimpleDateFormat timeFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'"); // and for timestamps of incomming data
String fileName;

Serial myPort; // Create objects from Serial class
short portIndex= 2; // select the com port, 0 is the first port (Macs normally use 0, windows machines 1, or highest)
String dataIn = null;
String HEADER = "a"; //Data HEADER
short LF = 10; // ASCII linefeed indicator


void setup()
{


// check output from list of connections and change portIndex if needed.
println(Serial.list());
String portName = Serial.list()[portIndex]; // Open whatever serial port is connected to the Arduino.
println(Serial.list()); // check output from list of connections and change portIndex if needed.
println(" Connecting to -> " + Serial.list()[portIndex]);
myPort = new Serial(this, portName, 57600);
myPort.bufferUntil(LF);
delay(1);
Date now = new Date();
fileName = fnameFormat.format(now);
output = createWriter(fileName + ".csv"); // save the file in the sketch folder
println("Time \t PIR1 \t PIR2 \t PIR3 \t PIR4 \t PIR5 \t PIR6 \t LDR1 \t LDR2 \t LDR3 \t LDR4 \t LDR5 \t LDR6");
output.println("Time,header,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6"); // headers to file as comma-delimited
}

void draw()
{
  delay(3000);
  myPort.write('A');
//void serialEvent(Serial myPort) {
 if (myPort.available() > 0) {
String dataI = myPort.readString(); // read data from the port:
String timeString = timeFormat.format(new Date());
if (dataI != null) {
println(timeString + "," + dataI); // tell us who sent what:
output.println(timeString+ "," +dataI); //save sent message:
  }
 }
}
void keyPressed() {
if (key == 'x' || key == 'X') {
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  exit(); // Stops the program
  }
}
