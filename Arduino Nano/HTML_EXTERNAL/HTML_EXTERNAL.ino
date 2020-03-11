
// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


//--------------------------
#include <string.h>
String tValue;// 
String c ;
String b ;
String d ;

//-------------------------

#ifndef STASSID
#define STASSID "dbSoft" // Your WiFi SSID
#define STAPSK  "xVf5nTEN" //Your WiFi password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
 
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
 
AsyncWebSocketClient * globalClient = NULL;
 
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
 
  if(type == WS_EVT_CONNECT){
 
     Serial.println("Websocket client connection received");
     globalClient = client;
     
  } else if(type == WS_EVT_DISCONNECT){
     
     Serial.println("Websocket client connection finished");
     globalClient = NULL;
 
  }
}

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
// Variable to store the HTTP request
String header;

float ctherm ;
void setup(){
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if(!SPIFFS.begin()){
     Serial.print("An Error has occurred while mounting SPIFFS");
     return;
  }


  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);



//--------------------------------------------------------------------
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ws.html", "text/html");
  });
   
//--------------------------------------------------------------------
 server.on("/ws", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ws.html", "text/html");
  });
server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });  
  server.on("/Photo-0004.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/Photo-0004.jpg", "text/jpg");
  });  
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/main.js", "text/js");
  });  
  server.begin();
}
 
void loop(){
  
     readSerial();
   
   delay(1000);// change this to larger value (1000 or more) if you don't need very often reading

   if(globalClient != NULL && globalClient->status() == WS_CONNECTED){
      //String randomNumber = String(random(0,20));
      String randomNumber = String(b) + "  Boiler:" + String(d) ;
      globalClient->text(randomNumber);
   }
   delay(1000);
}

void readSerial(){
  if (Serial.available()) {
      c =  Serial.readString() ;
      b = c.substring(0,5);
      d = c.substring(5);
     Serial.println( b  );
     Serial.print(d  );
  
   }
}
