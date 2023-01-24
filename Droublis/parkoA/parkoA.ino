/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
//////#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

//// RemoteXY connection settings 
//#define REMOTEXY_WIFI_SSID ""
//#define REMOTEXY_WIFI_PASSWORD ""
//#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
//#define REMOTEXY_CLOUD_PORT 6376
//#define REMOTEXY_CLOUD_TOKEN "fe907fb1cef195e8720675bdee8c869e"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 230 bytes
  { 255,0,0,107,0,223,0,16,13,0,129,0,10,4,86,7,17,206,166,207,
  137,207,132,206,191,206,178,206,191,206,187,207,132,206,177,207,138,206,186,206,
  191,32,207,128,206,172,207,129,206,186,206,191,32,206,145,0,70,24,40,15,
  9,9,4,37,4,70,24,18,34,9,9,4,37,4,70,24,34,34,9,9,
  4,37,4,70,24,50,34,9,9,4,37,4,70,24,65,33,9,9,4,37,
  4,129,0,31,27,28,5,17,115,111,108,97,114,32,112,97,110,101,108,115,
  0,129,0,20,36,4,6,17,206,145,0,129,0,36,36,4,6,17,206,146,
  0,129,0,52,36,4,6,17,67,0,129,0,68,35,4,6,17,68,0,67,
  5,6,48,79,6,30,142,51,67,5,17,56,57,6,30,142,51,129,0,80,
  59,17,2,24,206,156,207,133,207,129,206,175,207,131,206,186,206,191,207,130,
  32,206,153,207,137,206,172,206,189,206,189,206,183,207,130,0,129,0,84,56,
  9,3,205,100,98,83,111,102,116,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  uint8_t led_1; // led state 0 .. 1 
  uint8_t led_2; // led state 0 .. 1 
  uint8_t led_3; // led state 0 .. 1 
  uint8_t led_4; // led state 0 .. 1 
  uint8_t led_5; // led state 0 .. 1 
  char text_1[51];  // string UTF8 end zero 
  char text_2[51];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

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
         char con_ssid[32]; //will hold the ssid of the wlan to which it is connectd
         char con_psk[64];  // ^^ private shared key for the wlan (password)
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
 
 // WhatsApp Bot Messages
 #include <ESP8266HTTPClient.h>
 #include <WiFiClient.h>
 #include <UrlEncode.h> 


//----------------Start espnow ---------
#include <espnow.h>

// REPLACE WITH RECEIVER MAC Address
// {0xA4, 0xCF, 0x12, 0xDF, 0x58, 0x21} ;  // SEND A
// {0xA4, 0xCF, 0x12, 0xDF, 0x58, 0x22} ;  // SEND B
// {0xA4, 0xCF, 0x12, 0xDF, 0x48, 0x20} ;  // RECEIVER
// a4:cf:12:df:58:21    SEND A
// a4:cf:12:df:58:22    SEND B
// A4:CF:12:DF:48:20    RECEIVER

 bool parkoA = false ;
 bool trap_A = false ;
 bool trap_B = false ;
 bool trap_C = false ;
 bool trap_D = false ;

 const int buzzerPin = D2;
 const int buttonPin = D1; // 16
 int buttonState = 0;
 int counter = 0;
 bool lSend = false ;

 String mac_esp;
 // Set your new MAC Address
 uint8_t newMACAddress[] = {0xA4, 0xCF, 0x12, 0xDF, 0x48, 0x20}; // RECEIVER

#include "funcs.h"


//String phoneNumber = "+306977996927"; // to WhatsAPP
String apiKey = "1356292"; //to WhatsAPP
//String apiKey = "4055612"; //to WhatsAPP


CRemoteXY *remotexy;

//-----------------
void setup() {
//-----------------  
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode( buttonPin,INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT); 
   
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);  //  
  // Allagh macAdrees sto esp8266
  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);

  StartConect();
  StartRemoteXY();
   
  // Init ESP-NOW
  if (esp_now_init() != 0) {
   Serial.println("Error initializing ESP-NOW");
   return;
  }
   Serial.println("initializing ESP-NOW");
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv); 

}
//----------------- 
void loop() {
//-----------------  
  strcpy (RemoteXY.text_2 ,con_ssid  ) ; 
  
  remotexy->handler ();//RemoteXY
  myData.b = 0;
  buttonState = digitalRead(buttonPin);
  if (buttonState){
    if (parkoA  )  {
       parkoA = false ;
     //  sendMessage( "Η Διακοπη αποκαταστάθηκε στο πάρκο  A"  ,"+306977996927");
       MailYahoo("Η Διακοπη αποκαταστάθηκε στο πάρκο  A <br>Arduino.<br>www.dbsoft.gr");
       if (myData.b >0 ) {
          strcpy(myData.mess, "Send to myriskos@Yahoo.gr");
         }
       else  {
          strcpy(myData.mess, "No Send Message ");
       }
       Serial.println(myData.mess);
       delay(2000);
       strcpy(myData.mess, "Διακοπη αποκαταστάθηκε στο πάρκο A");
       RemoteXY.led_1=0;
       
       Serial.println(myData.mess);
       delay(2000);
    }
    else  {
      lSend    = false ;
      parkoA = false;
      RemoteXY.led_1=0;
    }
    strcpy(myData.mess, "Παροχη ρεύματος οκ");
    delay(2000);
  }
  if (!buttonState  ){  
    strcpy(myData.mess, "Διακοπη στο πάρκο A");
    strcpy( RemoteXY.text_1 , myData.mess );
    parkoA = true;
    RemoteXY.led_1=1;
    delay(2000);
    beep(440, 500);
    beep(600, 500);
    beep(700, 500);
    if (!lSend) {
       MailYahoo("Διακοπη ρεύματος στο πάρκο  A <br>Arduino.<br>www.dbsoft.gr");
     // sendMessage( "Διακοπη ρεύματος στο πάρκο  A"  ,"+306977996927");
      if (myData.b >0 ) {
        strcpy(myData.mess, "Send to myriskos@Yahoo.gr");
        strcpy( RemoteXY.text_1 , myData.mess );
      }
      else {
       strcpy(myData.mess, "No Send Message ");
       strcpy( RemoteXY.text_1 , myData.mess );
      } 
      Serial.println(myData.mess);
      lSend = true ;
      delay(2000);  
    }    
  }
}

//-----------------
void StartRemoteXY(){
//-----------------  
 CRemoteXYComm_WiFi * wifi =  new CRemoteXYComm_WiFi (
    con_ssid,                            // REMOTEXY_WIFI_SSID
    con_psk                                 // REMOTEXY_WIFI_PASSWORD
  );
  
  remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, "");
  
  remotexy->addConnection (new CRemoteXYConnectionServer ( wifi, 
    6377                                      // REMOTEXY_SERVER_PORT
  ));
  
  remotexy->addConnection (new CRemoteXYConnectionCloud ( wifi, 
    "cloud.remotexy.com",                     // REMOTEXY_CLOUD_SERVER 
    6376,                                     // REMOTEXY_CLOUD_PORT
    "fe907fb1cef195e8720675bdee8c869e"                // REMOTEXY_CLOUD_TOKEN
  ));
}

//-----------------
//WhatsApp Bot Messages
void sendMessage(String message , String phoneNumber ){
//-----------------  
  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}
