const int refresh=3;//3 seconds
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
String tValue;// 
String c ;
String b ;
String d ;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "dbSoft" // Your WiFi SSID
#define STAPSK  "xVf5nTEN" //Your WiFi password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);


void sendTemp() {

  String page = "<!DOCTYPE html>";
  page +="    <head><meta charset=\"utf-8\">" ;
  page +="    <meta http-equiv='refresh' content='";
  page += String(refresh);// how often temperature is read
  page +="'/>";  
  page +="<html>";
  page +="<body>"; 
  page +="<h1>Read from Arduino Serial </h1>";    
  page +="<p style=\"font-size:50px;\">Θερμοκρασία<br/>";  
  page +="<p style=\"color:red; font-size:50px;\">";
  page += tValue;
  page +="</p>";  
  page +="</body>";  
  page +="</html>";  
 server.send(200,  "text/html",page);

}

void handleNotFound() {
 
  String message = "File Not Found";
  message += "URI: ";
  message += server.uri();
  message += "Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "Arguments: ";
  message += server.args();
  message += "";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "";
  }
  server.send(404, "text/plain", message);

}



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    Serial.printf("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  }  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("robojaxDHT")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", sendTemp);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

 
}

void loop() { // run over and over
   readSerial();
  server.handleClient();
  MDNS.update();
  tValue ="Λέβητας "+b+"  Boiler "+d; 
  
}


void readSerial(){
	if (Serial.available()) {
      c =  Serial.readString() ;
      b = c.substring(0,6);
      d = c.substring(6);
     Serial.println( b  );
     Serial.print(d  );
  
   }
}
