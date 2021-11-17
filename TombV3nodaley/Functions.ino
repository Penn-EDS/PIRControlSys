
void clearparameters(){
  for(int x=0; x<65; x++){
    parameters[x]=0;
  }
}

void clearLEDparameters(){
  for(int x=0; x<ASize; x++){
    LEDparameters[x]=0;
  }
}


void clearrecvchars(){
  for(int x=0; x<32; x++){
    recvchars[x]=0;
  }
}

void recvdata(){
  delay(100);
  static boolean recvinprogress=false;
  static byte ndx=0;
  char startmarker='<';
  char comma=',';
  char endmarker='>';
  char c;
  
  while(1){
  while(Serial.available()>0 && newdata==false){
    c=Serial.read();
    //delay(100);
    //Serial.println("serial>0");
    if(c==startmarker){
    recvinprogress=true;
    //delay(100);
    //Serial.println("startmaker");
    }

    if(c==comma && recvinprogress==true){
      //Serial.println("comma");
      //Serial.println(recvchars);
      parameters[p]=atol(recvchars);
      //delay(100);
      
      ndx=0;
      clearrecvchars();
      p++;
    }

    if(c==endmarker && recvinprogress==true){
      //Serial.println("endmaker");
      parameters[p]=atol(recvchars);
      recvinprogress=false;
      ndx=0;
      //p=0;
      newdata=true;
     /*
      for(int g=0; g<(p+1); g++){
      //Serial.println(recvchars[g]);
      //Serial.println("parameters readed:");
       Serial.println((String)"g:"+g+" "+parameters[g]);
       //Serial.println((String)"p:"+p+","+PLDinfo[p]);
       //delay(100);
     }
     */
     
     p=0;

     goto OUT;
    }
    
    if(recvinprogress==true && c!=comma && c!=startmarker && c!=']'){
      recvchars[ndx]=c;
      ndx++;  
    }
    
    
  }
  }
  
OUT:
newdata=false;
delay(1);
}
void LEDrecvdata(){
  delay(100);
  static boolean recvinprogress=false;
  static byte ndx=0;
  char startmarker='<';
  char comma=',';
  char endmarker='>';
  char c;
  
  while(1){
  while(Serial.available()>0 && newdata==false){
    c=Serial.read();
    //delay(100);
    //Serial.println("serial>0");
    if(c==startmarker){
    recvinprogress=true;
    //delay(100);
    //Serial.println("startmaker");
    }

    if(c==comma && recvinprogress==true){
      //Serial.println("comma");
      //Serial.println(recvchars);
      LEDparameters[p]=atol(recvchars);
      //delay(100);
      
      ndx=0;
      clearrecvchars();
      p++;
    }

    if(c==endmarker && recvinprogress==true){
      //Serial.println("endmaker");
      LEDparameters[p]=atol(recvchars);
      recvinprogress=false;
      ndx=0;
      //p=0;
      newdata=true;
     /*
      for(int g=0; g<(p+1); g++){
      //Serial.println(recvchars[g]);
      //Serial.println("parameters readed:");
       Serial.println((String)"g:"+g+" "+parameters[g]);
       //Serial.println((String)"p:"+p+","+PLDinfo[p]);
       //delay(100);
     }
     */
     
     p=0;

     goto OUT;
    }
    
    if(recvinprogress==true && c!=comma && c!=startmarker && c!=']'){
      recvchars[ndx]=c;
      ndx++;  
    }
    
    
  }
  }
  
OUT:
newdata=false;
delay(1);
}
