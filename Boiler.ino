/*
// βιβλιοθηκη για οθονη LCD I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
*/

// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>


//οθονη LCD I2C
//LiquidCrystal_I2C lcd(0x27, 16, 2); //δηλωση πινακων I2C

//αισθητηρας θερμοκρασιας DS18B20
 #define ONE_WIRE_BUS 10 //δηλωση pin δεδομενων στο 10
 OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature

//ορισμος θερμομετρου 1&2
 float therm_1;
 float therm_2;

//ορισμος εξοδων ρελε
 int Relay_01 = A0 ;
 bool Relay_on = false ;
//ορισμος τιμων θερμοκρασιων
 float therm_T1    ;
 float therm_T2  ;
    
//το flag ειναι για να αναβοσβηνη το LED στο PIN 13
 int flag=0 ;

const int ledPinRed   =  11;
const int ledPinGreen =  12;     



void setup() {
 sensors.begin(); /* Εκκίνηση της βιβλιοθήκης για DS18B20 */

  //Input or output?
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);

  /*ορισμος pin σε εξοδους για ρελε */
  pinMode(Relay_01,OUTPUT);

  /* οριζουμε οι εξοδοι να ειναι σε κατασταση HIGH για να ειναι
     απενεργοποιοιμενα τα ρελε κατα την εκκινηση του κωδικα και 
     σε καθε επανεκκινηση του arduino,ετσι δουλευουν τα πλακετακια 
     των ρελε*/
   digitalWrite(Relay_01,HIGH);
   digitalWrite( ledPinRed , HIGH);
   digitalWrite( ledPinGreen , HIGH);
   Serial.begin(9600);

}

void loop() {
    
     sensors.requestTemperatures ();
     therm_1=(sensors.getTempCByIndex(0));  
     therm_2=(sensors.getTempCByIndex(1)); 

     Serial.print( therm_1 );
     Serial.print( " 1.<---->2. " );
	   Serial.println( therm_2 );
       
	if (therm_1 >  therm_2 ) {
       Relay_on = true ;
       digitalWrite(Relay_01,LOW);
       digitalWrite( ledPinRed , LOW);
	     ledAlarm( ledPinGreen );
    }
    else if  (therm_1 <  therm_2 )  {
       Relay_on = false ;
       digitalWrite(Relay_01,HIGH);
       digitalWrite( ledPinGreen , LOW);
	     ledAlarm( ledPinRed );
     }  
 
    
    delay(2000);
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
