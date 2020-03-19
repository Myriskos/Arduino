/*
   -- Burn_Pellet_wifi --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.5.1 or later version;
     - for iOS 1.4.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,9,0,72,0,253,1,10,161,4,
  131,1,8,55,18,5,1,2,31,206,
  145,207,129,207,135,206,185,206,186,206,
  174,0,131,0,78,56,16,5,4,2,
  31,109,97,110,117,97,108,0,69,0,
  90,2,6,6,1,1,66,132,5,12,
  13,10,1,2,24,66,132,23,12,13,
  10,1,2,24,66,132,44,12,13,10,
  1,2,24,66,132,64,12,13,10,1,
  2,24,66,132,84,12,13,10,1,2,
  24,129,0,27,3,34,5,1,17,206,
  152,206,181,207,129,206,188,206,191,206,
  186,207,129,206,177,207,131,206,175,206,
  181,207,130,0,129,0,2,32,19,3,
  1,17,206,157,206,181,207,129,206,172,
  32,206,155,206,173,206,178,206,183,207,
  132,206,177,0,129,0,22,32,16,3,
  1,17,206,154,206,177,207,133,207,131,
  206,177,206,173,207,129,206,185,206,177,
  0,129,0,39,32,26,3,1,17,206,
  152,206,172,206,187,206,177,206,188,206,
  191,207,130,32,206,154,206,177,207,141,
  207,131,206,183,207,130,32,0,129,0,
  67,32,9,3,1,17,66,111,105,108,
  101,114,0,129,0,80,32,19,3,1,
  17,206,167,207,142,207,129,206,191,207,
  130,32,80,101,108,108,101,116,0,67,
  4,5,25,12,5,1,2,26,11,67,
  4,23,25,12,5,1,2,26,11,67,
  4,44,25,12,5,1,2,26,11,67,
  4,65,25,12,5,1,2,26,11,67,
  4,84,25,12,5,1,2,26,11,65,
  38,7,48,5,5,1,65,38,25,48,
  5,5,1,65,38,45,48,5,5,1,
  65,38,67,48,5,5,1,65,38,86,
  48,5,5,1,129,0,3,43,16,3,
  1,17,206,145,206,189,207,132,206,175,
  207,131,207,132,206,177,207,131,206,183,
  32,0,129,0,22,43,10,3,1,17,
  66,108,111,119,101,114,0,129,0,38,
  43,22,3,1,17,206,154,207,133,206,
  186,206,187,206,191,207,134,206,191,207,
  129,206,183,207,132,206,174,207,130,0,
  129,0,65,43,12,3,1,17,206,154,
  206,191,207,135,206,187,206,175,206,177,
  207,130,0,129,0,84,43,9,3,1,
  17,66,111,105,108,101,114,0,131,0,
  32,54,19,6,2,2,31,115,101,116,
  117,112,0,7,12,9,8,20,5,2,
  2,26,2,2,7,12,9,16,20,5,
  2,2,26,2,2,1,0,49,6,12,
  12,2,2,31,88,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  float edit_1;
  float edit_2;
  uint8_t button_1; // =1 if button pressed, else =0 

    // output variables
  int16_t sound_1; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  int8_t level_1; // =0..100 level position 
  int8_t level_2; // =0..100 level position 
  int8_t level_3; // =0..100 level position 
  int8_t level_4; // =0..100 level position 
  int8_t level_5; // =0..100 level position 
  char text_1[11];  // string UTF8 end zero 
  char text_2[11];  // string UTF8 end zero 
  char text_3[11];  // string UTF8 end zero 
  char text_4[11];  // string UTF8 end zero 
  char text_5[11];  // string UTF8 end zero 
  uint8_t led_1_r; // =0..255 LED Red brightness 
  uint8_t led_1_g; // =0..255 LED Green brightness 
  uint8_t led_2_r; // =0..255 LED Red brightness 
  uint8_t led_2_g; // =0..255 LED Green brightness 
  uint8_t led_3_r; // =0..255 LED Red brightness 
  uint8_t led_3_g; // =0..255 LED Green brightness 
  uint8_t led_4_r; // =0..255 LED Red brightness 
  uint8_t led_4_g; // =0..255 LED Green brightness 
  uint8_t led_5_r; // =0..255 LED Red brightness 
  uint8_t led_5_g; // =0..255 LED Green brightness 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <EEPROM.h>
#include <string.h>
    float  therm_1 ;     
    float  therm_2 ;  
    float  therm_3 ;   
    float  therm_4 ; 
    float  therm_5 ;  
    float  therm_6 ;
    float  therm_7 ;  
     
    String Stherm_1 ;
    String Stherm_2 ;
    String Stherm_3 ;
    String Stherm_4 ;
    String Stherm_5 ;
    String Stherm_6 ;
    String Stherm_7 ;

    String c ;
    String b ;
    String d ;
    bool nn   = false ;
    bool line = true ;
  String ReadString ;
  String St ;
  #include <SoftwareSerial.h>
  SoftwareSerial NodeMCU(D2,D3);

void setup() 
{
//  Serial.begin(9600);
  NodeMCU.begin(2400);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);

  
 /* 
   while (!Serial) {
    ; 
  }  
  */
  RemoteXY_Init (); 

   //  EEPROM.get(10,RemoteXY.edit_1); 
   // if ( RemoteXY.edit_1 > 0 ) {
     EEPROM.get( 11,RemoteXY.edit_1);
     EEPROM.get( 21,RemoteXY.edit_2);
   // }  
   // else {
   //  RemoteXY.edit_1=25; //Αντίσταση
   //  RemoteXY.edit_2=90;
   //  EEPROM.put( 10,RemoteXY.edit_1);
   //  EEPROM.put( 20,RemoteXY.edit_2);
   // }
 
}

void loop() 
{ 
  RemoteXY_Handler ();

  // Αποθήκευση στην EIPROM αν πατηθεί το save  
    if (RemoteXY.button_1){
       EEPROM.put( 11,RemoteXY.edit_1);
       EEPROM.put( 21,RemoteXY.edit_2);
       delay(300);
    }
 
  
   while (line) {
     readSerialNANO();  
   }   
   readSerial();
   Serial.println(ReadString);
   line = true ;
   ReadString = "" ;
   therm_1 = Stherm_2.toFloat();
   therm_2 = Stherm_3.toFloat();
   therm_3 = Stherm_4.toFloat();
   therm_4 = Stherm_5.toFloat();
   therm_5 = Stherm_6.toFloat();
 
  
    // Serial.println("------------------------------");
     dtostrf(therm_1, 0, 1, RemoteXY.text_1);
     RemoteXY.level_1 = therm_1 ;
     dtostrf(therm_2, 0, 1, RemoteXY.text_2);
     RemoteXY.level_2 = therm_2 ;
     dtostrf(therm_3, 0, 1, RemoteXY.text_3);
     RemoteXY.level_3 = therm_3 ;
     dtostrf(therm_4, 0, 1, RemoteXY.text_4);
     RemoteXY.level_4 = therm_4 ;
     dtostrf(therm_5, 0, 1, RemoteXY.text_5);
     RemoteXY.level_5 = therm_5 ;

}
//-------------------------------------------------------------
void readSerialNANO(){    
//-------------------------------------------------------------

// while(NodeMCU.available()>0){
//   float val = NodeMCU.parseFloat();
//   if(NodeMCU.read()== '\n'){
//   Serial.println(val);
//   }
   
//   String ReadString =  NodeMCU.readString() ;
//   ReadString =  NodeMCU.parseFloat();
//   Serial.print(ReadString);
//   Serial.println("----------");  
// }
   
 
    St =  NodeMCU.parseFloat();
    if (St == "11.11") {  nn=true  ;  }
    if (St == "99.99"){  nn=false ; line=false ; } 
    if (nn) {
      ReadString+="%"+St ;
    }
    
}


//-------------------------------------------------------------
void readSerial(){    // αυτο το βαζoυμε στο ESP8266 ΓΙΑ Cloud
//-------------------------------------------------------------
    
       //  ReadString =  "%23.00%25.00%60.00%45.00%30.00%" ;
       //  πχ   %23.00%25.00%60.00%45.00%30.00%
       int delimiter, delimiter_1, delimiter_2, delimiter_3, delimiter_4, delimiter_5, delimiter_6, delimiter_7;
       delimiter =   ReadString.indexOf("%");
       delimiter_1 = ReadString.indexOf("%", delimiter + 1);
       delimiter_2 = ReadString.indexOf("%", delimiter_1 +1);
       delimiter_3 = ReadString.indexOf("%", delimiter_2 +1);
       delimiter_4 = ReadString.indexOf("%", delimiter_3 +1);
       delimiter_5 = ReadString.indexOf("%", delimiter_4 +1);
       delimiter_6 = ReadString.indexOf("%", delimiter_5 +1);
       delimiter_7 = ReadString.indexOf("%", delimiter_6 +1);
     
     
       // Define variables to be executed on the code later by collecting information from the readString as substrings.
        Stherm_1 =  ReadString.substring(delimiter   + 1, delimiter_1) ;     
        Stherm_2 =  ReadString.substring(delimiter_1 + 1, delimiter_2) ;  
        Stherm_3 =  ReadString.substring(delimiter_2 + 1, delimiter_3) ;   
        Stherm_4  = ReadString.substring(delimiter_3 + 1, delimiter_4) ; 
        Stherm_5  = ReadString.substring(delimiter_4 + 1, delimiter_5) ;     
        Stherm_6  = ReadString.substring(delimiter_5 + 1, delimiter_6) ;     
        Stherm_7  = ReadString.substring(delimiter_6 + 1, delimiter_7) ;     
    
//   }
  

}
