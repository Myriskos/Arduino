#include <SoftwareSerial.h>
//SoftwareSerial ArduinoResive(3,2);
//SoftwareSerial.Serial3(15,14);
//SoftwareSerial ArduinoResive(19,18);



void setup(){
	
	Serial.begin(9600);
  Serial3.begin(9600);

}

void loop(){
	
//	while(ArduinoResive.available()>0){
 // float val = ArduinoResive.parseFloat();
//	if(ArduinoResive.read()== '\n'){
//	Serial.println(val);

int delimiter, delimiter_1;
String c =  Serial3.readString() ;
delimiter = c.indexOf("%");
delimiter_1 = c.indexOf("%", delimiter + 1);
String first = c.substring(delimiter + 1, delimiter_1);
Serial.println( first  );

  
//	}

   int i = 20;
  Serial3.print(i);
  Serial3.println("\n");
  
  Serial.println(i);
  delay(30);
 
// }
 
}
