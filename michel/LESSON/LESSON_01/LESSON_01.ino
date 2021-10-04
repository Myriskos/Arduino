#include <SoftwareSerial.h>
int delay_GSM = 600;
String number_TEL = "+306977996927";
String TEL_3 = "+306977999999";
String TEL_2 = "+306977988889";
String TEL_adiaforo = "+000000000000"; 
float therm_1 = 23.5 ;



//---------------------------------------
void setup() {
//---------------------------------------  
  Serial.begin(9600);
}



//---------------------------------------
void loop() {
//---------------------------------------  
  relay_on_off("EX.1 : ON");
  relay_on_off("EX.1 : OFF");
  
  relay_on_off("EX.2 : ON");
  relay_on_off("EX.2 : OFF");
  
  gsm_sms_Message("POWER OFF  :" ,   TEL_3   ) ;
  gsm_sms_Message("FIRE  :"      ,   TEL_3   ) ;
  gsm_sms_Message("TEMP.  OK :"  ,   TEL_2   ) ;
}

//---------------------------------------
void relay_on_off( String Ex  ) {
//--------------------------------------  
  delay(delay_GSM);
  Serial.println("AT+CMGS=\"" + number_TEL + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(delay_GSM);
  Serial.print(Ex);   
  delay(delay_GSM);
  Serial.write(26);
}
//-------------------------------------------------
void gsm_sms_Message( String Ex , String Num_TEL     ) {
//-------------------------------------------------  
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial.println("AT+CMGS=\"" + Num_TEL  + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial.println( Ex + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial.write(26);
  }
}
