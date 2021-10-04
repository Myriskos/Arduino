#include <Wire.h>
// βιβλιοθηκη για οθονη LCD I2C
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif



//οθονη LCD I2C
LiquidCrystal_I2C lcd(0x27,20, 4); //δηλωση πινακων I2C

const int buttonPin1 = 7; // Right
const int buttonPin2 = 6; // Up
const int buttonPin3 = 5; // Down
const int buttonPin4 = 4; // Ok
const int buttonPin5 = 3; // Left




const int buzzerPin = 10;
int counter = 0;

int buttonState1 ;
int buttonState2 ;
int buttonState3 ;
int buttonState4 ;
int buttonState5 ;

String lekt   = "" ;
String StrNum = String("6977996927") ;

//-----------------
void setup() {
//-----------------
   Serial.begin(9600);
   EEPROM.put( 100,StrNum);
   delay(500);
   lcd.init();      /* αρχικοποιηση οθονης */
   lcd.backlight();  /* ενεργοποιηση οπισθιου φωτισμου */
   lcd.home();
 
/*    String StrNum1 = "" ;
    EEPROM.get( 100,StrNum1);
    lcd.clear() ;
    lcd.print( "AT " + StrNum1 ) ;
    delay(500) ;
*/

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

  
   
   EEPROM.get( 100,lekt);

}

void loop() {
  lcd.home() ;
  lcd.clear() ;
  String stringTwo = String("This is a string"); 
  lcd.setCursor( 0,3 ) ;
  lcd.print( stringTwo ) ; 
 
    
    lcd.setCursor( 0,0 ) ;
    lcd.print(  lekt)  ; 
    
    lcd.setCursor( 0,1 ) ;
    lcd.print(  "myriskos John")  ; lcd.write(66); 
    delay(1500) ;
    
//   Put_Phone() ; 
 
}  


//-----------------------------  
void Put_Phone() {
//-----------------------------
 bool phone_flag = false ;
 int ArrayNumb[] = { 0,1,2,3,4,5,6,7,8,9 } ;
 String StrNum = "6977996927" ;
 String lekt   = "" ;
 int Thesi = 0 ;
 lcd.clear() ;
String stringTwo = String("This is a string"); 
 lcd.setCursor( 0,3 ) ;
 lcd.print( stringTwo ) ; 
  delay(150) ;
    EEPROM.get( 100,lekt);
    lcd.home() ;
    lcd.setCursor( 0,3 ) ;
    lcd.print( "AT1 " + lekt ) ;
    
 
 for ( int i=0; i< 10 ; ++i   ) {
   lcd.setCursor( i,0 ) ;
   lcd.print( String(ArrayNumb[i]) ) ;
  }
  // lcd.print( " M.MAXATOS" )   ;// lcd.write(243);
   lcd.setCursor( 0,2 ) ;
   lcd.print( StrNum  ) ;
  
  lcd.setCursor( Thesi,1 ) ;
  lcd.print( "*" ) ;

     while(!phone_flag){
        buttonState1 = digitalRead(buttonPin1);
        buttonState2 = digitalRead(buttonPin2);
        buttonState3 = digitalRead(buttonPin3);
        buttonState4 = digitalRead(buttonPin4);
        buttonState5 = digitalRead(buttonPin5);
        Serial.println(  lekt  ) ;
        
        delay(150) ;
        
        if (!buttonState1) {
          lcd.setCursor( Thesi,1 ) ;
          lcd.print( " " ) ;
          if (Thesi < 9){ ; ++Thesi ; }
          lcd.setCursor( Thesi,1 ) ;
          lcd.print( "*" ) ;
        }

        if (!buttonState5) {
          lcd.setCursor( Thesi,1 ) ;
          lcd.print( " " ) ;
          if ( Thesi > 0  ){ ; --Thesi ; }
          lcd.setCursor( Thesi,1 ) ;
          lcd.print( "*" ) ;
        }
        
        if (!buttonState3) {
            StrNum = StrNum + String(ArrayNumb[Thesi]) ;
            lcd.setCursor( 0,2 ) ;
            lcd.print( StrNum ) ;
        }
        if (!buttonState2) {
            int lenS= StrNum.length()  ;
            StrNum =  StrNum.substring(0 ,( lenS-1 ) ) ;
            lcd.setCursor( 0,2 ) ;
            lcd.print( StrNum+" " ) ;
        }
	      if (!buttonState4) {
            phone_flag = true   ;
            beep(440, 500);
                    
 	  	  }	
	
     }
   //εγγραφη στην eeprom 

    EEPROM.put( 100,StrNum);
    delay(500);
    EEPROM.get( 100,StrNum);
    lcd.clear() ;
    lcd.print( "AT " + StrNum ) ;
    delay(500) ;

return ;
 
}


void beep(int note, int duration)
{
 //Play tone on buzzerPin
 tone(buzzerPin, note, duration);
  delay(duration);
 
 //Stop tone on buzzerPin
 noTone(buzzerPin);
 delay(50);
 
 //Increment counter
 counter++;
}
 


//-----------------------------  
void Print_chraracter() {
//-----------------------------

/*
 lcd.printByte(224);
 // α  224
 // β  226
 // ε  227
 // μ  228 
 // σ  229
 // ρ  230
 // φ  236
 // Ω  241
 // Σ  243
 // π  244
*/

 /*  
  for ( int i=65; i< 100 ; ++i   ) {
   lcd.printByte(i);
  }
  
   delay(500);
*/


/*
  int row = 0 ;
  int col = 0 ;
  lcd.setCursor(0,row );
  for ( int i=224; i< 304 ; ++i    ) {
    ++col ;
    if (col > 20){
      col =0 ;
      ++row ;
      lcd.setCursor(0,row );
    }  
    lcd.printByte(i);
  }
 */

} 
