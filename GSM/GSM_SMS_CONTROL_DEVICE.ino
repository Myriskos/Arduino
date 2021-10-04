#include "Adafruit_FONA.h"
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

char sendto[21] = "+919043392011"; // Enter your Number here.
String teachmesomethingsms;
String teachmesomethingnumber;
char LEDON[141]= "ON"  ;
char LEDOFF[141]= "OFF";
int led=12;
// We default to using software serial. If you want to use hardware serial
// (because softserial isnt supported) comment out the following three lines 
// and uncomment the HardwareSerial line
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Hardware serial is also possible!
//  HardwareSerial *fonaSerial = &Serial1;

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
// Use this one for FONA 3G
//Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

void setup() {
  while (!Serial);
pinMode(led,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  // make it slow so its easy to read!
  fonaSerial->begin(9600);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));

  // Print SIM card IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }

  fonaSerial->print("AT+CNMI=2,1\r\n");  //set up the FONA to send a +CMTI notification when an SMS is received

  Serial.println("FONA Ready");
  digitalWrite(led,LOW);
}

  
char fonaNotificationBuffer[64];          //for notifications from the FONA
char smsBuffer[250];

void loop() {
  
  char* bufPtr = fonaNotificationBuffer;    //handy buffer pointer
  
  if (fona.available())      //any data available from the FONA?
  {
    int slot = 0;            //this will be the slot number of the SMS
    int charCount = 0;
    //Read the notification into fonaInBuffer
    do  {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer)-1)));
    
    //Add a terminal NULL to the notification string
    *bufPtr = 0;

    //Scan the notification string for an SMS received notification.
    //  If it's an SMS message, we'll get the slot number in 'slot'
    if (1 == sscanf(fonaNotificationBuffer, "+CMTI: " FONA_PREF_SMS_STORAGE ",%d", &slot)) {
      Serial.print("slot: "); Serial.println(slot);
      
      char callerIDbuffer[32];  //we'll store the SMS sender number in here
      
      // Retrieve SMS sender address/phone number.
      if (! fona.getSMSSender(slot, callerIDbuffer, 31)) {
        Serial.println("Didn't find SMS message in slot!");
      }
      Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

        // Retrieve SMS value.
        uint16_t smslen;
        if (fona.readSMS(slot, smsBuffer, 250, &smslen)) { // pass in buffer and max len!
         teachmesomethingsms=smsBuffer;
         teachmesomethingnumber=callerIDbuffer;
         
          if(teachmesomethingnumber==sendto)
         {
           if(teachmesomethingsms==LEDON)
          { digitalWrite(led,HIGH);
            fona.sendSMS(callerIDbuffer, "LED ON");
          }
          else if(teachmesomethingsms==LEDOFF)
          {
            digitalWrite(led,LOW);
            fona.sendSMS(callerIDbuffer, "LED OFF");
          }
          else
           fona.sendSMS(callerIDbuffer, "Send SMS in proper format");
          }
          else
     fona.sendSMS(callerIDbuffer, "You cannot control GSM device. You do not have access");
          }
      fona.deleteSMS(slot);
      fona.print(F("AT+CMGD=1,4\n\r"));
      fona.print(F("AT+CMGDA=\"DEL ALL\""));
           
      // delete the original msg after it is processed
      //   otherwise, we will fill up all the slots
      //   and then we won't be able to receive SMS anymore
      
    }
  }
}
