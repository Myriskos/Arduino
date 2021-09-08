#include <SoftwareSerial.h>
SoftwareSerial s(D2,D3);
#include <ArduinoJson.h>
 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
   while (!Serial) continue;
 }
 
void loop() {

  // Resive Data from AeduinoMega Serial3
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;

//  StaticJsonDocument<1000> root;
//  DeserializationError error = deserializeJson(root,s);

//   while (error) {
//    Serial.println("Invalid JSON Object");
//    delay(500);
//    DeserializationError error = deserializeJson(root, s);
//  }
 
  Serial.println("JSON received Data from AeduinoMega Serial3");
  root.prettyPrintTo(Serial);
 // serializeJson(root, s);
  Serial.println("");
  Serial.print("Data 1-> ");
  int data1=root["data1"];
  Serial.print(data1);
  Serial.println("");
  Serial.print("Data 2-> ");
  int data2=root["data2"];
  Serial.print(data2);
  Serial.println("");
  Serial.print("Data 3-> ");
  String data3=root["data3"];
  Serial.print(data3);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  delay(500);


  // Send Data to ArduinoMega from  Esp8266 

  StaticJsonBuffer<1000> jsonBuffer2;
  JsonObject& root2 = jsonBuffer2.createObject();
//  StaticJsonDocument<1000> root2;
  root2["Espdata1"] = 1000;
  root2["Espdata2"] = 2000;
  root2["Espdata3"] = "EspdbSoft";
  root2.printTo(s);
 // serializeJson(root2,s);
  delay(500);
 
}
