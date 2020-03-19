/*
   -- Burn_Pellet --
   
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
  { 255,54,0,99,0,62,4,10,161,4,
  131,1,3,56,18,5,1,2,31,206,
  145,207,129,207,135,206,185,206,186,206,
  174,0,131,0,26,56,22,5,2,2,
  31,83,101,116,117,112,32,85,115,101,
  114,0,131,0,52,55,16,6,3,2,
  31,83,101,114,118,105,115,0,131,0,
  75,55,17,5,4,2,31,109,101,115,
  115,97,103,101,0,69,0,90,2,6,
  6,1,1,66,132,5,12,13,10,1,
  2,24,66,132,23,12,13,10,1,2,
  24,66,132,44,12,13,10,1,2,24,
  66,132,64,12,13,10,1,2,24,66,
  132,84,12,13,10,1,2,24,129,0,
  27,3,34,5,1,17,206,152,206,181,
  207,129,206,188,206,191,206,186,207,129,
  206,177,207,131,206,175,206,181,207,130,
  0,129,0,2,32,19,3,1,17,206,
  157,206,181,207,129,206,172,32,206,155,
  206,173,206,178,206,183,207,132,206,177,
  0,129,0,22,32,16,3,1,17,206,
  154,206,177,207,133,207,131,206,177,206,
  173,207,129,206,185,206,177,0,129,0,
  39,32,26,3,1,17,206,152,206,172,
  206,187,206,177,206,188,206,191,207,130,
  32,206,154,206,177,207,141,207,131,206,
  183,207,130,32,0,129,0,67,32,9,
  3,1,17,66,111,105,108,101,114,0,
  129,0,80,32,19,3,1,17,206,167,
  207,142,207,129,206,191,207,130,32,80,
  101,108,108,101,116,0,129,0,4,10,
  16,3,2,17,206,145,206,189,207,132,
  206,175,207,131,207,132,206,177,207,131,
  206,183,32,0,7,14,27,6,13,6,
  2,2,26,2,1,7,14,27,12,13,
  6,2,2,26,2,1,129,0,3,32,
  19,3,2,17,206,157,206,181,207,129,
  206,172,32,206,155,206,173,206,178,206,
  183,207,132,206,177,0,129,0,3,22,
  20,3,2,17,206,154,207,133,206,186,
  206,187,206,191,207,134,206,191,207,129,
  206,183,207,132,206,174,0,129,0,44,
  7,24,3,2,17,206,145,206,173,207,
  129,206,177,207,130,32,206,145,206,189,
  206,172,206,188,206,177,207,132,206,191,
  207,130,0,129,0,45,13,17,3,2,
  17,206,145,206,173,207,129,206,177,207,
  130,32,206,161,206,191,206,174,207,130,
  46,46,46,46,46,46,46,46,46,46,
  46,46,0,129,0,4,43,15,3,2,
  17,66,108,111,119,101,114,32,111,102,
  102,0,129,0,8,1,28,4,2,39,
  206,152,206,181,207,129,206,188,206,191,
  206,186,207,129,206,177,207,131,206,175,
  206,181,207,130,0,129,0,44,1,28,
  4,2,39,206,160,206,191,207,131,207,
  140,207,132,206,183,207,132,206,177,0,
  129,0,45,27,13,4,2,39,206,167,
  207,129,207,140,206,189,206,191,206,185,
  0,129,0,43,36,33,3,2,17,206,
  154,206,191,207,135,206,187,206,175,206,
  177,207,130,32,206,154,206,177,207,133,
  207,131,207,132,32,206,134,206,189,206,
  177,206,188,206,177,32,0,129,0,43,
  40,28,3,2,17,206,154,206,191,207,
  135,206,187,206,175,206,177,207,130,32,
  206,154,206,177,207,133,207,131,207,132,
  32,206,161,206,191,206,174,0,7,14,
  27,20,13,6,2,2,26,2,1,7,
  14,27,27,13,6,2,2,26,2,1,
  7,14,27,33,13,6,2,2,26,2,
  1,7,14,77,6,13,6,2,2,26,
  2,1,7,14,77,12,13,6,2,2,
  26,2,1,7,14,77,33,13,6,2,
  2,26,2,1,7,14,91,33,13,6,
  2,2,26,2,1,7,14,27,41,13,
  6,2,2,26,2,1,2,0,7,13,
  17,6,3,2,26,31,31,79,78,0,
  79,70,70,0,67,4,5,25,12,5,
  1,2,26,11,67,4,23,25,12,5,
  1,2,26,11,67,4,44,25,12,5,
  1,2,26,11,67,4,65,25,12,5,
  1,2,26,11,67,4,84,25,12,5,
  1,2,26,11,65,38,7,48,5,5,
  1,65,38,25,48,5,5,1,65,38,
  45,48,5,5,1,65,38,67,48,5,
  5,1,65,38,86,48,5,5,1,129,
  0,3,43,16,3,1,17,206,145,206,
  189,207,132,206,175,207,131,207,132,206,
  177,207,131,206,183,32,0,129,0,22,
  43,10,3,1,17,66,108,111,119,101,
  114,0,129,0,38,43,22,3,1,17,
  206,154,207,133,206,186,206,187,206,191,
  207,134,206,191,207,129,206,183,207,132,
  206,174,207,130,0,129,0,65,43,12,
  3,1,17,206,154,206,191,207,135,206,
  187,206,175,206,177,207,130,0,129,0,
  84,43,9,3,1,17,66,111,105,108,
  101,114,0,129,0,44,19,31,3,2,
  17,206,145,206,173,207,129,206,177,207,
  130,32,206,154,206,177,206,184,206,177,
  207,129,32,207,131,207,135,206,172,207,
  129,206,177,207,130,0,7,14,77,18,
  13,6,2,2,26,2,1,1,0,94,
  4,10,10,2,2,31,115,97,118,101,
  0,7,14,77,40,13,6,2,2,26,
  2,1,7,14,91,40,13,6,2,2,
  26,2,1,67,4,5,11,34,6,4,
  2,26,16,67,4,5,24,33,6,4,
  2,26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  float edit_1;
  float edit_2;
  float edit_3;
  float edit_4;
  float edit_5;
  float edit_7;
  float edit_8;
  float edit_10;
  float edit_11;
  float edit_6;
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  float edit_9;
  uint8_t button_1; // =1 if button pressed, else =0 
  float edit_12;
  float edit_13;

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
  char mess_01[16];  // string UTF8 end zero 
  char mess_02[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
/*
#include <SoftwareSerial.h>
SoftwareSerial Serial1(3,2);   // TX-RX
*/

String str;
#include <EEPROM.h>
#define PIN_SWITCH_1 13
//ορισμος εξοδων ρελε
int  Relay_00 = D0 ;
int  Relay_01 = D1 ;
int  Relay_02 = D2 ;
int  Relay_03 = D3 ;
bool Relay_00_on = false ;
bool Relay_01_on = false ;
bool Relay_02_on = false ;
bool Relay_03_on = false ;

 const int buttonPin = 7; //θερμοστάτης
 int buttonState = 0;

float therm_1 ;
float therm_2 ;
float therm_3 ;
float therm_4 ;
float therm_5 ;

unsigned long previousMillisCochlea = 0; 
const long intervalCochlea = 1000;
int ledStateCochlea = LOW; 

unsigned long previousMillisFire = 0; 
const long intervalFire = 1000;
int ledStateFire = LOW; 

void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(9600);
  //Serial1.begin(9600);

  

  if (!RemoteXY.connect_flag){
    Serial.print("no_connect" );
  }

  
  pinMode( buttonPin,INPUT_PULLUP);  
  pinMode (PIN_SWITCH_1, OUTPUT);
  
  pinMode(Relay_00,OUTPUT);
  pinMode(Relay_01,OUTPUT);
  pinMode(Relay_02,OUTPUT);
  pinMode(Relay_03,OUTPUT);

/*
  digitalWrite(Relay_00,HIGH);     
  digitalWrite(Relay_01,HIGH);     
  digitalWrite(Relay_02,HIGH);     
  digitalWrite(Relay_03,HIGH);     
*/
      EEPROM.get(10,RemoteXY.edit_1); 
  if ( RemoteXY.edit_1 > 0 ) {
     EEPROM.get( 10,RemoteXY.edit_1);
     EEPROM.get( 20,RemoteXY.edit_2);
     EEPROM.get( 30,RemoteXY.edit_3);
     EEPROM.get( 40,RemoteXY.edit_4);
     EEPROM.get( 50,RemoteXY.edit_5);
     EEPROM.get( 60,RemoteXY.edit_6);
     EEPROM.get( 70,RemoteXY.edit_7);
     EEPROM.get( 80,RemoteXY.edit_8);
     EEPROM.get( 90,RemoteXY.edit_9);
     EEPROM.get(100,RemoteXY.edit_10);
     EEPROM.get(110,RemoteXY.edit_11);
     EEPROM.get(120,RemoteXY.edit_12);
     EEPROM.get(130,RemoteXY.edit_13);
  }  
  
  else {
     RemoteXY.edit_1=25; //Αντίσταση
     RemoteXY.edit_2=90;
     RemoteXY.edit_3=40; // κυκλοφοριτης
     RemoteXY.edit_4=75; // νερα λεβητα
     RemoteXY.edit_5=65;
     RemoteXY.edit_6=40; // Blower off
     RemoteXY.edit_7=25; // αέρας αναματος
     RemoteXY.edit_8=35; // αέρας ροής 
     RemoteXY.edit_9=40; // αέρας καθαρισμού σχάρας
     RemoteXY.edit_10=5; // κοχλιας καυστήρα αναμα
     RemoteXY.edit_11=8; // κοχλιας καυστήρα αναμα
     RemoteXY.edit_12=2; // κοχλιας καυστήρα ροή
     RemoteXY.edit_13=4; // κοχλιας καυστήρα ροή

     EEPROM.put( 10,RemoteXY.edit_1);
     EEPROM.put( 20,RemoteXY.edit_2);
     EEPROM.put( 30,RemoteXY.edit_3);
     EEPROM.put( 40,RemoteXY.edit_4);
     EEPROM.put( 50,RemoteXY.edit_5);
     EEPROM.put( 60,RemoteXY.edit_6);
     EEPROM.put( 70,RemoteXY.edit_7);
     EEPROM.put( 80,RemoteXY.edit_8);
     EEPROM.put( 90,RemoteXY.edit_9);
     EEPROM.put(100,RemoteXY.edit_10);
     EEPROM.put(110,RemoteXY.edit_11);
     EEPROM.put(120,RemoteXY.edit_12);
     EEPROM.put(130,RemoteXY.edit_13);
          
  }
}

void loop() 
{ 
  RemoteXY_Handler ();

    digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
   // test ALARM  
     if (RemoteXY.switch_1) {   
       RemoteXY.sound_1 = 1001;
    }
    else {
       RemoteXY.sound_1 = 0;
    }
 
   // Αποθήκευση στην EIPROM αν πατηθεί το save  
    if (RemoteXY.button_1){
       EEPROM.put( 10,RemoteXY.edit_1);
       EEPROM.put( 20,RemoteXY.edit_2);
       EEPROM.put( 30,RemoteXY.edit_3);
       EEPROM.put( 40,RemoteXY.edit_4);
       EEPROM.put( 50,RemoteXY.edit_5);
       EEPROM.put( 60,RemoteXY.edit_6);
       EEPROM.put( 70,RemoteXY.edit_7);
       EEPROM.put( 80,RemoteXY.edit_8);
       EEPROM.put( 90,RemoteXY.edit_9);
       EEPROM.put(100,RemoteXY.edit_10);
       EEPROM.put(110,RemoteXY.edit_11);
       EEPROM.put(120,RemoteXY.edit_12);
       EEPROM.put(130,RemoteXY.edit_13);
       RemoteXY.sound_1 = 1001;
       delay(300);
    }
  
//-----------------------------------------------------
     buttonState = digitalRead(buttonPin);
    // Serial.println( buttonState ) ;
     if (buttonState){// εικονικες θερμοκρασίες
        therm_1 = 23 ;//  Νερά Λέβητα
        therm_2 = 25 ;//  Καυσαέρια
        therm_3 = 60 ;//  Θάλαμος καύσης
        therm_4 = 45 ;//  Boiler
        therm_5 = 30 ;//  χώρος Pellet κοχλία
        
         Close_Fire();
         Close_Blower();
         Close_Cochlea();
     } 
     else if(!buttonState){  // Αν ανοίξη ο Θερμοστάτης
        // εικονικες θερμοκρασίες 
        therm_1 = 75 ;//
        therm_2 = 80 ;//
        therm_3 = 260;// 
        therm_4 = 60 ;//
        therm_5 = 40 ;//

        open_Fire();
        open_Blower();
        open_Cochlea();
        
     } 
  
     dtostrf(therm_1, 0, 1, RemoteXY.text_1);
     RemoteXY.level_1 = therm_1 ;

     dtostrf(therm_2, 0, 1, RemoteXY.text_2);
     RemoteXY.level_2 = therm_2 ;

     dtostrf(therm_3, 0, 1, RemoteXY.text_3);
     RemoteXY.level_3 = ( map(therm_3, 0, 500, 0, 100) ) ;

     dtostrf(therm_4, 0, 1, RemoteXY.text_4);
     RemoteXY.level_4 = therm_4 ;
     
     dtostrf(therm_5, 0, 1, RemoteXY.text_5);
     RemoteXY.level_5 = (therm_5) ;     
 str =String('%')+String(therm_1)+String('%')+String(therm_2)+String('%')+ String(therm_3)+String('%')+ String(therm_4)+String('%')+String(therm_5)+String('%')  ;  
 Serial.println(str);
/*  
  //-----------------------------------------------------
  str =String('%')+String(therm_1)+String('%')+String(therm_2)+String('%')+ String(therm_3)+String('%')+ String(therm_4)+String('%')+String(therm_5)+String('%')  ;
  if (Serial1.available()) {
    Serial1.println(str);
   
    char message[] = "SEND TO ESP...." ;
    strcpy (RemoteXY.mess_01, message ) ;
    dtostrf(therm_1, 0, 1, RemoteXY.mess_02);
  //  strcpy (RemoteXY.mess_02[] ,  str  ) ;
  }
  else {
   strcpy ( RemoteXY.mess_01 , "error on Serial") ;
   dtostrf( 99.99, 0, 1, RemoteXY.mess_02);
  }
  Serial.println(str+" SEND TO ESP  ");
  delay(1000);
//---------------------------------------------------------
*/
}




void open_Fire() {
  //digitalWrite(Relay_00,HIGH);
  RemoteXY.led_1_r = 0 ;
  RemoteXY.led_1_g = 200 ;
}

void Close_Fire() {
  //  digitalWrite(Relay_00,LOW);
    RemoteXY.led_1_g = 0 ;
    RemoteXY.led_1_r = 200 ;
}

void open_Blower() {
//  digitalWrite(Relay_01,HIGH);
  RemoteXY.led_2_r = 0 ;
  RemoteXY.led_2_g = 200 ;
}

void Close_Blower() {
  // digitalWrite(Relay_01,LOW);
    RemoteXY.led_2_g = 0 ;
    RemoteXY.led_2_r = 200 ;
}


void open_Cochlea() {
    // Μαυτο τον τρόπο δεν σταματάει η ροη του προγράμματος
    // ενω με την daley()  σταματάει
    unsigned long currentMillisCochlea = millis();
    //Serial.println( currentMillisCochlea ) ;
    int  timer = 0 ;
    if (ledStateCochlea){
       timer = RemoteXY.edit_10 ;  // ο χρονος που ριχνει pellet
    }
    else{
      timer = RemoteXY.edit_11 ;   // ο χρονος αναμονής
    }
  if (currentMillisCochlea - previousMillisCochlea >= (intervalCochlea * timer )  ) {
      previousMillisCochlea = currentMillisCochlea;
    if (ledStateCochlea == LOW) {
      ledStateCochlea = HIGH;
      digitalWrite(Relay_02,HIGH);
      RemoteXY.led_4_g = 200 ;
      RemoteXY.led_4_r = 0 ;
    } else {
      ledStateCochlea = LOW;
      digitalWrite(Relay_02,LOW);
      RemoteXY.led_4_r = 200 ;
      RemoteXY.led_4_g = 0 ;
    }
  }
}

void Close_Cochlea() {
      ledStateCochlea = LOW;
  //    digitalWrite(Relay_02 ,LOW);
      RemoteXY.led_4_r = 200 ;
      RemoteXY.led_4_g = 0 ;
}
