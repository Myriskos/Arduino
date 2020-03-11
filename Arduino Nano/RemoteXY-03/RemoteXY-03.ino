
#include <math.h>
#include <stdio.h> 

#include <SoftwareSerial.h>
SoftwareSerial Serial1(3,2);

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




#define PIN_BUTTON_1 11
#define PIN_BUTTON_2 12
//το flag ειναι για να αναβοσβηνη το LED στο PIN 11 12
int flag=0 ;

float therm_T1 ;
float therm_T2 ;
float therm_1 ;
float therm_2 ;
String str;
//ορισμος εξοδων ρελε
int Relay_01 = A0 ;
bool Relay_on = false ;


void setup() 
{
  
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

 Serial.begin(115200);
 Serial1.begin(115200);
 Serial.print(char(169)); // Copyright Symbol
 Serial.println(" Myengineeringstuffs.com");
 delay(500);



}

void loop() 
{ 
  
 
  sensors.requestTemperatures ();
  therm_1=(sensors.getTempCByIndex(0));  
  therm_2=(sensors.getTempCByIndex(1));

//---------------------------------------
  Serial.print("T1: ");
  Serial.print(therm_1); 
  Serial.print("C ");
  Serial.print(" T2: ");
  Serial.print(therm_2); 
  Serial.print(char(176));
  Serial.println("C");
  str =String('T')+String(therm_1)+String('T')+String(therm_2);
  Serial1.println(str);
//---------------------------------------
 
  u8g.firstPage();
 do {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("levitas------boiler");
 // u8g.setFont(u8g_font_profont15r);  // u8g_font_timR14
  u8g.setFont(u8g_font_timR14);
  u8g.setPrintPos(0, 40);
  u8g.print(therm_1);
  u8g.setPrintPos(75,40);
  u8g.print(therm_2);
  u8g.setPrintPos(10, 60);
  u8g.setFont(u8g_font_profont10);
  u8g.print("www.dbsoft.gr");
 } while (u8g.nextPage() ); 
   // TODO you loop code
  // use the RemoteXY structure for data transfer
 
 

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


 
