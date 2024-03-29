/*
 You need to set offsettime for me it is 19800
 Because my timezone is utc+5:30 so
 UTC +5:30=5.5*60*60=19800
 UTC+1=1*60*60=3600
 CALCULATE your timezone and edit it and then upload the code.
*/

#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"

const char *ssid = "***********";
const char *password = "***********";

const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
Serial.begin(115200);

WiFi.begin(ssid, password);

while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "." );
}

timeClient.begin();
}

void loop() {
timeClient.update();

Serial.print(daysOfTheWeek[timeClient.getDay()]);
Serial.print(", ");
Serial.print(timeClient.getHours());
Serial.print(":");
Serial.print(timeClient.getMinutes());
Serial.print(":");
Serial.println(timeClient.getSeconds());
//Serial.println(timeClient.getFormattedTime());

delay(1000);
}