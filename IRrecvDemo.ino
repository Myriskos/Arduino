/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
//---------------------------------------------------
// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>
//αισθητηρας θερμοκρασιας DS18B20
 #define ONE_WIRE_BUS 5 //δηλωση pin δεδομενων στο 5
 OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature
//-----------------------------------------------------
#define DHTPIN 6    // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)



DHT dht(DHTPIN, DHTTYPE);

// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;

float therm_1 ;

unsigned long previousMillis = 0;    // will store last time DHT was updated
// Updates DHT readings every 10 seconds
const long interval = 10000;  
int RECV_PIN = 10;

int ledRED = 11 ;
int ledGREEN = 12 ;

int ledYELLOW = 2 ;
int ledORANGE = 3 ;

IRrecv irrecv(RECV_PIN);
int nkey ; 
decode_results results;

void setup(){
pinMode (ledRED, OUTPUT);
pinMode (ledGREEN,OUTPUT);
pinMode (ledYELLOW,OUTPUT);
pinMode (ledORANGE,OUTPUT);
//---------------------------------------
sensors.begin(); /* Εκκίνηση της βιβλιοθήκης για DS18B20 */
//---------------------------------------
//digitalWrite(ledRED,HIGH);
//digitalWrite(ledGREEN,HIGH);
  Serial.begin(9600);
  dht.begin();
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
   
  Serial.println("Enabled IRin ok");
 
}


void loop() {

//---------------------------------------
  sensors.requestTemperatures ();
  therm_1=(sensors.getTempCByIndex(0));  
  Serial.println(therm_1);
//---------------------------------------
  
  if (irrecv.decode(&results)) {
    nkey = (results.value);
    Serial.println(results.value, HEX);
    Serial.println(nkey);
    irrecv.resume(); // Receive the next value

    if  ( nkey  == 12495) {
       digitalWrite(ledRED,HIGH);
       digitalWrite(ledGREEN,LOW);    
    }
    if  ( nkey==6375 ) {
        digitalWrite(ledRED,LOW);
        digitalWrite(ledGREEN,HIGH);
    } 
    
    if  ( (nkey)  == 26775 ) {
       digitalWrite(ledRED,LOW);
       digitalWrite(ledGREEN,LOW);  
       digitalWrite(ledORANGE,LOW);
       digitalWrite(ledYELLOW,LOW);   
         
    }
    if  ( (nkey)  == 31365 ) {
       digitalWrite(ledRED,HIGH);
       digitalWrite(ledGREEN,HIGH);    
    }

     if  ( (nkey)  == 4335 ) {
       digitalWrite(ledYELLOW,HIGH);
       digitalWrite(ledORANGE,LOW);    
    }

    if  ( (nkey)  == 14535 ) {
       digitalWrite(ledORANGE,HIGH);
       digitalWrite(ledYELLOW,LOW);    
    } 
    if  ( (nkey)  == 23205 ) {
       digitalWrite(ledORANGE,HIGH);
       digitalWrite(ledYELLOW,HIGH);    
    } 
  }



//-----------------------------------------------

unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();
    
    
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float newT = dht.readTemperature(true);
    // if temperature read failed, don't change t value
   
    if (isnan(newT)) {
     // Serial.println("Failed to read temperature from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
     // Serial.println("Failed to read Humidity from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }


//-----------------------------------------------
  
  delay(1000);
}
