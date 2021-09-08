
#include <EEPROM.h>
#include <DallasTemperature.h>
#include <OneWire.h>
//αισθητηρας θερμοκρασιας DS18B20
 #define ONE_WIRE_BUS 10 //δηλωση pin 
 OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature

float Stherm   ;
float thermReadDS18B20  ;
const int Relay_01 = A0 ;
bool Relay_on_off = HIGH ;

//------------------------------
void setup() {
//------------------------------  
Serial.begin(115200);
pinMode( Relay_01 ,OUTPUT );  
digitalWrite(Relay_01,HIGH);
EEPROM.get(10,Stherm);
}

//------------------------------
void loop() {
//------------------------------  
  sensors.requestTemperatures ();
  thermReadDS18B20=(sensors.getTempCByIndex(0)); 
   checktherm(  thermReadDS18B20  ) ;
  digitalWrite(Relay_01, Relay_on_off );
  Serial.println( Relay_on_off );
  delay(1000);
  
}

//------------------------------
void checktherm( float ther) {
//------------------------------
  if ( ther <= (Stherm - 0,5) ) {
    Relay_on_off = HIGH ;
  }  
  if ( ther >= (Stherm + 0,5) ) {
    Relay_on_off =  LOW ;
  }
 
}
 
