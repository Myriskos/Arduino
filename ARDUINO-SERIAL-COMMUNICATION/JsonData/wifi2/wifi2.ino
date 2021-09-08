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

//  // Resive Data from AeduinoMega Serial3
//  StaticJsonBuffer<1000> jsonBuffer;
//  JsonObject& root = jsonBuffer.parseObject(s);
//  if (root == JsonObject::invalid())
//    return;
// 
//  Serial.println("JSON received Data from AeduinoMega Serial3");
//  root.prettyPrintTo(Serial);
//  Serial.println("");
//  Serial.print("Data 1-> ");
//  int data1=root["data1"];
//  Serial.print(data1);
//  Serial.println("");
//  Serial.print("Data 2-> ");
//  int data2=root["data2"];
//  Serial.print(data2);
//  Serial.println("");
//  Serial.print("Data 3-> ");
//  String data3=root["data3"];
//  Serial.print(data3);
//  Serial.println("");
//  Serial.println("---------------------xxxxx--------------------");
//  delay(500);

  // Resive Data from AeduinoMega Serial2
  StaticJsonBuffer<1000> jsonBuffers2;
  JsonObject& roots2 = jsonBuffers2.parseObject(s);
  if (roots2 == JsonObject::invalid())
    return;
 
  Serial.println("JSON received Data from AeduinoMega Serial2");
  roots2.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Serial2Data 1-> ");
  int Serial2data1=roots2["Serial2data1"];
  Serial.print(Serial2data1);
  Serial.println("");
  Serial.print("Serial2Data 2-> ");
  int Serial2data2=roots2["Serial2data2"];
  Serial.print(Serial2data2);
  Serial.println("");
  Serial.print("Serial2Data 3-> ");
  String Serial2data3=roots2["Serial2data3"];
  Serial.print(Serial2data3);
  Serial.println("");
  Serial.println("-------Resive Data from AeduinoMega Serial2------");
  delay(500);



//  // Send Data to ArduinoMega from  Esp8266 
//
//  StaticJsonBuffer<1000> jsonBuffer2;
//  JsonObject& root2 = jsonBuffer2.createObject();
//  root2["Espdata1"] = 10000;
//  root2["Espdata2"] = 20000;
//  root2["Espdata3"] = "EspdbSoft";
//  root2.printTo(s);
//  delay(500);
// 
}
