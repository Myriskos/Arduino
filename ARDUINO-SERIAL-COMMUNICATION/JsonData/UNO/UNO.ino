#include <SoftwareSerial.h>
#include <ArduinoJson.h>   // Ver 5.xx

 
void setup() {
Serial.begin(9600);  
Serial3.begin(9600);  // TX3 = 14  RX3 = 15
Serial2.begin(9600);  // TX2 = 16  RX2 = 17
}
 
void loop() {

 // Send Data from ArduinoMega Serial3 to Esp8266 
 StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
// StaticJsonDocument<1000> root;
  root["data1"] = 100;
  root["data2"] = 200;
  root["data3"] = "Serial3";
//if(Serial3.available()>0){
 root.printTo(Serial3);
// serializeJson(root, Serial3);
// }
delay(500);

 // Send Data from ArduinoMega Serial2  to Esp8266 
 StaticJsonBuffer<1000> jsonBufferSerial2;
 JsonObject& rootSerial2 = jsonBufferSerial2.createObject();
 // StaticJsonDocument<1000> rootSerial2;
  rootSerial2["Serial2data1"] = 1000;
  rootSerial2["Serial2data2"] = 2000;
  rootSerial2["Serial2data3"] = "ArduinoMega Serial2";
//if(Serial2.available()>0){
 rootSerial2.printTo(Serial2);
//   serializeJson(rootSerial2, Serial2);
// }
delay(500);


// Resive Data from Esp8266
  StaticJsonBuffer<1000> jsonBuffer2;
  JsonObject& root2 = jsonBuffer2.parseObject(Serial3);
//  StaticJsonDocument<1000> root2;
//  DeserializationError error = deserializeJson(root2, Serial3);
  if (root2 == JsonObject::invalid())
    return;
//
//  while (error) {
//    Serial.println("Invalid JSON Object");
//    delay(500);
//    DeserializationError error = deserializeJson(root2, Serial3);
//  }

 
  Serial.println("JSON received from Esp8266 ");
  root2.prettyPrintTo(Serial);
//  serializeJsonPretty(root2, Serial);
  Serial.println("");
  Serial.print("EspData 1-> ");
  int Espdata1=root2["Espdata1"];
  Serial.print(Espdata1);
  Serial.println("");
  Serial.print("EspData 2-> ");
  int Espdata2=root2["Espdata2"];
  Serial.print(Espdata2);
  Serial.println("");
  Serial.print("EspData 3-> ");
  String Espdata3=root2["Espdata3"];
  Serial.print(Espdata3);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  delay(500);

}
