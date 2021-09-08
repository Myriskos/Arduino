#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>

SoftwareSerial NodeMCU(D2,D3);

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "dbSoft";
const char *password = "xVf5nTEN";

//const long utcOffsetInSeconds = 19800;
const long utcOffsetInSeconds = 10800; 

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
NTPClient timeClient(ntpUDP, "gr.pool.ntp.org", utcOffsetInSeconds);




void setup(){
	Serial.begin(9600);
	
	NodeMCU.begin(9600);
 	pinMode(D2,INPUT);
	pinMode(D3,OUTPUT);
 
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
  delay ( 500 );
  Serial.print ( "." );
  }

 timeClient.begin();
 
}

void loop(){
    String str = "%" ;
    timeClient.update();
    str += daysOfTheWeek[timeClient.getDay()] ;
    str += ", " ; 
    str += timeClient.getHours();
    str += ":" ; 
    str += timeClient.getMinutes();
    str += ":" ;
    str += timeClient.getSeconds();
    str += "%" ;
    
//    Serial.print(daysOfTheWeek[timeClient.getDay()]);
//    Serial.print(", ");
//    Serial.print(timeClient.getHours());
//    Serial.print(":");
//    Serial.print(timeClient.getMinutes());
//    Serial.print(":");
//    Serial.println(timeClient.getSeconds());
//    //Serial.println(timeClient.getFormattedTime());
      NodeMCU.print(str);
 //     NodeMCU.println("\n");

      Serial.println(str);
      delay(30); 

  
//	int i = 10;
// 	NodeMCU.print(i);
//	NodeMCU.println("\n");
//  Serial.println(i);
//	delay(30);

  float val = NodeMCU.parseFloat();
  if(NodeMCU.read()== '\n'){
  Serial.println(val);
  delay(30);

  }


}
