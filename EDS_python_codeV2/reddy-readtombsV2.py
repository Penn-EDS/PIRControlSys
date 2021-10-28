import serial
import datetime
import os
import time
#Tombs = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16] #ALL TOMBS Active
Tombs = [1,2,8] #Some Tombs
Tombscall = [b'A',b'B',b'C',b'D',b'E',b'F',b'G',b'H',b'I',b'J',b'K',b'L',b'M',b'N',b'O',b'P']
T=0
row = 1
col = 1
nodata = 0
ser = serial.Serial('/dev/cu.usbserial-A10KBZNY', 57600,timeout=1.009)  # open serial port. Minimum timeout = (PIRdelay*SamplingNumber) + 0.009 .  The PIRdelay and SamplingNumber values can be find in the TombV2.ino code.
#time.sleep(4)

#Folder Name 
timenow = datetime.datetime.now()
foldername=timenow.strftime("%Y%m%d_%H%M")

#folder creation
currentpath = os.getcwd() #getting current path
path = os.path.join(currentpath,foldername)
os.mkdir(path)
#workbook = xlsxwriter.Workbook(filename)
for x in Tombs:
 if Tombscall[x-1] == b'A':
     FilenameT1=foldername+"/Tomb1.txt"
     FileT1 = open(FilenameT1,"a")
     FileT1.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT1.close()
 if Tombscall[x-1] == b'B':
     FilenameT2=foldername+"/Tomb2.txt"
     FileT2 = open(FilenameT2,"a")
     FileT2.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT2.close()
 if Tombscall[x-1] == b'C':
     FilenameT3=foldername+"/Tomb3.txt"
     FileT3 = open(FilenameT3,"a")
     FileT3.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT3.close()
 if Tombscall[x-1] == b'D':
     FilenameT4=foldername+"/Tomb4.txt"
     FileT4 = open(FilenameT4,"a")
     FileT4.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT4.close()
 if Tombscall[x-1] == b'E':
     FilenameT5=foldername+"/Tomb5.txt"
     FileT5 = open(FilenameT5,"a")
     FileT5.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT5.close()
 if Tombscall[x-1] == b'F':
     FilenameT6=foldername+"/Tomb6.txt"
     FileT6 = open(FilenameT6,"a")
     FileT6.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT6.close()
 if Tombscall[x-1] == b'G':
     FilenameT7=foldername+"/Tomb7.txt"
     FileT7 = open(FilenameT7,"a")
     FileT7.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT7.close()
 if Tombscall[x-1] == b'H':
     FilenameT8=foldername+"/Tomb8.txt"
     FileT8 = open(FilenameT8,"a")
     FileT8.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT8.close()
 if Tombscall[x-1] == b'I':
     FilenameT9=foldername+"/Tomb9.txt"
     FileT9 = open(FilenameT9,"a")
     FileT9.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT9.close()
 if Tombscall[x-1] == b'J':
     FilenameT10=foldername+"/Tomb10.txt"
     FileT10 = open(FilenameT10,"a")
     FileT10.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT10.close()
 if Tombscall[x-1] == b'K':
     FilenameT11=foldername+"/Tomb11.txt"
     FileT11 = open(FilenameT11,"a")
     FileT11.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT11.close()
 if Tombscall[x-1] == b'L':
     FilenameT12=foldername+"/Tomb12.txt"
     FileT12 = open(FilenameT12,"a")
     FileT12.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT12.close()
 if Tombscall[x-1] == b'M':
     FilenameT13=foldername+"/Tomb13.txt"
     FileT13 = open(FilenameT13,"a")
     FileT13.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT13.close()
 if Tombscall[x-1] == b'N':
     FilenameT14=foldername+"/Tomb14.txt"
     FileT14 = open(FilenameT14,"a")
     FileT14.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT14.close()
 if Tombscall[x-1] == b'O':
     FilenameT15=foldername+"/Tomb15.txt"
     FileT15 = open(FilenameT15,"a")
     FileT15.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT15.close()
 if Tombscall[x-1] == b'P':
     FilenameT16=foldername+"/Tomb16.txt"
     FileT16 = open(FilenameT16,"a")
     FileT16.write("Time Stamp,Data Header ID,PIR1,PIR2,PIR3,PIR4,PIR5,PIR6,LDR1,LDR2,LDR3,LDR4,LDR5,LDR6 \n")
     FileT16.close()
 

try:
 while True:
  if T == len(Tombs):
   T=0
   row += 1
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
     FileT1 = open(FilenameT1,"a")
     FileT1.write(data)
     FileT1.close()
  if m == b'B':
     FileT2 = open(FilenameT2,"a")
     FileT2.write(data)
     FileT2.close()
  if m == b'C':
     FileT3 = open(FilenameT3,"a")
     FileT3.write(data)
     FileT3.close()
  if m == b'D':
     FileT4 = open(FilenameT4,"a")
     FileT4.write(data)
     FileT4.close()
  if m == b'E':
     FileT5 = open(FilenameT5,"a")
     FileT5.write(data)
     FileT5.close()
  if m == b'F':
     FileT6 = open(FilenameT6,"a")
     FileT6.write(data)
     FileT6.close()
  if m == b'G':
     FileT7 = open(FilenameT7,"a")
     FileT7.write(data)
     FileT7.close()
  if m == b'H':
     FileT8 = open(FilenameT8,"a")
     FileT8.write(data)
     FileT8.close()
  if m == b'I':
     FileT9 = open(FilenameT9,"a")
     FileT9.write(data)
     FileT9.close()
  if m == b'J':
     FileT10 = open(FilenameT10,"a")
     FileT10.write(data)
     FileT10.close()
  if m == b'K':
     FileT11 = open(FilenameT11,"a")
     FileT11.write(data)
     FileT11.close()
  if m == b'L':
     FileT12 = open(FilenameT12,"a")
     FileT12.write(data)
     FileT12.close()
  if m == b'M':
     FileT13 = open(FilenameT13,"a")
     FileT13.write(data)
     FileT13.close()
  if m == b'N':
     FileT14 = open(FilenameT14,"a")
     FileT14.write(data)
     FileT14.close()
  if m == b'O':
     FileT15 = open(FilenameT15,"a")
     FileT15.write(data)
     FileT15.close()
  if m == b'P':
     FileT16 = open(FilenameT16,"a")
     FileT16.write(data)
     FileT16.close()
       
  T += 1
except KeyboardInterrupt:
    print("Ctrl-C was pressed")
    pass
    ser.close()             # close ports

