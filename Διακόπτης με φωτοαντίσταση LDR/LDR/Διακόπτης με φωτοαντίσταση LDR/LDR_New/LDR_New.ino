/*
   -- LDR Διακόπτης εισόδου New --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

#include <EEPROM.h>
#if defined (ESP8266)
  #include <ESP8266WiFi.h>
#elif defined (ESP32)
  #include <WiFi.h>  
#endif
#include <RemoteXY.h>

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 259 bytes
  { 255,5,0,13,0,252,0,16,27,1,130,1,2,13,31,24,27,130,1,2,
  62,32,37,27,130,1,2,39,31,22,27,2,0,5,23,22,11,2,26,31,
  31,77,97,110,117,97,108,0,65,117,116,111,0,2,0,5,48,22,11,2,
  26,31,31,79,78,0,79,70,70,0,7,52,6,71,26,8,2,26,2,66,
  1,38,8,10,79,5,26,70,16,39,89,9,9,26,37,0,129,0,50,8,
  10,4,17,53,48,48,0,129,0,52,43,7,4,17,50,53,48,0,129,0,
  53,82,5,4,17,48,37,0,129,0,5,42,13,4,16,77,97,110,117,97,
  108,0,129,0,6,65,21,4,16,65,117,116,111,32,108,101,118,101,108,32,
  58,0,129,0,5,15,13,5,16,77,111,100,101,0,129,0,50,90,9,7,
  16,79,78,0,129,0,3,2,45,4,16,76,68,82,32,206,148,206,185,206,
  177,206,186,207,140,207,128,207,132,206,183,207,130,32,206,181,206,185,207,131,
  207,140,206,180,206,191,207,133,0,1,0,6,81,9,9,2,31,0,129,0,
  17,83,11,5,16,83,97,118,101,0,67,4,7,91,23,7,2,26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  int16_t edit_1;  // 32767.. +32767 
  uint8_t button_1; // =1 if button pressed, else =0 

    // output variables
  int8_t level_1; // =0..100 level position 
  uint8_t led_1; // led state 0 .. 1 
  char text_1[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

//-------auto connect---------------------------
  #include <WiFiManager.h>
  char con_ssid[32]; //will hold the ssid of the wlan to which it is connectd
  char con_psk[64];  // ^^ private shared key for the wlan (password)
 //------- end auto connect-------------------------
 CRemoteXY *remotexy;

float timiFotos = 0; 
int EEPROM_timiFotos = 0;
int pinAisthitira = A0; 
int RelayPin = D1; 
bool light_on = false ;
//----------------------------------------
void setup() {
//----------------------------------------  
 Serial.begin(115200);

// Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);  //  
  
  StartConect();
  StartRemoteXY();

  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin,LOW);
 
   EEPROM.begin(512);
   EEPROM.get(100,EEPROM_timiFotos); 
   if (EEPROM_timiFotos <= 0 ){
	 //for (int i = 0; i < 512; i++) { EEPROM.write(i, 0); }  
     EEPROM.put( 100,201); 
     EEPROM.commit();
     delay(300);
   }
  EEPROM.get(100,EEPROM_timiFotos);  // -16777216 -16777016 51400
  EEPROM.end() ;

  RemoteXY.edit_1 = EEPROM_timiFotos ;
  RemoteXY.led_1 = 0 ;
}

//----------------------------------------
void loop(){ 
//----------------------------------------  
  remotexy->handler ();
  timiFotos = analogRead(pinAisthitira); 
  dtostrf(timiFotos, 0,0, RemoteXY.text_1);
  Serial.println(EEPROM_timiFotos);
  delay(500);

    if (RemoteXY.button_1 == 1){
       EEPROM.begin(512);
       EEPROM.put( 100,RemoteXY.edit_1); 
       EEPROM.commit();
       delay(300);
       EEPROM.get( 100,RemoteXY.edit_1);
       EEPROM.end() ;
	    // RemoteXY.edit_1 = EEPROM.read(100);  
       EEPROM_timiFotos = RemoteXY.edit_1 ;
       RemoteXY.level_1 = ( map(timiFotos, 0, 500, 0, 100) ) ;
       RemoteXY.button_1 = 0 ;
    }
    
      RemoteXY.level_1 = ( map(timiFotos, 0, 500, 0, 100) ) ;
      EEPROM_timiFotos = RemoteXY.edit_1 ;

      if (!RemoteXY.switch_1){
         RemoteXY.led_1 = (timiFotos <  EEPROM_timiFotos -100)?0:1;
         if (timiFotos >= EEPROM_timiFotos  ){ 
             digitalWrite(RelayPin,HIGH);
         }
         else if (timiFotos <  EEPROM_timiFotos -100 ) {
             digitalWrite(RelayPin, LOW); 
         } 
        else {
             Serial.println(" waiting.... ");
        }
      }
      else {
         if(RemoteXY.switch_2){
           digitalWrite(RelayPin,HIGH);
           RemoteXY.led_1 = 1 ;
         }
         else {
          digitalWrite(RelayPin,LOW);
           RemoteXY.led_1 = 0 ;
         }
      }
}

void StartConect(){
    //------------Start autoConnect---- 
    WiFiManager wifiManager;
    // wifiManager.resetSettings();
    wifiManager.setTimeout(180); 
    if (!wifiManager.autoConnect("WiFi-ESP_A", "12345678")) // credenziali per accedere alla modalità AP
    {
      delay(3000);
      ESP.reset();
      delay(5000);
    }
    WiFi.SSID().toCharArray(con_ssid, 32);
    WiFi.psk().toCharArray(con_psk, 64);
     
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
   //------------end autoConnect-----------
}

void StartRemoteXY(){

 CRemoteXYComm_WiFi * wifi =  new CRemoteXYComm_WiFi (
    con_ssid,                            // REMOTEXY_WIFI_SSID
    con_psk                                 // REMOTEXY_WIFI_PASSWORD
  );
  
  remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, "");
  
  remotexy->addConnection (new CRemoteXYConnectionServer ( wifi, 
    6377                                      // REMOTEXY_SERVER_PORT
  ));
  
  remotexy->addConnection (new CRemoteXYConnectionCloud ( wifi, 
    "cloud.remotexy.com",                     // REMOTEXY_CLOUD_SERVER 
    6376,                                     // REMOTEXY_CLOUD_PORT
    "fe907fb1cef195e8720675bdee8c869e"                // REMOTEXY_CLOUD_TOKEN
  ));
 

}
