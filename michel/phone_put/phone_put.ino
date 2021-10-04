#include <Wire.h>
// βιβλιοθηκη για οθονη LCD I2C
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


#include "GreeceGhr.h"

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



/*

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
*/


const int buzzerPin = 10;
int counter = 0;

int buttonState1 ;
int buttonState2 ;
int buttonState3 ;
int buttonState4 ;
int buttonState5 ;

String StrNum = "" ;
//String StrNumArr[] = {"6977996927"};
String lekt   = "" ;







//-----------------
void setup() {
//-----------------
  Serial.begin(9600);

   lcd.init();      /* αρχικοποιηση οθονης */
   lcd.backlight();  /* ενεργοποιηση οπισθιου φωτισμου */
   lcd.home();


  lcd.createChar(0, Gama);
  lcd.createChar(1, Delta);
  lcd.createChar(2, Thita);
  lcd.createChar(3, Lamda);
  lcd.createChar(4, Ksi);
  lcd.createChar(5, Pi);
  lcd.createChar(6, Sigma);
//  lcd.createChar(15, Fi);
//  lcd.createChar(16, Psi);
//  lcd.createChar(17, Omega);
  
  
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

/*  
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
*/

/*

   EEPROM.put( 0,StrNum);
   delay(500);
   EEPROM.get( 0,lekt);
*/

 // epromPut() ;
  epromGet() ;
 

}

void loop() {
   
   Put_Phone() ; 
 
}  


//-----------------------------  
void Put_Phone() {
//-----------------------------
 bool phone_flag = false ;
 int ArrayNumb[] = { 0,1,2,3,4,5,6,7,8,9 } ;
 int Thesi = 0 ;

    lcd.clear() ;
    lcd.setCursor( 0,3 ) ;
    lcd.print( "AT " ) ;  lcd.print( lekt  ) ;
    
 
 for ( int i=0; i< 10 ; ++i   ) {
   lcd.setCursor( i,0 ) ;
   lcd.print( String(ArrayNumb[i]) ) ;
 }
   lcd.setCursor( 12,0 ) ;
   lcd.print( "MAXATO"  ) ;  lcd.write(6);
   lcd.setCursor( 12,1 ) ;
   lcd.print( "MIXA"  ) ;  lcd.write(3); lcd.print( "H"  ) ; lcd.write(6);
   
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
       
      //  Serial.println(  lekt  ) ;
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

     epromPut() ;
     epromGet() ;

/*
  // StrNum = String("6977996927") ;
   EEPROM.put( 0,StrNum);
   delay(500);
   EEPROM.get( 0,lekt);
*/

   
   Serial.println(  "----------------------------- " ) ;
   delay(150) ;
 

 
}


//-----------------
void epromPut() {
//-----------------
struct MyObject {
  char name[11];
};
//myString.toCharArray(buf, len)

char thl[11];
StrNum.toCharArray( thl , 11) ;

 Serial.println(  thl  ) ;
 delay(150) ;

//MyObject customVar = {  "6977996927" };
//EEPROM.put(0, customVar);
EEPROM.put(0, thl );
}
//-----------------
void epromGet() {
//-----------------
struct MyObject {
  char name[11];
};
MyObject customVar;
EEPROM.get(0, customVar);
lekt = customVar.name ;
}
//-----------------
void beep(int note, int duration) {
//-----------------  

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
