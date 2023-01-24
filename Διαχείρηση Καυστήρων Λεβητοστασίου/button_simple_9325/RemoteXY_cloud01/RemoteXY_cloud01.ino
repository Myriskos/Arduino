/*
   -- Διαχείρηση Καυτήρων Λεβητοστασίου --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.7.12 or later version;
     - for iOS 1.4.7 or later version;
    
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
#define REMOTEXY_WIFI_SSID "" //"dbSoft"
#define REMOTEXY_WIFI_PASSWORD "" // "xVf5nTEN"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//#define REMOTEXY_CLOUD_TOKEN "16fc05194613e331f4df167717f19ac5"  // ILI9341
#define REMOTEXY_CLOUD_TOKEN "078a2fb13ad44666194d3dbd124c4332"  // ILI9486  - ILI9327 


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,135,0,192,1,11,13,4,
  66,132,14,17,14,11,0,2,24,67,
  5,8,30,26,10,0,2,26,11,66,
  132,42,15,10,8,2,2,24,66,132,
  42,25,10,8,2,2,24,66,132,42,
  34,10,8,2,2,24,65,23,69,16,
  6,6,2,65,7,69,25,6,6,2,
  65,7,69,34,6,6,2,129,0,30,
  0,34,5,0,17,206,155,206,181,206,
  178,206,183,207,132,206,191,207,131,207,
  132,206,172,207,131,206,185,206,191,0,
  129,0,8,43,25,4,0,17,206,157,
  206,181,207,129,206,172,32,206,155,206,
  173,206,178,206,183,207,132,206,177,0,
  129,0,61,43,28,4,1,17,206,157,
  206,181,207,129,206,172,32,206,156,207,
  128,207,140,207,138,206,187,206,181,207,
  129,0,129,0,80,35,17,4,2,17,
  206,156,207,128,207,140,206,185,206,187,
  206,181,207,129,0,66,132,42,44,10,
  8,2,2,24,65,7,69,44,6,6,
  2,67,4,54,16,14,6,2,2,26,
  11,67,4,54,25,14,6,2,2,26,
  11,67,4,54,34,14,6,2,2,26,
  11,67,4,54,44,14,6,2,2,26,
  11,129,0,8,9,27,3,1,17,206,
  149,206,189,206,181,207,129,206,179,207,
  140,207,130,32,206,155,206,173,206,178,
  206,183,207,132,206,177,207,130,32,58,
  0,67,5,37,8,25,5,1,2,26,
  51,129,0,79,16,20,4,2,17,206,
  155,206,173,206,178,206,183,207,132,206,
  177,32,32,203,154,67,0,129,0,79,
  25,27,4,2,17,206,154,207,133,206,
  186,206,187,206,191,207,134,206,191,207,
  129,206,183,207,132,206,174,0,66,132,
  67,18,13,10,1,2,24,67,5,61,
  30,26,10,1,2,26,11,131,1,34,
  55,16,5,1,2,31,80,97,103,101,
  49,0,131,0,54,55,14,5,2,2,
  31,80,97,103,101,50,0,129,0,16,
  7,55,5,2,17,206,152,206,181,207,
  129,206,188,206,191,206,186,207,129,206,
  177,207,131,206,175,206,181,207,130,32,
  206,181,206,187,206,173,206,179,207,135,
  206,191,207,133,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  int8_t level_0_1; // =0..100 level position 
  char text_0_1[11];  // string UTF8 end zero 
  int8_t level_1; // =0..100 level position 
  int8_t level_2; // =0..100 level position 
  int8_t level_3; // =0..100 level position 
  uint8_t led_1_r; // =0..255 LED Red brightness 
  uint8_t led_1_g; // =0..255 LED Green brightness 
  uint8_t led_1_b; // =0..255 LED Blue brightness 
  uint8_t led_2_r; // =0..255 LED Red brightness 
  uint8_t led_2_g; // =0..255 LED Green brightness 
  uint8_t led_2_b; // =0..255 LED Blue brightness 
  uint8_t led_3_r; // =0..255 LED Red brightness 
  uint8_t led_3_g; // =0..255 LED Green brightness 
  uint8_t led_3_b; // =0..255 LED Blue brightness 
  int8_t level_4; // =0..100 level position 
  uint8_t led_4_r; // =0..255 LED Red brightness 
  uint8_t led_4_g; // =0..255 LED Green brightness 
  uint8_t led_4_b; // =0..255 LED Blue brightness 
  char text_1[11];  // string UTF8 end zero 
  char text_2[11];  // string UTF8 end zero 
  char text_3[11];  // string UTF8 end zero 
  char text_4[11];  // string UTF8 end zero 
  char text_0[51];  // string UTF8 end zero 
  int8_t level_0_2; // =0..100 level position 
  char text_0_2[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <SoftwareSerial.h>
SoftwareSerial s2(D7,D8);  // TX-RX 16,17  Serial2
SoftwareSerial s(D5,D6);   //  TX-RX 14,15  Serial3


/*
  MEGA        ESP8266 NODE MCU
  TX16 -----> D6
  RX17 -----> D5

  SoftwareSerial SerialMega(16,17);    // TX-RX 5,6   ΣΤΟ MEGA
  SoftwareSerial ArduinoMega(D5,D6);   // TX-RX 16,17 ΣΤΟ ESP 
  
*/ 


#include <string.h>
#include<stdio.h>
String tValue;// 
String watchdog  ;

String c ;
String b ; // Νερά Λέβητα
String d ; // Νερά Μπόϊλερ
String e ; // επιστρεφόμενα

String therm1 ;
String therm2 ;
String therm3 ;
String therm4 ;
String Levitas ;

float therm_1 ;
float therm_2 ;
float therm_3 ;
float therm_4 ;
String CL , CK , CB ;




//-------auto connect---------------------------
        #include <DNSServer.h>
        #include <ESP8266WebServer.h>
        #include <ESP8266WiFiMulti.h>
        #include <WiFiManager.h>
        ESP8266WiFiMulti WiFiMulti;
       
        char con_ssid[32]; //will hold the ssid of the wlan to which it is connectd
        char con_psk[64];  // ^^ private shared key for the wlan (password)
 //------- end auto connect-------------------------


//------------------------------
void setup(){
//------------------------------  
  watchdog = "%1%" ;
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  s.begin(9600);
  while (!s) {
    Serial.print( "s."  );  
  }  
  s2.begin(9600);
  while (!s2) {
    Serial.print( "s2."  );  
  }  
// RemoteXY_Init (); 
  
//------------Start autoConnect--------------   
// Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);


    //--- settaggi di Wifimanager-------
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
  // RemoteXY 2.4.6  
  //  remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD,  con_ssid , con_psk, REMOTEXY_CLOUD_SERVER, REMOTEXY_CLOUD_PORT, REMOTEXY_CLOUD_TOKEN );

  //---------------  // RemoteXY 3.1.9
   remotexy = new CRemoteXY (
    RemoteXY_CONF_PROGMEM,
    &RemoteXY,
    "",
    new CRemoteXYConnectionCloud (
      new CRemoteXYComm_WiFi (
        con_ssid,       // REMOTEXY_WIFI_SSID
        con_psk),          // REMOTEXY_WIFI_PASSWORD
      "cloud.remotexy.com",   // REMOTEXY_CLOUD_SERVER
      6376,                   // REMOTEXY_CLOUD_PORT
      "078a2fb13ad44666194d3dbd124c4332"  // REMOTEXY_CLOUD_TOKEN
    )
  );
  //----------------

    
     //------------end autoConnect-------------- 
    //Serial.print( RemoteXY.connect_flag );   
}

//------------------------------
void readSerialMega(){
//------------------------------ 
      c =  s.readString() ;
      Serial.println( c  );
     //c = "T72.50T45.00T75.00T40.00T45.00L01L01K01B01" ;
      b = c.substring(1 ,6);
      d = c.substring(7 ,12);
  therm1= c.substring(13,18);   
  therm2= c.substring(19,24);   
  therm3= c.substring(25,30);
  Levitas=c.substring(30,33);
  CL = c.substring(33,36);  
  CK = c.substring(36,39);
  CB = c.substring(39,42); 

}

//----------------------------
void loop() {
//---------------------------   

  RemoteXY_Handler ();
  // watchdog = "%1%" ;
  s2.print( watchdog  );
   
 readSerialMega();


   therm_1 = b.toFloat();  // Νερά Λέβητα 
   therm_2 = d.toFloat();  // Νερά Μπόϊλερ
 //  therm_4 = e.toFloat();  // Επισρεφόμενα 
   
  // Page1   
   
   if ( Levitas == "L01" ){
    // RemoteXY.text_0 = "Pellet" ;
     strcpy (RemoteXY.text_0 , "Pellet" ) ;
   }
   else if ( Levitas == "L02" ){
     //RemoteXY.text_0 = "Oil" ;
     strcpy (RemoteXY.text_0 , "Oil" ) ;
   }
   // Νερά Λέβητα
   dtostrf(therm_1, 0, 2, RemoteXY.text_0_1);
   RemoteXY.level_0_1 = therm_1 ;
   // Νερά Μπόϊλερ
   dtostrf(therm_2, 0, 2, RemoteXY.text_0_2);
   RemoteXY.level_0_2 = therm_2 ;

  // Page2
   // Θερμοκρασία off Relay από Αισθητήρα Λέβητα 
   dtostrf(therm1.toFloat(), 0, 2, RemoteXY.text_1);
   RemoteXY.level_1 = therm1.toFloat() ; 
   // Θερμοκρασία on  Relay από Αισθητήρα Κυκλοφοριτή
   dtostrf(therm2.toFloat(), 0, 2, RemoteXY.text_2);
   RemoteXY.level_2 = therm2.toFloat() ; 
   // Θερμοκρασία on  Relay από Αισθητήρα Μπόϊλερ
   dtostrf( therm3.toFloat()   , 0, 2, RemoteXY.text_3);
   RemoteXY.level_3 = therm3.toFloat() ; 

   // Επισρεφόμενα
 //  dtostrf( therm_4   , 0, 2, RemoteXY.text_4);
 //  RemoteXY.level_4 = therm_4 ; 

    
  
//  RemoteXY.led_1_r = xromaGreen( CL  ) ;
//  RemoteXY.led_1_g = xromaRed(  CL   ) ; 

//  Λέβητα
  if (CL == "L01") {
   RemoteXY.led_1_r =  0   ;
   RemoteXY.led_1_g =  200     ;
   RemoteXY.led_1_b =  0     ;
  }
  else if (CL == "L02") {
   RemoteXY.led_1_r =  200    ;
   RemoteXY.led_1_b =  0    ;
   RemoteXY.led_1_g =  0  ; 
  }
  // Κυκλοφοριτή
   if (CK == "K01") {
   RemoteXY.led_2_r =  0   ;
   RemoteXY.led_2_g =  200     ;
   RemoteXY.led_2_b =  0     ;
  }
  else if (CK == "K02") {
   RemoteXY.led_2_r =  200    ;
   RemoteXY.led_2_b =  0    ;
   RemoteXY.led_2_g =  0  ; 
  }
  //  Μπόϊλερ
   if (CB == "B01") {
   RemoteXY.led_3_r =  0   ;
   RemoteXY.led_3_g =  200     ;
   RemoteXY.led_3_b =  0     ;
  }
  else if (CB == "B02") {
   RemoteXY.led_3_r =  200    ;
   RemoteXY.led_3_b =  0    ;
   RemoteXY.led_3_g =  0  ; 
  } 
  
delay(500);

}

/*
//-------------------------------
String xromaGreen( String xrom) {
//------------------------------
 uint8_t ligth = 0  ;

  switch (xrom) {
   case "L01" || "K01" || "B01" :
     ligth = 200 ; 
     break;
   case  "L02" || "K02" || "B02" : :
     ligth = 0 ; 
     break;
   default: ;
  }
return( ligth )
}

//-------------------------------
String xromaRed( String xrom) {
//------------------------------
 uint8_t ligth = 0  ;

  switch (xrom) {
   case "L01" || "K01" || "B01" :
     ligth = 0 ; 
     break;
   case  "L02" || "K02" || "B02" : :
     ligth = 200 ; 
     break;
   default: ;
  }
return( ligth )
}

*/
