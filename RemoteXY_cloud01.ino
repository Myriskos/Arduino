/*
   -- Cloud_01 --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.3.1 or later version;
     - for iOS 1.3.5 or later version;
    
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

#include <string.h>
#include<stdio.h>
String tValue;// 
String c ;
String b ;
String d ;



// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "dbSoft"
#define REMOTEXY_WIFI_PASSWORD "xVf5nTEN"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "078a2fb13ad44666194d3dbd124c4332"


// RemoteXY configurate  
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,24,0,103,0,8,13,0,
  66,132,18,26,13,10,2,24,129,0,
  9,4,87,7,17,101,115,112,56,50,
  54,54,45,101,115,112,49,50,32,77,
  111,100,101,32,77,99,117,0,67,4,
  9,38,34,13,2,26,11,66,132,67,
  26,13,10,2,24,67,4,57,38,34,
  13,2,26,11,129,0,13,19,23,6,
  17,206,155,206,173,206,178,206,183,207,
  132,206,177,207,130,0,129,0,66,19,
  17,6,17,66,111,105,108,101,114,0 };
  
// this structure defines all the variables of your control interface 
struct {

    // output variable
  int8_t level_1; // =0..100 level position 
  char text_1[11];  // string UTF8 end zero 
  int8_t level_2; // =0..100 level position 
  char text_2[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

float therm_1 ;
float therm_2 ;

void setup() 
{
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }  
 
  RemoteXY_Init (); 
  
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  readSerial();

//  b = "23.57" ;
//  d= "21.56 " ;
   therm_1 = b.toFloat();
   therm_2 = d.toFloat();
   
   dtostrf(therm_1, 0, 1, RemoteXY.text_1);
   RemoteXY.level_1 = therm_1 ;

   dtostrf(therm_2, 0, 1, RemoteXY.text_2);
   RemoteXY.level_2 = therm_2 ;
  
delay(500);

}


void readSerial(){
  if (Serial.available()) {
      c =  Serial.readString() ;
      b = c.substring(1,6);
      d = c.substring(7);
     
     Serial.println( c  ); 
     Serial.println( b  );
     Serial.print(d  );
  
   }
}
