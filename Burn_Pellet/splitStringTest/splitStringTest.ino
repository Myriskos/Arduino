#include <SoftwareSerial.h>
SoftwareSerial Serial1(3,2);
String str;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
// Αυτό το τρεχουμε στο Arduino
String first  = "Enter";    
String second = "your";
String third  = "string"; 
String five   = "here"'
/*
Serial.println(first  ) ;
Serial.println(second  ) ;
Serial.println(third  ) ;
Serial.println(five  ) ;
*/

// "%Enter%your%string%here%"
str ="%"+first+"%"+second+"%"+third+"%"+five+"%" ;
Serial1.println(str);

delay(1000);

}

//-------------------------------------------------------------
void readSerial(){    // αυτο το βαζoυμε στο ESP8266 ΓΙΑ Cloud
//-------------------------------------------------------------
  if (Serial.available()) {
      String   c =  Serial.readString() ;
      // c  = "%Enter%your%string%here%";
       int delimiter, delimiter_1, delimiter_2, delimiter_3, delimiter_4;
       delimiter = readString.indexOf("%");
       delimiter_1 = readString.indexOf("%", delimiter + 1);
       delimiter_2 = readString.indexOf("%", delimiter_1 +1);
       delimiter_3 = readString.indexOf("%", delimiter_2 +1);
       delimiter_4 = readString.indexOf("%", delimiter_3 +1);
/*            
     Serial.println(delimiter  ) ;   //  0
     Serial.println(delimiter_1 ) ;  //  6
     Serial.println(delimiter_2  ) ; //  11
     Serial.println(delimiter_3 ) ;  //  18
     Serial.println(delimiter_4 ) ;  //  23
     Serial.println("--------------------"  ) ;
*/
     
       // Define variables to be executed on the code later by collecting information from the readString as substrings.
       String first = readString.substring(delimiter + 1, delimiter_1);     //Διαβάζει απο το 1 και σταματάει στο 6
       String second = readString.substring(delimiter_1 + 1, delimiter_2);  //Διαβάζει απο το 7 και σταματάει στο 11 
       String third = readString.substring(delimiter_2 + 1, delimiter_3);   //Διαβάζει απο το 12 και σταματάει στο 18
       String five  = readString.substring(delimiter_3 + 1, delimiter_4);   //Διαβάζει απο το 19 και σταματάει στο 23
  
   }
}
