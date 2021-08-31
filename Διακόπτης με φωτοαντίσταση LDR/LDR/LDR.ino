/*
   -- LDR_Διακόπτης --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.6 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.8.01 or later version;
     - for iOS 1.5.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID ""  //"dbSoft"
#define REMOTEXY_WIFI_PASSWORD "" //"xVf5nTEN"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "a515f1bb78cb31301ce9f499c3ed7620"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,95,0,13,13,0,
  2,0,57,30,20,9,2,26,31,31,
  79,78,0,79,70,70,0,4,0,40,
  16,8,27,2,26,7,54,6,31,26,
  9,2,26,2,129,0,17,7,70,6,
  17,76,68,82,32,206,148,206,185,206,
  177,206,186,207,140,207,128,207,132,206,
  183,207,130,32,206,181,206,185,207,131,
  207,140,206,180,206,191,207,133,0,1,
  0,12,45,12,12,2,31,83,97,118,
  101,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  int8_t slider_1; // =0..100 slider position 
  int16_t edit_1;  // 32767.. +32767 
  uint8_t button_1; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#include <ESP8266WiFi.h>
#include <EEPROM.h>

//-------auto connect---------------------------
        #include <DNSServer.h>
        #include <ESP8266WebServer.h>
        #include <ESP8266WiFiMulti.h>
        #include <WiFiManager.h>
        ESP8266WiFiMulti WiFiMulti;
       
        char con_ssid[32]; 
        char con_psk[64];  
 //------- end auto connect-------------------------


int timiFotos = 0; 
int EEPROM_timiFotos = 0;
int pinAisthitira = A0; 
int RelayPin = D1; 
//----------------------------------------
void setup() {
//----------------------------------------
 // RemoteXY_Init (); 
  
   Serial.begin(9600); //Epikoinonia seiriakis thiras

   //------------Start autoConnect--------------   
    WiFi.mode(WIFI_STA);
    WiFiManager wifiManager;
     //     wifiManager.resetSettings();
    wifiManager.setTimeout(180); 
 
    if (!wifiManager.autoConnect("WiFi-ESP_A", "12345678")) // credenziali per accedere alla modalità AP
    {
      delay(3000);
      ESP.reset();
      delay(5000);
    }
    WiFi.SSID().toCharArray(con_ssid, 32);
    WiFi.psk().toCharArray(con_psk, 64);
    remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD,  con_ssid , con_psk, REMOTEXY_CLOUD_SERVER, REMOTEXY_CLOUD_PORT, REMOTEXY_CLOUD_TOKEN );
   //------------end autoConnect--------------
    
     pinMode(RelayPin, OUTPUT);
     digitalWrite(RelayPin,LOW);
     
     EEPROM.begin(512);
     EEPROM.get(100,EEPROM_timiFotos); 
    if ( EEPROM_timiFotos > 0 ) {
     EEPROM.get( 100,EEPROM_timiFotos);
    } 
    else { 
     EEPROM_timiFotos = 400 ; 
     EEPROM.begin(512);
     EEPROM.put( 100,EEPROM_timiFotos);
     EEPROM.commit();
    }

    RemoteXY.edit_1 = EEPROM_timiFotos ;
    RemoteXY_sendInputVariables();
}
//----------------------------------------
void loop() {
//----------------------------------------
RemoteXY_Handler ();

 if (RemoteXY.switch_1 == 1){
   digitalWrite(RelayPin,HIGH);
   Serial.println(" light ");
   delay(1000); 
 }
 else {
    if (RemoteXY.button_1 == 1){
       EEPROM.begin(512);
       EEPROM.put( 100,RemoteXY.edit_1); 
       EEPROM.commit();
       EEPROM.get( 100,EEPROM_timiFotos);
       delay(300);
       RemoteXY.slider_1 = ( map(EEPROM_timiFotos, 0, 900, 0, 100) ) ;
       RemoteXY_sendInputVariables();
       RemoteXY.button_1 = 0 ;
    }
     
    timiFotos = analogRead(pinAisthitira); 
    delay(500);
    Serial.println(timiFotos); 
   // Serial.println(RemoteXY.edit_1);
    if (timiFotos <  RemoteXY.edit_1 - 50 )
    {
     digitalWrite(RelayPin, LOW);
    }
    if (timiFotos > RemoteXY.edit_1  )
    {
     digitalWrite(RelayPin,HIGH);
     Serial.println(" light ");
    }
 } 
}
