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

//// RemoteXY select connection mode and include library 
//#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
//
#include <RemoteXY.h>
//
//// RemoteXY connection settings 
//#define REMOTEXY_WIFI_SSID "" //"dbSoft"
//#define REMOTEXY_WIFI_PASSWORD "" // "xVf5nTEN"
//#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
//#define REMOTEXY_CLOUD_PORT 6376
////#define REMOTEXY_CLOUD_TOKEN "16fc05194613e331f4df167717f19ac5"  // ILI9341
//#define REMOTEXY_CLOUD_TOKEN "078a2fb13ad44666194d3dbd124c4332"  // ILI9486  - ILI9327 


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 490 bytes
  { 255,0,0,134,0,227,1,16,13,4,66,132,14,17,14,11,1,2,24,67,
  5,8,30,26,10,1,2,26,11,66,132,14,15,10,8,2,2,24,66,132,
  15,27,10,8,2,2,24,66,132,16,37,10,8,2,2,24,65,112,46,16,
  6,6,2,65,112,47,27,6,6,2,65,112,47,37,6,6,2,129,0,30,
  0,34,5,0,17,206,155,206,181,206,178,206,183,207,132,206,191,207,131,207,
  132,206,172,207,131,206,185,206,191,0,129,0,9,43,25,4,1,17,206,157,
  206,181,207,129,206,172,32,206,155,206,173,206,178,206,183,207,132,206,177,0,
  129,0,40,43,28,4,1,17,206,157,206,181,207,129,206,172,32,206,156,207,
  128,207,140,207,138,206,187,206,181,207,129,0,129,0,58,39,17,4,2,17,
  206,156,207,128,207,140,206,185,206,187,206,181,207,129,0,66,132,79,18,13,
  10,1,2,24,65,96,83,8,6,6,1,67,4,28,16,14,6,2,2,26,
  11,67,4,29,27,14,6,2,2,26,11,67,4,29,37,14,6,2,2,26,
  11,67,4,74,30,24,10,1,2,26,11,129,0,14,9,27,3,1,17,206,
  149,206,189,206,181,207,129,206,179,207,140,207,130,32,206,155,206,173,206,178,
  206,183,207,132,206,177,207,130,32,58,0,67,5,41,8,25,5,1,2,26,
  51,129,0,57,16,20,4,2,17,206,155,206,173,206,178,206,183,207,132,206,
  177,32,32,203,154,67,0,129,0,57,28,27,4,2,17,206,154,207,133,206,
  186,206,187,206,191,207,134,206,191,207,129,206,183,207,132,206,174,0,66,132,
  44,18,13,10,1,2,24,67,5,40,30,26,10,1,2,26,11,131,1,32,
  55,16,5,1,2,31,80,97,103,101,49,0,131,0,58,55,14,5,2,2,
  31,80,97,103,101,50,0,129,0,22,7,55,5,2,17,206,152,206,181,207,
  129,206,188,206,191,206,186,207,129,206,177,207,131,206,175,206,181,207,130,32,
  206,181,206,187,206,173,206,179,207,135,206,191,207,133,0,129,0,71,43,30,
  4,1,17,206,149,207,128,206,185,207,131,207,132,207,129,206,181,207,134,207,
  140,206,188,206,181,206,189,206,177,0 };
  
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
SoftwareSerial s(D5,D6);    // TX-RX 14,15  Serial2
SoftwareSerial s2(D7,D8);   //  TX-RX 16,17  Serial3

#include <ArduinoJson.h>

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
#define JSON  false
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
        #include <WiFiManager.h>
        char con_ssid[32]; //will hold the ssid of the wlan to which it is connectd
        char con_psk[64];  // ^^ private shared key for the wlan (password)
 //------- end auto connect-------------------------

CRemoteXY *remotexy;
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
    
    StartConect();
    StartRemoteXY();
 
}

//------------------------------
void readSerialMega(){
//------------------------------ 
        c =  s.readString() ;
        Serial.println( c  );

        int delimiter0 = c.indexOf('|'); 
        int delimiter1 = c.indexOf('|' ,delimiter0 +1 ); 
        int delimiter2 = c.indexOf('|' ,delimiter1 +1 ); 
        int delimiter3 = c.indexOf('|' ,delimiter2 +1 ); 
        int delimiter4 = c.indexOf('|' ,delimiter3 +1 ); 
        int delimiter5 = c.indexOf('|' ,delimiter4 +1 ); 
        int delimiter6 = c.indexOf('|' ,delimiter5 +1 ); 
        int delimiter7 = c.indexOf('|' ,delimiter6 +1 ); 
        int delimiter8 = c.indexOf('|' ,delimiter7 +1 ); 
        int delimiter9 = c.indexOf('|' ,delimiter8 +1 ); 
        int delimiter10 = c.indexOf('|',delimiter9 +1 );
      
        b =     c.substring(delimiter0 + 1, delimiter1);
        d =     c.substring(delimiter1 + 1, delimiter2);
        therm1= c.substring(delimiter2 + 1, delimiter3);
        therm2= c.substring(delimiter3 + 1, delimiter4); 
        therm3= c.substring(delimiter4 + 1, delimiter5);
        Levitas=c.substring(delimiter5 + 1, delimiter6);
        CL =    c.substring(delimiter6 + 1, delimiter7);
        CK =    c.substring(delimiter7 + 1, delimiter8);
        CB =    c.substring(delimiter8 + 1, delimiter9);
        e =     c.substring(delimiter9 + 1, delimiter10);
   }

//----------------------------
void loop() {
//---------------------------   
// RemoteXY_Handler ();
 remotexy->handler ();
   ESP.wdtDisable();
   ESP.wdtEnable(0);
   ESP.wdtFeed();
// while (true) {}   // για test wdt

  /*
      watchdog = "%1%" ; 
   Αυτο το στέλνει sto MEGA με Serial
   Αν για καποιο λογο το MEGA δεν το πάρει
   θα κανει διακοπή παροχής VCC με Relay  
   Ειναι ενα δεύτερο watchdog εκτός του 
           ESP.wdtDisable()
   */
 // watchdog = "%1%" ;
  s2.print( watchdog  );
    
 # if !JSON 
     readSerialMega();
 #else
     // Resive Data from AeduinoMega Serial2 // 16-17
     // Resive Data from AeduinoMega Serial3 // 14-15
      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(s);
     // if (root == JsonObject::invalid())
     //   return;
     Serial.println("JSON received Data from AeduinoMega Serial3 ");
     root.prettyPrintTo(Serial);
     Serial.println("");
     Serial.println("---------------------xxxxx--------------------");
     delay(1500);
      
     String b = root["therm0"]    ; // Νερά Λέβητα    
     String d = root["therm03"]   ; // Νερά Μπόϊλερ
     //String e = root["therm04"]   ; // Επισρεφόμενα 
     String therm1=root["therm1"] ; // Θερμοκρασία off Relay από Αισθητήρα Λέβητα   
     String therm2=root["therm2"] ; // Θερμοκρασία on  Relay από Αισθητήρα Κυκλοφοριτή  
     String therm3=root["therm3"] ; // Θερμοκρασία on  Relay από Αισθητήρα Μπόϊλερ
     String Levitas=root["Levitas"];
     String CL = root["CL"] ;  
     String CK = root["CK"] ;
     String CB = root["CB"] ; 
 
 #endif
 
   therm_1 = b.toFloat();  // Νερά Λέβητα 
   therm_2 = d.toFloat();  // Νερά Μπόϊλερ
   therm_4 = e.toFloat();  // Επισρεφόμενα 
  // Page1   
   
   if ( Levitas == "L01" ){
      strcpy (RemoteXY.text_0 , "Pellet" ) ;
   }
   else if ( Levitas == "L02" ){
      strcpy (RemoteXY.text_0 , "Oil" ) ;
   }
   // Νερά Λέβητα
   dtostrf(therm_1, 0, 2, RemoteXY.text_0_1);
   RemoteXY.level_0_1 = therm_1 ;
   // Νερά Μπόϊλερ
   dtostrf(therm_2, 0, 2, RemoteXY.text_0_2);
   RemoteXY.level_0_2 = therm_2 ;

   //if(therm_1 < therm_2.toFloat() ){ 
   if(therm_1 > therm_2 ){  
     RemoteXY.led_4_g =   0 ; 
     RemoteXY.led_4_r = 200 ;
     
   }
   else {
     RemoteXY.led_4_g = 200 ;
     RemoteXY.led_4_r =   0 ;
     
   }



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
   dtostrf( therm_4   , 0, 2, RemoteXY.text_4);
   RemoteXY.level_4 = therm_4 ;
   
  

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
  
delay(100); // 500

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
    "078a2fb13ad44666194d3dbd124c4332"                // REMOTEXY_CLOUD_TOKEN
  ));
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
