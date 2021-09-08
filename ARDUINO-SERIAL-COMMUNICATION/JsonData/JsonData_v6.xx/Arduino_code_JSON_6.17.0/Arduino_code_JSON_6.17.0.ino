//Arduino side code
//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(14, 15);

//Initialisation of DHT11 Sensor
#define DHTPIN 4
DHT dht(DHTPIN, DHT11);
float temp;
float hum;

void setup() {
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  delay(1000);
  Serial.println("Program started");
}

void loop() {

  StaticJsonDocument<1000> doc;

  //Obtain Temp and Hum data
  dht11_func();

  //Assign collected data to JSON Object
  doc["humidity"] = hum;
  doc["temperature"] = temp;

  //Send data to NodeMCU
  serializeJson(doc, nodemcu);
  serializeJsonPretty(doc, nodemcu);
  delay(500);
}

void dht11_func() {

//  hum = dht.readHumidity();
//  temp = dht.readTemperature();
  hum = 60.60;
  temp = 30.55;
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);

}
