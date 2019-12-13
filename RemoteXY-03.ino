/*
   -- hc-06 test01 --
   
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
#include <EEPROM.h>
// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>
#include <math.h>
#include <stdio.h> 
// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>
//αισθητηρας θερμοκρασιας DS18B20
 #define ONE_WIRE_BUS 10 //δηλωση pin δεδομενων στο 10
 OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature
// screen drivers
#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);


// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,39,0,123,0,123,2,8,13,4,
  1,0,3,9,12,12,1,2,31,114,
  101,100,0,1,0,3,27,12,12,1,
  2,31,103,114,101,101,110,0,7,44,
  34,1,15,5,2,2,26,2,2,2,
  0,73,39,20,9,2,2,26,31,31,
  109,111,100,101,49,0,109,111,100,101,
  50,0,7,44,34,7,15,5,2,2,
  26,2,2,67,4,73,2,21,5,1,
  2,26,11,131,1,13,54,16,5,1,
  2,31,206,145,207,129,207,135,206,185,
  206,186,206,174,0,131,0,30,54,14,
  5,2,2,31,83,101,116,117,112,0,
  131,0,45,54,14,5,3,2,31,68,
  105,115,112,108,97,121,0,66,132,21,
  8,18,14,1,2,24,66,132,44,7,
  19,15,1,2,24,67,4,73,8,21,
  5,1,2,26,11,67,4,73,14,21,
  5,1,2,26,11,67,4,73,20,21,
  5,1,2,26,11,67,4,73,26,21,
  5,1,2,26,11,67,4,73,32,21,
  5,1,2,26,11,67,4,73,38,21,
  5,1,2,26,11,67,4,73,44,21,
  5,1,2,26,11,7,44,34,13,15,
  5,2,2,26,2,2,7,44,34,19,
  15,5,2,2,26,2,2,7,44,34,
  25,15,5,2,2,26,2,2,7,44,
  34,31,15,5,2,2,26,2,2,7,
  44,34,37,15,5,2,2,26,2,2,
  129,0,1,2,30,3,2,17,206,145,
  207,129,207,135,206,185,206,186,206,183,
  32,206,152,206,181,207,129,206,188,206,
  191,206,186,207,129,206,177,207,131,206,
  175,206,177,0,129,0,1,8,22,3,
  2,17,206,160,207,129,207,142,207,132,
  206,183,32,206,180,206,185,206,177,207,
  134,206,191,207,129,206,172,0,129,0,
  1,14,25,3,2,17,206,148,206,181,
  207,141,207,132,206,181,207,129,206,183,
  32,206,180,206,185,206,177,207,134,206,
  191,207,129,206,172,0,129,0,1,20,
  21,3,2,17,206,164,207,129,206,175,
  207,132,206,183,32,206,180,206,185,206,
  177,207,134,206,191,207,129,206,172,0,
  129,0,1,26,21,3,2,17,206,164,
  206,173,207,132,206,177,207,129,207,132,
  206,183,32,206,180,206,185,206,177,207,
  134,206,191,207,129,206,172,0,129,0,
  1,32,23,3,2,17,206,165,207,136,
  206,183,206,187,206,174,32,206,152,206,
  181,207,129,206,188,206,191,206,186,207,
  129,206,177,207,131,206,175,206,177,0,
  129,0,1,38,30,3,2,17,206,167,
  206,177,206,188,206,183,206,187,206,174,
  32,206,152,206,181,207,129,206,188,206,
  191,206,186,207,129,206,177,207,131,206,
  175,206,177,0,7,44,82,2,15,5,
  2,2,26,2,2,7,44,82,8,15,
  5,2,2,26,2,2,129,0,68,3,
  6,3,2,17,72,101,97,116,0,129,
  0,68,9,6,3,2,17,67,111,111,
  108,0,67,4,73,50,21,5,1,2,
  26,11,67,4,21,27,17,8,1,2,
  26,11,67,4,45,27,18,8,1,2,
  26,11 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  float edit_1;
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  float edit_2;
  float edit_3;
  float edit_4;
  float edit_5;
  float edit_6;
  float edit_7;
  float edit_8;
  float edit_9;

    // output variable
  char text_1[11];  // string UTF8 end zero 
  int8_t level_1; // =0..100 level position 
  int8_t level_2; // =0..100 level position 
  char text_2[11];  // string UTF8 end zero 
  char text_3[11];  // string UTF8 end zero 
  char text_4[11];  // string UTF8 end zero 
  char text_5[11];  // string UTF8 end zero 
  char text_6[11];  // string UTF8 end zero 
  char text_7[11];  // string UTF8 end zero 
  char text_8[11];  // string UTF8 end zero 
  char text_9[11];  // string UTF8 end zero 
  char text_10[11];  // string UTF8 end zero 
  char text_11[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 11
#define PIN_BUTTON_2 12
//το flag ειναι για να αναβοσβηνη το LED στο PIN 11 12
int flag=0 ;

float therm_T1 ;
float therm_T2 ;
float therm_1 ;
float therm_2 ;
int mode ;
char strn[11] ;

//ορισμος εξοδων ρελε
int Relay_01 = A0 ;
bool Relay_on = false ;


void setup() 
{
  RemoteXY_Init (); 
  mode = 0 ;
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (PIN_BUTTON_2, OUTPUT);
  
sensors.begin(); /* Εκκίνηση της βιβλιοθήκης για DS18B20 */
/*ορισμος pin σε εξοδους για ρελε */
pinMode(Relay_01,OUTPUT);

  /* οριζουμε οι εξοδοι να ειναι σε κατασταση HIGH για να ειναι
     απενεργοποιοιμενα τα ρελε κατα την εκκινηση του κωδικα και 
     σε καθε επανεκκινηση του arduino,ετσι δουλευουν τα πλακετακια 
     των ρελε*/
digitalWrite(Relay_01,HIGH);       
       
       
       EEPROM.get(10,therm_T1); 
       if ( therm_T1 > 0 ) {
          EEPROM.get(10,therm_T1);
          EEPROM.get(20,therm_T2);
          EEPROM.get(30,mode)    ;
       }
       else {
          therm_T1  = 20.00 ;
          therm_T2  = 22.00 ;
          EEPROM.put(10,therm_T1); 
          EEPROM.put(20,therm_T2); 
          EEPROM.put(30,mode );
       }

       
  RemoteXY.switch_1 = mode ;
  RemoteXY.edit_1   = therm_T1 ;
  RemoteXY.edit_2   = therm_T2 ;
 
   ftoa(therm_T1, RemoteXY.text_1, 2) ;
   ftoa(therm_T2, RemoteXY.text_2, 2) ;
  //RemoteXY.text_1= ftoa(therm_T2, strn, 2) ;


       
  // TODO you setup code
 // RemoteXY_Handler ();
}

void loop() 
{ 
  
  RemoteXY_Handler ();
  
  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);
  digitalWrite(PIN_BUTTON_2, (RemoteXY.button_2==0)?LOW:HIGH);
 
  sensors.requestTemperatures ();
  therm_1=(sensors.getTempCByIndex(0));  
  therm_2=(sensors.getTempCByIndex(1));

  RemoteXY.level_1 = therm_1 ;
  RemoteXY.level_2 = therm_2 ;
  
  u8g.firstPage();
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_4x6);
  u8g.drawStr(53,9,"code.google.com");
  
   // TODO you loop code
  // use the RemoteXY structure for data transfer
 
 chech();

 ftoa(therm_T1, RemoteXY.text_1, 2) ;
 ftoa(therm_T2, RemoteXY.text_2, 2) ;

 ftoa(therm_1, RemoteXY.text_10, 2) ;
 ftoa(therm_2, RemoteXY.text_11, 2) ;

     if (therm_1 >  therm_2 ) {
       Relay_on = true ;
       digitalWrite(Relay_01,LOW);
       digitalWrite( PIN_BUTTON_1 , LOW);
       ledAlarm( PIN_BUTTON_2 );
    }
    else if  (therm_1 <  therm_2 )  {
       Relay_on = false ;
       digitalWrite(Relay_01,HIGH);
       digitalWrite( PIN_BUTTON_2 , LOW);
       ledAlarm( PIN_BUTTON_1 );
   }  

  delay(1000);
 
}

void chech() {

 if (RemoteXY.switch_1 == 0){   
     if ( RemoteXY.edit_2 > 30 ) {
      // RemoteXY.edit_1 = 10.7 ;
    //   digitalWrite(PIN_BUTTON_1,HIGH);
    //   digitalWrite(PIN_BUTTON_2,LOW);
       
     }
     else {  
     //  RemoteXY.edit_1 = 20.5 ;
    //   digitalWrite(PIN_BUTTON_2,HIGH);
    //   digitalWrite(PIN_BUTTON_1,LOW);
             
     }
  }

        RemoteXY;
        therm_T1 = RemoteXY.edit_1 ;
        therm_T2 = RemoteXY.edit_2 ;
        mode     = RemoteXY.switch_1 ;
        EEPROM.put(10,therm_T1); 
        EEPROM.put(20,therm_T2);
        EEPROM.put(30,mode    );
        

   
}


//----------------------------------------------------------
void ledAlarm(  int pinled  ) {
    if ( flag == 0){
      digitalWrite( pinled , HIGH);
      flag=1; 
    }
    else if ( flag == 1){
      digitalWrite( pinled , LOW);
      flag=0;  
    }    
return ;
}


// Converts a floating-point/double number to a string. 
void ftoa(float n, char* res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter  
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
}

// Converts a given integer x to string str[].  
// d is the number of digits required in the output.  
// If d is more than the number of digits in x,  
// then 0s are added at the beginning. 
int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
}
// Reverses a string 'str' of length 'len' 
void reverse(char* str, int len) 
{ 
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 
