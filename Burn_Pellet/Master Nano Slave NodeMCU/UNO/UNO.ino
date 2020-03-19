#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

void setup(){
	
	Serial.begin(9600);
	ArduinoUno.begin(2400);

}

void loop(){
	
//	while(ArduinoUno.available()>0){
//	float val = ArduinoUno.parseFloat();
//	 if(ArduinoUno.read()== '\n'){
//	  Serial.println(val);
//	 }
//  }

  

  
//  int i = 12;
//  ArduinoUno.print(i);
//  ArduinoUno.println("\n");
//  Serial.print(i); 

  
  String str = "%11.11%23.00%25.00%60.00%45.00%30.00%99.99" ;
  ArduinoUno.print(str);
 // ArduinoUno.println("\n");
  Serial.println(str);
  


delay(30);
}
