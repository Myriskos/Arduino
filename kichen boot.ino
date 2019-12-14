

// βιβλιοθηκη για αποθηκευση στην EEPROM
#include <EEPROM.h>
// βιβλιοθηκη για οθονη LCD I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>


//οθονη LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); //δηλωση πινακων I2C

//αισθητηρας θερμοκρασιας DS18B20
#define ONE_WIRE_BUS 10 //δηλωση pin δεδομενων στο 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature

//ορισμος θερμομετρου 1&2
float therm_1;
float therm_2;

//ορισμος εξοδων ρελε
    int tax_01 = A3 ;
    int tax_02 = A2 ;
    int tax_03 = A1 ;
    int tax_04 = A0 ;
    int s_xam  = 11 ;
    int s_yps  = 12 ;

//ορισμος τιμων θερμοκρασιων
    float therm     ;
    float therm_t   ;
    float therm_D1  ;
    float therm_D2  ;
    float therm_D3  ;
    float alarm_high ;
  	float alarm_low ;
   

int flag=0 ;
int menu=0 ;
bool update_Screen = true ;
bool Moto_Run      = true ;
bool exodos        = false ;
const int buttonPin1 = 5; 
const int buttonPin2 = 6; 
const int buttonPin3 = 7; 
const int buttonPin4 = 8; 
const int ledPin0 =  11;
const int ledPin1 =  12;     
const int ledPin2 =  13;
//Variables
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;


//---------------------------------------------------------
void setup() {

  lcd.begin();  /* αρχικοποιηση οθονης */
  lcd.backlight();  /* ενεργοποιηση οπισθιου φωτισμου */
  
  sensors.begin(); /* Εκκίνηση της βιβλιοθήκης για DS18B20 */

  //Input or output?
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);      
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  /*ορισμος pin σε εξοδους για ρελε */
  pinMode(tax_01,OUTPUT);
  pinMode(tax_02,OUTPUT);
  pinMode(tax_03,OUTPUT);
  pinMode(tax_04,OUTPUT);
  pinMode(s_xam,OUTPUT);
  pinMode(s_yps,OUTPUT);


  /* οριζουμε οι εξοδοι να ειναι σε κατασταση HIGH για να ειναι
     απενεργοποιοιμενα τα ρελε κατα την εκκινηση του κωδικα και 
     σε καθε επανεκκινηση του arduino*/
    digitalWrite(tax_01,HIGH);
    digitalWrite(tax_02,HIGH);
    digitalWrite(tax_03,HIGH);
    digitalWrite(tax_04,HIGH);

    Serial.begin(9600);


  
	
	      EEPROM.get(10,therm);
   //  Serial.println( therm );
        if ( therm > 0 ) {
          EEPROM.get(10,therm);
		      EEPROM.get(20,therm_D1);
		      EEPROM.get(30,therm_D2);
			    EEPROM.get(40,therm_D3);
			    EEPROM.get(50,alarm_high);
			    EEPROM.get(60,alarm_low);
	      }		   
      
        else {
		      therm     = 24.00;
          therm_D1  = 2 ;
			    therm_D2  = 4 ;
			    therm_D3  = 6 ;
			    alarm_high = 32.00 ;
			    alarm_low = 22.00 ;
			    EEPROM.put(10,therm);	
		      EEPROM.put(20,therm_D1);	
		      EEPROM.put(30,therm_D2);	
			    EEPROM.put(40,therm_D3);
			    EEPROM.put(50,alarm_high);
			    EEPROM.put(60,alarm_low);
	    }
    
     /*
        Serial.println(  therm ) ;
        Serial.println(  therm_D1);
        Serial.println(  therm_D2);
        Serial.println(  therm_D3);
        Serial.println(  alarm_high);
        Serial.println(  alarm_low);
     */

  /* αρχικη ενδειξη οθονης LCD */
 // sensors.requestTemperatures ();  /* εκκινηση της θερμοκρασιας */
    updateScreen() ; 
   
}
//---------------------------------------------------------
void loop(){
  //Read button state (pressed or not pressed?)
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  delay(200); //Small delay
   
  //If button pressed...
  if (buttonState1 == LOW) { 
    //...ones, turn led on!
    if ( flag == 0){
      digitalWrite(ledPin2, HIGH);
      flag=1; //change flag variable
    }
    //...twice, turn led off!
    else if ( flag == 1){
      digitalWrite(ledPin2, LOW);
      flag=0; //change flag variable again 
    }    
  }
 

  if (buttonState1 == HIGH) {
    update_Screen = false ;
    Moto_Run = false ;
    exodos = false ;
    digitalWrite(ledPin1, HIGH);
    menu++ ;
     if ( menu > 7 ) {
	    menu = 1 ;
	 }
    menu_list(menu) ; 
  }
  
  if (buttonState2 == HIGH) {

  }
  
  if (buttonState3 == HIGH) {

  } 
  
  if (buttonState4 == HIGH ) {
      if ( menu < 7 ) {
         lcd.clear();
         lcd.setCursor(2,0);
         lcd.print("PATHSE + H - GIA ALLAGH");
         delay(200); //Small delay
      }
    
    // Serial.println( " patithike 4 " );
     Setup_therm(menu) ;
  }

    if ( update_Screen == true) {  
     updateScreen() ; 
  }     
   
   // ENERGOLOIHSH MOTER 
     if(Moto_Run == true){ 
      motoboot() ;
     }
}
//----------------------------------------------------------
void Setup_therm( int  ePr) {
     float eprom_Therm ;
     bool Setup_flag = false;
     if ( ePr == 7  ){
       update_Screen = true ;    
       Setup_flag = true;
       Moto_Run =  true ;
       digitalWrite(ledPin1, LOW);
       return ;
     }

     
   EEPROM.get( (ePr*10) ,eprom_Therm);
  // Serial.println( eprom_Therm );   
  while(!Setup_flag){
        //Read button state (pressed or not pressed?)
        buttonState1 = digitalRead(buttonPin1);
        buttonState2 = digitalRead(buttonPin2);
        buttonState3 = digitalRead(buttonPin3);
        buttonState4 = digitalRead(buttonPin4);
     //   Serial.print ( "buttonState2 " ) ;
     //   Serial.println( buttonState2 ) ;  
    if ( buttonState2 == HIGH   )
          {
         eprom_Therm = eprom_Therm + 1 ;
         //  Serial.println( eprom_Therm );
           lcd.clear();
           lcd.setCursor(5,0);
           lcd.print(eprom_Therm);
           digitalWrite(ledPin1, HIGH);
           delay(500) ;      
     }
    
    if ( buttonState3 == HIGH   )
          {
         eprom_Therm = eprom_Therm - 1 ;
         //  Serial.println( eprom_Therm );
           lcd.clear();
           lcd.setCursor(5,0);
           lcd.print(eprom_Therm);
           delay(500) ;      
     }
      
    if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,eprom_Therm);
  
         // Serial.println( "eprom_Therm "  ) ;
         // Serial.println(  ePr*10 ) ;
         // Serial.println( eprom_Therm  ) ;
          
          delay(2000);
      
          EEPROM.get(10,therm);
          EEPROM.get(20,therm_D1);
          EEPROM.get(30,therm_D2);
          EEPROM.get(40,therm_D3);
          EEPROM.get(50,alarm_high);
          EEPROM.get(60,alarm_low);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
          break;
      }
   
  }

}
//----------------------------------------------------------
void menu_list( int mm  ) {
 
 //Serial.print( " epilegmeno menu "  ) ;
 //Serial.println(  mm  ) ;
  
  switch ( mm) {	
  case 1 : 
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("1.allagh THERMOKRASIAs elexoy");
	  break;  	
	case  2 : 
	 lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("2.allagh A diaforas");
	 	 
	 break;
	case  3 : 
	 lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("3.allagh B diaforas");
	 	 
	 break;
	case  4 : 
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("4.allagh C diaforas");
	 break;
	case  5 : 
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("5.allagh LOW THERM ");
	 break;
	case  6 : 
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("6.allagh HIGH THERM ");
	 break;
   case  7 : 
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("7.  exit  ");
  break;
    default: ;
  } 
}


/*---------------------------------------------------------*/
void updateScreen() {

  //   return ;
     
     sensors.requestTemperatures ();
     therm_1=(sensors.getTempCByIndex(0));  
     therm_2=(sensors.getTempCByIndex(1)); 

 /* Serial.print (therm_1);
  Serial.println (therm_2); 
 */
  ///  lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("THERMOKRASIA");
    lcd.setCursor(0,1);
    lcd.print("1");
    lcd.setCursor(1,1);
    lcd.print("=");
    lcd.setCursor(2,1);
    lcd.print(therm_1);
    lcd.setCursor(9,1);
    lcd.print("2");
    lcd.setCursor(10,1);
    lcd.print("=");
    lcd.setCursor(11,1);
    lcd.print(therm);   /* θερμοκρασία EEPROM 10    */


}
/*----------------------------------------------------*/
void motoboot() {

 // Serial.println( therm_1  ) ;
 // Serial.println( therm  ) ;
    //0 taxytita
    if (therm_1 < therm)
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
    }
    // 1 taxytita
    if (therm_1 >= therm and therm_1<(therm+ therm_D1 ))
       {
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_01,LOW);
    }
    // 2 taxytita
    if (therm_1>=(therm+ therm_D1) and therm_1<(therm+therm_D2))
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_02,LOW);
    }
    // 3 taxytita
    if (therm_1>=(therm+therm_D2) and therm_1<(therm+therm_D3))
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_03,LOW);
       }
    // 4 taxytita
    if (therm_1>=(therm+therm_D3))
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         delay(2000);
         digitalWrite(tax_04,LOW);
    }

   /* 
      // kindinos xamili thermokrasia
      
    if (therm_1<=therm_xam)
      {  digitalWrite(s_xam,HIGH);
    }
    else 
        {  digitalWrite(s_xam,LOW);
    }

      // kindinos ypsili thermokrasia
      
    if (therm_1>=therm_yps)
      {  digitalWrite(s_yps,HIGH);
    }
    else
        {digitalWrite(s_yps,LOW);
    }
*/


	
}	
	
