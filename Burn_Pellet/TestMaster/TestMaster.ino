
#include <math.h>
#include <stdio.h> 

#include <SoftwareSerial.h>
SoftwareSerial Serialwifi(3,2);  // tx rx

#define PIN_BUTTON_1 7

float therm_1=0.00 ;
float therm_2=0.00 ;
float therm_3=0.00 ;
float therm_4=0.00 ;
float therm_5=0.00 ;
String str;
int flag = 0;
void setup() 
{
  
  pinMode (PIN_BUTTON_1, OUTPUT);

 Serial.begin(9600);
 Serialwifi.begin(9600);

  while (!Serialwifi) {
    Serial.println(" while to connect.....");
    ; 
  }  
 
}

void loop() 
{ 
  
 SendString();
//---------------------------------------
  str =String('%')+String(therm_1)+String('%')+String(therm_2)+String('%')+ String(therm_3)+String('%')+ String(therm_4)+String('%')+String(therm_5)+String('%')  ;
 // str =String('T')+String(therm_1)+String('T')+String(therm_2);
  Serial.println(str);
  Serialwifi.println(str);
//---------------------------------------
  delay(1000);
}
//----------------------------------------------------------
void SendString() {
    if ( flag == 0){
       therm_1=11.51;  
       therm_2=21.42;
       therm_3=31.51;  
       therm_4=41.42;
       therm_5=51.42;

       
      flag=1; 
    }
    else if ( flag == 1){
       therm_1=62.57;  
       therm_2=72.49;
       therm_3=82.51;  
       therm_4=92.12;
       therm_5=125.42;
       
      flag=0;  
    }    
return ;
}
 
