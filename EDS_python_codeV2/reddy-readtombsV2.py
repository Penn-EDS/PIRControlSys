import serial
import datetime
import os
import time
import keyboard #problem to run this in module in Mac
#Tombs = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16] #ALL TOMBS Active
Tombs = [1] #Some Tombs
Tombscall = [b'A',b'B',b'C',b'D',b'E',b'F',b'G',b'H',b'I',b'J',b'K',b'L',b'M',b'N',b'O',b'P']
T=0
nodata = 0
COfilestime=15 #in Seconds
#ser = serial.Serial('/dev/cu.usbserial-A10KBZNY', 57600,timeout=1.009)  # open serial port. Minimum timeout = (PIRdelay*SamplingNumber) + 0.009 .  The PIRdelay and SamplingNumber values can be find in the TombV2.ino code.
ser = serial.Serial('COM10', 57600,timeout=1)  # open serial port. Minimum timeout = (PIRdelay*SamplingNumber) + 0.009 .  The PIRdelay and SamplingNumber values can be find in the TombV2.ino code.
#time.sleep(4)

#Folder Name 
timenow = datetime.datetime.now()
foldername=timenow.strftime("%Y%m%d_%H%M")


#folder creation

#check if output_folder exist
currentpath = os.getcwd()
path = os.path.join(currentpath,"output_folder")
if os.path.isdir(path)==False:
  #create the output_folder if not exist
  os.mkdir(path)
path = os.path.join(path,foldername)
os.mkdir(path)
foldername="output_folder/"+foldername
#workbook = xlsxwriter.Workbook(filename)
for x in Tombs:
 if Tombscall[x-1] == b'A':
     FilenameT1=foldername+"/Tomb1.txt"
     FileT1 = open(FilenameT1,"a")
     FileT1.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT1.close()
 if Tombscall[x-1] == b'B':
     FilenameT2=foldername+"/Tomb2.txt"
     FileT2 = open(FilenameT2,"a")
     FileT2.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT2.close()
 if Tombscall[x-1] == b'C':
     FilenameT3=foldername+"/Tomb3.txt"
     FileT3 = open(FilenameT3,"a")
     FileT3.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT3.close()
 if Tombscall[x-1] == b'D':
     FilenameT4=foldername+"/Tomb4.txt"
     FileT4 = open(FilenameT4,"a")
     FileT4.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT4.close()
 if Tombscall[x-1] == b'E':
     FilenameT5=foldername+"/Tomb5.txt"
     FileT5 = open(FilenameT5,"a")
     FileT5.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT5.close()
 if Tombscall[x-1] == b'F':
     FilenameT6=foldername+"/Tomb6.txt"
     FileT6 = open(FilenameT6,"a")
     FileT6.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT6.close()
 if Tombscall[x-1] == b'G':
     FilenameT7=foldername+"/Tomb7.txt"
     FileT7 = open(FilenameT7,"a")
     FileT7.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT7.close()
 if Tombscall[x-1] == b'H':
     FilenameT8=foldername+"/Tomb8.txt"
     FileT8 = open(FilenameT8,"a")
     FileT8.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT8.close()
 if Tombscall[x-1] == b'I':
     FilenameT9=foldername+"/Tomb9.txt"
     FileT9 = open(FilenameT9,"a")
     FileT9.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT9.close()
 if Tombscall[x-1] == b'J':
     FilenameT10=foldername+"/Tomb10.txt"
     FileT10 = open(FilenameT10,"a")
     FileT10.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT10.close()
 if Tombscall[x-1] == b'K':
     FilenameT11=foldername+"/Tomb11.txt"
     FileT11 = open(FilenameT11,"a")
     FileT11.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT11.close()
 if Tombscall[x-1] == b'L':
     FilenameT12=foldername+"/Tomb12.txt"
     FileT12 = open(FilenameT12,"a")
     FileT12.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT12.close()
 if Tombscall[x-1] == b'M':
     FilenameT13=foldername+"/Tomb13.txt"
     FileT13 = open(FilenameT13,"a")
     FileT13.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT13.close()
 if Tombscall[x-1] == b'N':
     FilenameT14=foldername+"/Tomb14.txt"
     FileT14 = open(FilenameT14,"a")
     FileT14.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT14.close()
 if Tombscall[x-1] == b'O':
     FilenameT15=foldername+"/Tomb15.txt"
     FileT15 = open(FilenameT15,"a")
     FileT15.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT15.close()
 if Tombscall[x-1] == b'P':
     FilenameT16=foldername+"/Tomb16.txt"
     FileT16 = open(FilenameT16,"a")
     FileT16.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     #FileT16.close()
 


try:
 starttime=time.time() 
 while True:
     
  #To send the LED Configuration to each tomb
  if (keyboard.is_pressed("R")):
    for x in Tombs:
         if Tombscall[x-1] == b'A':
            #send all information inside LEDT1config.txt
         if Tombscall[x-1] == b'B':
             #send all information inside LEDT2config.txt
         if Tombscall[x-1] == b'C':
             #send all information inside LEDT3config.txt
         if Tombscall[x-1] == b'D':
           #send all information inside LEDT4config.txt
         if Tombscall[x-1] == b'E':
             #send all information inside LEDT5config.txt
         if Tombscall[x-1] == b'F':
             #send all information inside LEDT6config.txt
         if Tombscall[x-1] == b'G':
            #send all information inside LEDT7config.txt
         if Tombscall[x-1] == b'H':
             #send all information inside LEDT8config.txt
         if Tombscall[x-1] == b'I':
             #send all information inside LEDT9config.txt
         if Tombscall[x-1] == b'J':
             #send all information inside LEDT10config.txt
         if Tombscall[x-1] == b'K':
            #send all information inside LEDT11config.txt
         if Tombscall[x-1] == b'L':
             #send all information inside LEDT12config.txt
         if Tombscall[x-1] == b'M':
            #send all information inside LEDT13config.txt
         if Tombscall[x-1] == b'N':
            #send all information inside LEDT14config.txt
         if Tombscall[x-1] == b'O':
             #send all information inside LEDT15config.txt
         if Tombscall[x-1] == b'P':
             #send all information inside LEDT16config.txt
           
  #To send the LED Configuration Only to Tomb 1
  if (keyboard.is_pressed("A")):
    #send all information inside LEDT1config.txt
    
  #To send the LED Configuration Only to Tomb 2
  if (keyboard.is_pressed("B")):
    #send all information inside LEDT2config.txt
    
  #To send the LED Configuration Only to Tomb 3
  if (keyboard.is_pressed("C")):
    #send all information inside LEDT3config.txt

  #To send the LED Configuration Only to Tomb 4
  if (keyboard.is_pressed("D")):
    #send all information inside LEDT4config.txt
  
  #To setup the RTC with the computer time
  if (keyboard.is_pressed("T")):
      ser.write(b'T')
      timenow = datetime.datetime.now()
      RTCtime=timenow.strftime("<%S,%M,%H,%w,%d,%m,%y>")
      RTCtime=str.encode(RTCtime)
      ser.write(RTCtime)
  #saving and closing the files every COfilestime
  if (time.time()-starttime)>=COfilestime or keyboard.is_pressed("Q") :
     #closing and opening the just the files for the tombs that are being use
     for x in Tombs:
         if Tombscall[x-1] == b'A':
             FileT1.close()
             FileT1 = open(FilenameT1,"a")
         if Tombscall[x-1] == b'B':
             FileT2.close()
             FileT2 = open(FilenameT2,"a")
         if Tombscall[x-1] == b'C':
             FileT3.close()
             FileT3 = open(FilenameT3,"a")
         if Tombscall[x-1] == b'D':
             FileT4.close()
             FileT4 = open(FilenameT4,"a")
         if Tombscall[x-1] == b'E':
             FileT5.close()
             FileT5 = open(FilenameT5,"a")
         if Tombscall[x-1] == b'F':
             FileT6.close()
             FileT6 = open(FilenameT6,"a")
         if Tombscall[x-1] == b'G':
             FileT7.close()
             FileT7 = open(FilenameT7,"a")
         if Tombscall[x-1] == b'H':
             FileT8.close()
             FileT8 = open(FilenameT8,"a")
         if Tombscall[x-1] == b'I':
             FileT9.close()
             FileT9 = open(FilenameT9,"a")
         if Tombscall[x-1] == b'J':
             FileT10.close()
             FileT10 = open(FilenameT10,"a")
         if Tombscall[x-1] == b'K':
             FileT11.close()
             FileT11 = open(FilenameT11,"a")
         if Tombscall[x-1] == b'L':
             FileT12.close()
             FileT22 = open(FilenameT12,"a")
         if Tombscall[x-1] == b'M':
             FileT13.close()
             FileT13 = open(FilenameT13,"a")
         if Tombscall[x-1] == b'N':
             FileT14.close()
             FileT14 = open(FilenameT14,"a")
         if Tombscall[x-1] == b'O':
             FileT15.close()
             FileT15 = open(FilenameT15,"a")
         if Tombscall[x-1] == b'P':
             FileT16.close()
             FileT16 = open(FilenameT16,"a")
     
     #print("Files Closed")
     starttime=time.time()
        
  if T == len(Tombs):
   T=0
  m = Tombscall[Tombs[T] - 1] 
  ser.write(m)     # Asking tomb for data
  sended=str(m,'utf-8')
  print(sended)
  data=ser.readline()
  
  #saving timestamp to the correct spreadsheet
  timestampnow = datetime.datetime.now()
  timestamp=timestampnow.strftime("%Y-%m-%dT%H:%M:%S")
  data=str(data,'utf-8')
  
  if data != '':
    data=timestamp+"," + data
    print(data)
  
  if m == b'A':
     FileT1.write(data)
  if m == b'B':
     FileT2.write(data)
  if m == b'C':
     FileT3.write(data)
  if m == b'D':
     FileT4.write(data)
  if m == b'E':
     FileT5.write(data)
  if m == b'F':
     FileT6.write(data)
  if m == b'G':
     FileT7.write(data)
  if m == b'H':
     FileT8.write(data)
  if m == b'I':
     FileT9.write(data)
  if m == b'J':
     FileT10.write(data)
  if m == b'K':
     FileT11.write(data)
  if m == b'L':
     FileT12.write(data)
  if m == b'M':
     FileT13.write(data)
  if m == b'N':
     FileT14.write(data)
  if m == b'O':
     FileT15.write(data)
  if m == b'P':
     FileT16.write(data)
       
  T += 1
except KeyboardInterrupt:
  #close all files
    for x in Tombs:
         if Tombscall[x-1] == b'A':
             FileT1.close()
         if Tombscall[x-1] == b'B':
             FileT2.close()
         if Tombscall[x-1] == b'C':
             FileT3.close()
         if Tombscall[x-1] == b'D':
             FileT4.close()
         if Tombscall[x-1] == b'E':
             FileT5.close()
         if Tombscall[x-1] == b'F':
             FileT6.close()
         if Tombscall[x-1] == b'G':
             FileT7.close()
         if Tombscall[x-1] == b'H':
             FileT8.close()
         if Tombscall[x-1] == b'I':
             FileT9.close()
         if Tombscall[x-1] == b'J':
             FileT10.close()
         if Tombscall[x-1] == b'K':
             FileT11.close()
         if Tombscall[x-1] == b'L':
             FileT12.close()
         if Tombscall[x-1] == b'M':
             FileT13.close()
         if Tombscall[x-1] == b'N':
             FileT14.close()
         if Tombscall[x-1] == b'O':
             FileT15.close()
         if Tombscall[x-1] == b'P':
             FileT16.close()
    print("Ctrl-C was pressed")
    pass
    ser.close()             # close ports

