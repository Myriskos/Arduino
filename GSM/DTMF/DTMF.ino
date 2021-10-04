#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
#define RELAY_1 8
#define RELAY_2 9
#define RELAY_3 10
#define RELAY_4 11
boolean relay1_state = true;
boolean relay2_state = true;
boolean relay3_state = true;
boolean relay4_state = true;
//stores incomming data from sim800l
String buff;
String dtmf_cmd;
boolean is_call = false;
 
void setup()
{
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT); 
  digitalWrite(RELAY_1, HIGH); 
  digitalWrite(RELAY_2, HIGH); 
  digitalWrite(RELAY_3, HIGH); 
  digitalWrite(RELAY_4, HIGH); 
  Serial.begin(115200);
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(3000);
  fonaSS.begin(9600); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
    Serial.println(F("FONA is OK"));
    
  fona.println("AT"); //send AT
  delay(500);

  fona.println("AT+DDET=1"); //Enable DTMF
  delay(500);
}

void loop()
{
  while(fona.available()){
    buff = fona.readString();
    Serial.println(buff);
    if(is_call = true)
    {
      if(int index = buff.indexOf("+DTMF:") > -1 )
      {
        index = buff.indexOf(":");
        dtmf_cmd = buff.substring(index+1, buff.length());
        dtmf_cmd.trim();
        Serial.println("dtmf_cmd: "+dtmf_cmd);
        doAction();
      }    
      if(buff.indexOf("NO CARRIER") > -1)
      {
        fona.println("ATH");
        is_call = false;
      }
    }
     if(buff.indexOf("RING") > -1)
    {
      delay(2000);
      fona.println("ATA");
      is_call = true;
    }
  }

  
  //-------------------------------------------------------
  while(Serial.available())  {
    fona.println(Serial.readString());
  }
  //-------------------------------------------------------
}


void doAction(){
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  if(dtmf_cmd == "1"){
    relay1_state = !relay1_state;  
    digitalWrite(RELAY_1, relay1_state);
    if(relay1_state == false)
      {Serial.println("Relay 1 has been ON");}
    else
      {Serial.println("Relay 1 has been OFF");}
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(dtmf_cmd == "2"){
    relay2_state = !relay2_state;  
    digitalWrite(RELAY_2, relay2_state);
    if(relay2_state == false)
      {Serial.println("Relay 2 has been ON");}
    else
      {Serial.println("Relay 2 has been OFF");}
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

    else if(dtmf_cmd == "3"){
    relay3_state = !relay3_state;  
    digitalWrite(RELAY_3, relay3_state);
    if(relay3_state == false)
      {Serial.println("Relay 3 has been ON");}
    else
      {Serial.println("Relay 3 has been OFF");}
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

    else if(dtmf_cmd == "4"){
    relay4_state = !relay4_state;  
    digitalWrite(RELAY_4, relay4_state);
    if(relay4_state == false)
      {Serial.println("Relay 4 has been ON");}
    else
      {Serial.println("Relay 4 has been OFF");}
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}

/*
AT
Check Sim is ready or not
AT+CPIN?
 */
