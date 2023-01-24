/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>


// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char mess[50];
  int b;
  bool panelA ;
  bool panelB ;
  bool panelC ;
  bool panelD ;
} struct_message;

// Create a struct_message called myData
struct_message myData;

//-------auto connect---------------------------
        #include <WiFiManager.h>
        char ssid[32]; //will hold the ssid of the wlan to which it is connectd
        char password[64];  // ^^ private shared key for the wlan (password)
 //------- end auto connect-------------------------



//-------------------EMailSender---------------------------
 #include "Arduino.h"
 #include <EMailSender.h>
 #include <DNSServer.h>
 #include <ESP8266WebServer.h>
 #include <ESP8266WiFiMulti.h>
 ESP8266WiFiMulti WiFiMulti;

 uint8_t connection_state = 0;
 uint16_t reconnect_interval = 10000;

EMailSender emailSend("myriskos@yahoo.gr", "zylnocgpmjiqtdzg"); // 

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);
        Serial.println(nSSID);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}
  
void MailYahoo(){

    connection_state = WiFiConnect(ssid, password);
    if(!connection_state)  // if not connected to WIFI
     {
       Awaits();              // constantly trying to connect
     }
    EMailSender::EMailMessage message;
    message.subject = "Esp8266NodeMCU";
  message.mime = MIME_TEXT_PLAIN;   //
    message.message = "Διακοπή στο PANEL B <br>Arduino.<br>www.dbsoft.gr";
 
    EMailSender::Response resp = emailSend.send("info.dbsoft@gmail.com", message);
   // EMailSender::Response resp2 = emailSend.send("myriskos@yahoo.gr", message);
  
    Serial.println("Sending status: ");

    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
//
//    Serial.println(resp2.status);
//    Serial.println(resp2.code);
//    Serial.println(resp2.desc); 
    
    myData.b = resp.status ;
}

//---------------------end EMailSender--------------------------------------

// REPLACE WITH RECEIVER MAC Address
// {0xA4, 0xCF, 0x12, 0xDF, 0x58, 0x21} ;  // SEND A
// {0xA4, 0xCF, 0x12, 0xDF, 0x58, 0x22} ;  // SEND B
// {0xA4, 0xCF, 0x12, 0xDF, 0x48, 0x20} ;  // RECEIVER

// a4:cf:12:df:58:21    SEND A
// a4:cf:12:df:58:22    SEND B
// A4:CF:12:DF:48:20    RECEIVER

uint8_t broadcastAddress[] = {0xA4, 0xCF, 0x12, 0xDF, 0x48, 0x20}; // RECEIVER
uint8_t newMACAddress[] = {0xA4, 0xCF, 0x12, 0xDF, 0x58, 0x22};


 const int buzzerPin = D2;
 const int buttonPin = D1; // 16
 int buttonState = 0;
 int counter = 0;
 bool lSend = false ;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.print("Delivery success from  ");
    Serial.print(WiFi.macAddress());
    Serial.print("  to  ");
    Serial.println(macToStr(mac_addr));
    
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode( buttonPin,INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT); 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Allagh macAdrees sto esp8266
  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);

  
//------------Start autoConnect-------------- 
    
    WiFiManager wifiManager;
    // wifiManager.resetSettings();
    wifiManager.setTimeout(180); 
 
    if (!wifiManager.autoConnect("WiFi-ESP_A", "12345678")) // credenziali per accedere alla modalità AP
    {
      delay(3000);
      ESP.reset();
      delay(5000);
    }
    WiFi.SSID().toCharArray(ssid, 32);
    WiFi.psk().toCharArray(password, 64);
    
   
    //------------end autoConnect--------------

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  
  // Set values to send
  strcpy(myData.mess, "PANEL B");
  myData.b = 0;
 // myData.panelB = false;
  Serial.println(myData.mess);
  Serial.println(myData.b);
  Serial.println(myData.panelB);
 

  buttonState = digitalRead(buttonPin);
  if (buttonState){
    myData.panelB = false;
    lSend    = false ;
    Serial.println("false");
  }
  else if (!buttonState){
    myData.panelB = true;
    beep(440, 500);
    beep(600, 500);
    beep(700, 500);
    Serial.println("true");
    if (!lSend)    {
        MailYahoo();
         if (myData.b >0 ) {
          strcpy(myData.mess, "Send to myriskos@Yahoo.gr");
          lSend = true ;
         }
         else {
          strcpy(myData.mess, "No Send Message ");
          lSend = true ;
          delay(2000);
         } 
    }    
  }
  

/*
struct point{
    int x;
    int y;
    float z;
};
struct point my_point1;
struct point my_point2 = {2, 5, 3.7};
my_point2.x = 4;
*/
  // Send message via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(2000);
}

//-----------------
String macToStr(const uint8_t* mac){
//-----------------  
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  
  return result;
}

//-----------------
void beep(int note, int duration) {
//-----------------  

 //Play tone on buzzerPin
 tone(buzzerPin, note, duration);
  delay(duration);
 
 //Stop tone on buzzerPin
 noTone(buzzerPin);
 delay(50);
 
 //Increment counter
 counter++;
}
