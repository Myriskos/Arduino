#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D2
#define SIM800_TX_PIN 2
 
//SIM800 RX is connected to Arduino D3
#define SIM800_RX_PIN 3
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
  Serial.println("Sending SMS...");
   
  //Set SMS format to ASCII
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  serialSIM800.write("AT+CMGS=\"0717447767\"\r\n");
  delay(1000);
   
  //Send SMS content
  serialSIM800.write("Hi This is from TRONICS LK");
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  serialSIM800.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent!");
}
 
void loop() {

  
}
