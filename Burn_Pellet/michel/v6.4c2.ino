
//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
//#define REMOTEXY_WIFI_SSID "COSMOTE-8130EC"
//#define REMOTEXY_WIFI_PASSWORD "djEhJnRXPXpD55F6"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "f5692435bdeb47b5e695af9ab641f8b7"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,12,0,30,0,10,13,0,
  66,132,39,13,19,15,2,24,67,4,
  34,36,27,8,2,26,11,129,0,45,
  2,7,6,17,42,67,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  int8_t level_1; // =0..100 level position 
  char text_1[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


//βιβλιοθηκη για αποθηκευση στην EEPROM
#include <EEPROM.h>

// βιβλιοθηκη για οθονη LCD I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>

//οθονη LCD I2C
LiquidCrystal_I2C lcd(0x27,20, 4); //δηλωση πινακων I2C

//αισθητηρας θερμοκρασιας DS18B20
#define ONE_WIRE_BUS 12 //δηλωση pin δεδομενων στο 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature

//ορισμος θερμομετρου
float therm_1;
float therm_2;

//ορισμος τιμων θερμοκρασιων
    float therm_T1    ;
    float proti_D ;
    float deuteri_D  ;
    float triti_D  ;
    float alarm_high ;
    float alarm_low ;
    float therm_T2 ;
    float therm_T3 ;
    float therm_T4 ;
    float COOL ;
    float HEAT ;

    //το mode χρησιμοποιητε για τον τροπο λειτουργιας ρελε
    float mode ;
//το flag ειναι για να αναβοσβηνη το LED στο PIN 13
   // int flag=0 ;---------------------------------------------------------
    //το menu χρησιμοποιητε για τα μπουτον του menu   
    int menu=0 ;
    
bool update_Screen = true ;
bool Moto_Run      = true ;
bool exodos        = false ;

//ορισμος εξοδων ρελε
 const int tax_01 = A0 ;
 const int tax_02 = A1 ;
 const int tax_03 = A2 ;
 const int tax_04 = A3 ;
 const int s_xam  = 8 ;
 const int s_yps = 9 ;
 const int cool = 10 ;
 const int heat = 11 ;
 
//δηλωση επαφων των μπουτον menu
const int buttonPin1 = 4; 
const int buttonPin2 = 5; 
const int buttonPin3 = 6; 
const int buttonPin4 = 7; 

//δηλωση επαφων των LED
//const int ledPin0 =  11;
const int ledPin1 =  13;     
//const int ledPin2 =  13;-----------------------------------

//τα μπουτον να ειναι σε κατασταση 0 στην εκκινηση
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
    

void setup() {

RemoteXY_Init ();

 lcd.begin();  /* αρχικοποιηση οθονης */
   lcd.backlight();  /* ενεργοποιηση οπισθιου φωτισμου */

   sensors.begin(); /* Εκκίνηση της βιβλιοθήκης για DS18B20 */

  //οροσμος pin εισοδων μπουτον 
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  //ορισμος pin  εξοδων LED
  //pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  //pinMode(ledPin2, OUTPUT); ---------------------------------

   /*ορισμος pin  εξοδων για ρελε */
  pinMode(tax_01,OUTPUT);
  pinMode(tax_02,OUTPUT);
  pinMode(tax_03,OUTPUT);
  pinMode(tax_04,OUTPUT);
  pinMode(s_xam,OUTPUT);
  pinMode(s_yps,OUTPUT);
  pinMode(cool,OUTPUT) ;
  pinMode(heat,OUTPUT) ;

    /* οριζουμε οι εξοδοι να ειναι σε κατασταση HIGH για να ειναι
     απενεργοποιοιμενα τα ρελε κατα την εκκινηση του κωδικα και 
     σε καθε επανεκκινηση του arduino,ετσι δουλευουν τα πλακετακια 
     των ρελε*/
    digitalWrite(tax_01,HIGH);
    digitalWrite(tax_02,HIGH);
    digitalWrite(tax_03,HIGH);
    digitalWrite(tax_04,HIGH);
    digitalWrite(s_xam,HIGH);
    digitalWrite(s_yps,HIGH);
    digitalWrite(cool,HIGH);
    digitalWrite(heat,HIGH);  

    // Serial.begin(9600);

     
        /*να παρει απο την διευθηνση μνημης 10 την τιμη 
        therm_T1 κατα την εκκηνιση*/
        EEPROM.get(10,therm_T1);
   //  Serial.println( therm_T1 );
   /*εαν η τιμη στη διευθηνση μνημης 10 ειναι μεγαλητερη του 0
    σημενη οτι εχουν μπη τιμες στις διευθηνσης απο προηγουμενη 
    χρηση και να παρη της τιμες απο τις τιμες για proti_D
    ,deuteri_D,triti_D,alarm_high,alarm_low αλλιως να βαλει
    της κατωθη τιμες */

    if ( therm_T1 > 0 ) {
       
        EEPROM.get(10,therm_T1);
          EEPROM.get(20,proti_D);
          EEPROM.get(30,deuteri_D);
          EEPROM.get(40,triti_D);
          EEPROM.get(50,alarm_high);
          EEPROM.get(60,alarm_low);
          EEPROM.get(70,COOL);
          EEPROM.get(80,HEAT);
          EEPROM.get(90,mode);

        }      
      
        else {
          therm_T1  = 20.00 ;
          proti_D  = 2.00 ;
          deuteri_D  = 2.00 ;
          triti_D  = 2.00 ;
          alarm_high = 30.00 ;
          alarm_low = 16.00 ;
          COOL = 28.00 ;
          HEAT = 18.00 ;
          mode = 1.00 ;
          
          EEPROM.put(10,therm_T1); 
          EEPROM.put(20,proti_D);  
          EEPROM.put(30,deuteri_D);  
          EEPROM.put(40,triti_D);
          EEPROM.put(50,alarm_high);
          EEPROM.put(60,alarm_low);
          EEPROM.put(70,COOL);
          EEPROM.put(80,HEAT);
          EEPROM.put(90,mode);
         }

maxatos();
delay(5000);
    /* εκκινηση της void  updateScreen() της κεντρικης  
   προβολης οθονης   */ 
 updateScreen() ; 
 
}

void loop() {
  
RemoteXY_Handler ();
RemoteXY.level_1=therm_1;
dtostrf(therm_1,4,2,RemoteXY.text_1);
   //να διαβαση τις εισοδους των μπουτον
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  delay(200); //μικρη χρονοκαθηστερηση

  /*εαν δεν πατηθει το μπουτον 1 ενεργοποιοιτε το flag 
   για να αναβοσβηνη το LED στο PIN 13*/
 /* if (buttonState1 == LOW) { 
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
  }*/

if (buttonState1 == HIGH) {
    update_Screen = false ;
    Moto_Run = false ;
    exodos = false ;
    digitalWrite(ledPin1, HIGH);
    menu++ ;
     if ( menu > 11 ) {
      menu = 1 ;
   }
    menu_list(menu) ; //η menu_list να περνη την τιμη του menu
  }
  
  if (buttonState2 == HIGH) {

  }
  
  if (buttonState3 == HIGH) {

  } 
  
  if (buttonState4 == HIGH ) {
    
       
      if ( menu < 11 ) {
        // lcd.clear();
         lcd.setCursor(0,3);
         lcd.print("PATHSE     (+) H (-) ");
         //lcd.setCursor(0,3);
         //lcd.print("GIA ALLAGH");
         delay(200); //Small delay
      }

       // Serial.println( " patithike 4 " );
  Setup_therm(menu) ; //η Setup_therm να περνη την τιμη του menu
  }

    if ( update_Screen == true) {  
     updateScreen() ; 
  }     
   
   // ENERGOLOIHSH MOTER 
     if(Moto_Run == true){ 
        motoboot();
      }

}

//----------------------------------------------------------
 void Setup_therm( int  ePr) {
     bool Setup_flag = false;
     if ( ePr == 11  ){
       update_Screen = true ;    
       Setup_flag = true;
       Moto_Run =  true ;
       digitalWrite(ledPin1, LOW);
       return ;
     }
while(!Setup_flag){
          //Read button state (pressed or not pressed?)
        buttonState1 = digitalRead(buttonPin1);
        buttonState2 = digitalRead(buttonPin2);
        buttonState3 = digitalRead(buttonPin3);
        buttonState4 = digitalRead(buttonPin4);
switch(ePr){
   case 1:
    if ( buttonState2 == HIGH   ){
     therm_T1= therm_T1+1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(therm_T1);
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      therm_T1=therm_T1-1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(therm_T1);
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,therm_T1);
          delay (2000);
          EEPROM.get(10,therm_T1);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
         
   }
        break; 

case 2:
    if ( buttonState2 == HIGH   ){
      proti_D=proti_D+1;
      if ( proti_D > 10 ){
    proti_D = 10;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(proti_D);
           lcd.setCursor(19,1);
           lcd.print(" ");
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      proti_D=proti_D-1;
      if ( proti_D < 2 ){
    proti_D = 2;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(proti_D);
           lcd.setCursor(19,1);
           lcd.print(" ");
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,proti_D);
          delay (2000);
          EEPROM.get(20,proti_D);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
         
   }
        
 break;

case 3:
    if ( buttonState2 == HIGH   ){
      deuteri_D=deuteri_D+1;
       if ( deuteri_D > 10 ){
    deuteri_D = 10;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(deuteri_D);
           lcd.setCursor(19,1);
           lcd.print(" ");
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      deuteri_D=deuteri_D-1;
      if ( deuteri_D < 2 ){
    deuteri_D = 2;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(deuteri_D);
           lcd.setCursor(19,1);
           lcd.print(" ");
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,deuteri_D);
          delay (2000);
          EEPROM.get(30,deuteri_D);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
          
   }
        break;

case 4:
    if ( buttonState2 == HIGH   ){
      triti_D=triti_D+1;
      if ( triti_D > 10 ){
    triti_D = 10;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(triti_D);
           lcd.setCursor(19,1);
           lcd.print(" ");
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      triti_D=triti_D-1;
      if ( triti_D < 2 ){
    triti_D = 2;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(triti_D);
           lcd.setCursor(19,1);
           lcd.print(" ");
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,triti_D);
          delay (2000);
          EEPROM.get(40,triti_D);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
         
   }
        break;

case 5:
    if ( buttonState2 == HIGH   ){
      alarm_high=alarm_high+1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(alarm_high);
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      alarm_high=alarm_high-1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(alarm_high);
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,alarm_high);
          delay (2000);
          EEPROM.get(50,alarm_high);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
         
   }
         break;

case 6:
    if ( buttonState2 == HIGH   ){
      alarm_low=alarm_low+1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(alarm_low);
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      alarm_low=alarm_low-1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(alarm_low);
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,alarm_low);
          delay (2000);
          EEPROM.get(60,alarm_low);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
         
   }
         break;

case 7:
    if ( buttonState2 == HIGH   ){
      COOL=COOL+1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(COOL);
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      COOL=COOL-1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(COOL);
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,COOL);
          delay (2000);
          EEPROM.get(70,COOL);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
          
   }
        break;

case 8:
    if ( buttonState2 == HIGH   ){
      HEAT=HEAT+1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(HEAT);
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      HEAT=HEAT-1;
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(HEAT);
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,HEAT);
          delay (2000);
          EEPROM.get(80,HEAT);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
          
   }
        break;

case 9:
    if ( buttonState2 == HIGH   ){
      mode=mode+1;
       if ( mode > 2 ){
    mode = 2;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(mode);
           delay(500) ;
    }
   if ( buttonState3 == HIGH   ){
      mode=mode-1;
      if ( mode < 1 ){
    mode = 1;
  }
      lcd.setCursor(0,1);
           lcd.print("NEA TIMH..");
           lcd.setCursor(15,1);
           lcd.print(mode);
           delay(500) ;
    }
     if ( buttonState4 == HIGH   )
          {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("***** OK ********");
       
          EEPROM.put( (ePr*10) ,mode);
          delay (2000);
          EEPROM.get(90,mode);
          update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
          
   }
        break;
        
case 10:
  if ( buttonState4 == HIGH   ){
     update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
         
  }
 break;
 
  case 11:
    if ( buttonState4 == HIGH   ){
    update_Screen = true ;    
          Setup_flag = true;
          Moto_Run =  true ;
          digitalWrite(ledPin1, LOW);
         
          
  }
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
     lcd.setCursor(0,0);
     lcd.print("1.T1 THERM"  );
     lcd.setCursor(15,0);
     lcd.print(String(therm_T1) );
    break;    
  case  2 : 
   lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("2.T2 THERM"   );
     lcd.setCursor(15,0);
     lcd.print(String(therm_T2) );
     lcd.setCursor(0,2);
     lcd.print("T1<T2...");
     lcd.setCursor(15,2);
     lcd.print(proti_D);
   break;
  case  3 : 
   lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("3.T3 THERM"  );
     lcd.setCursor(15,0);
     lcd.print(String(therm_T3) );     
     lcd.setCursor(0,2);
     lcd.print("T2<T3...");
     lcd.setCursor(15,2);
     lcd.print(deuteri_D);
   break;
  case  4 : 
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("4.T4 THERM"  );
     lcd.setCursor(15,0);
     lcd.print(String(therm_T4) );
     lcd.setCursor(0,2);
     lcd.print("T3<T4...");
     lcd.setCursor(15,2);
     lcd.print(triti_D);     
   break;
  case  5 : 
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("5.HIGH THERM"   );
     lcd.setCursor(15,0);
     lcd.print(String(alarm_high) );
   break;
  case  6 : 
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("6.LOW THERM"  );
     lcd.setCursor(15,0);
     lcd.print(String(alarm_low) );     
   break;
   case  7:
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("7.COOL");
     lcd.setCursor(15,0);
     lcd.print(String(COOL));
   break;
   case  8:
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("8.HEAT");
     lcd.setCursor(15,0);
     lcd.print(String(HEAT));
   break;
   case  9:
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("9.MODE");
     lcd.setCursor(14,0);
     lcd.print(".");
     lcd.setCursor(15,0);
     lcd.print(String(mode));
     lcd.setCursor(17,0);
     lcd.print("   ");
   break;
   case  10 :
     thermokrasion();
   break;  
   case  11 : 
     lcd.clear();
     lcd.setCursor(4,0);
     lcd.print("11.  exit  ");
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
     
/*int eprom;
int ena;
int dio;
int tria;
int tessera;
eprom=EEPROM.get(90,mode);
ena=digitalRead(tax_01);
dio=digitalRead(tax_02);
tria=digitalRead(tax_03);
tessera=digitalRead(tax_04);*/
 /* Serial.print (therm_1);
  Serial.println (therm_2); 
 */
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    THERMOKRASIA    ");
    lcd.setCursor(0,1);
    lcd.print("        ");
    lcd.setCursor(8,1);
    lcd.print(therm_1);
    lcd.setCursor(13,1);
    lcd.print("        ");
    lcd.setCursor(4,2);
    lcd.print("                ");
    lcd.setCursor(8,3);
    lcd.print("   ");
    lcd.setCursor(11,3);
    lcd.print("MODE.");
    lcd.setCursor(16,3);
    lcd.print(mode); 
    lcd.setCursor(18,3);
    lcd.print("  ");
    
  
}

/*----------------------------------------------------*/

void motoboot() {

 // Serial.println( therm_1  ) ;
 // Serial.println( therm  ) ;

  therm_T2 = (therm_T1 + proti_D);
  therm_T3 = (therm_T2 + deuteri_D);
  therm_T4 = (therm_T3 + triti_D);

 if (EEPROM.get(90,mode)==1.00){
    //0 taxytita
    if (therm_1 < therm_T1)
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         lcd.setCursor(0,2);
        lcd.print("____");
    }

    
    // 1 taxytita
    if (therm_1 >= therm_T1 and therm_1 < therm_T2 )
       {
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_01,LOW);
         lcd.setCursor(0,2);
        lcd.print("1___");
    }
        

    // 2 taxytita
    if (therm_1>=therm_T2 and therm_1<therm_T3 )
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_02,LOW);
         lcd.setCursor(0,2);
        lcd.print("_2__");
    }
        

    // 3 taxytita
    if (therm_1>=therm_T3 and therm_1<therm_T4 )
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_03,LOW);
         lcd.setCursor(0,2);
        lcd.print("__3_");
       }
    // 4 taxytita
    if (therm_1>=therm_T4 )
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         delay(2000);
         digitalWrite(tax_04,LOW);
         lcd.setCursor(0,2);
        lcd.print("___4");
    }

  
      // kindinos xamili thermokrasia
      
     // kindinos xamili thermokrasia
      
    if (therm_1<=alarm_low)
      {  digitalWrite(s_xam,LOW);
      lcd.setCursor(4,3);
        lcd.print("sX");
    }
    else 
        {  digitalWrite(s_xam,HIGH);
        lcd.setCursor(4,3);
        lcd.print("  ");
    }

      // kindinos ypsili thermokrasia
      
    if (therm_1>=alarm_high)
      {  digitalWrite(s_yps,LOW);
      lcd.setCursor(6,3);
        lcd.print("sY");
    }
    else
        {digitalWrite(s_yps,HIGH);
        lcd.setCursor(6,3);
        lcd.print("  ");
    }

    //οταν πεφτει η θερμοκρασια ενεργοποιω τη ζεστη
    if (therm_1<= HEAT)
      {  digitalWrite(heat,LOW);
      lcd.setCursor(0,3);
        lcd.print("HT");
    }
    else 
        {  digitalWrite(heat,HIGH);
        lcd.setCursor(0,3);
        lcd.print("  ");
    }

    //οταν ανεβαινη η θερμοκρασια ενεργοποιω το κρυο
     if (therm_1>= COOL)
      {  digitalWrite(cool,LOW);
      lcd.setCursor(2,3);
        lcd.print("CL");
    }
    else 
        {  digitalWrite(cool,HIGH);
        lcd.setCursor(2,3);
        lcd.print("  ");
    }
}

  if (EEPROM.get(90,mode)==2.00){
      //0 taxytita
    if (therm_1 < therm_T1)
       {
         digitalWrite(tax_01,HIGH);
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         lcd.setCursor(0,2);
        lcd.print("____");
    }

    
    // 1 taxytita
    if (therm_1 >= therm_T1 and therm_1 < therm_T2 )
       {
         digitalWrite(tax_02,HIGH);
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_01,LOW);
         lcd.setCursor(0,2);
        lcd.print("1___");
    }
        

    // 2 taxytita
    if (therm_1>=therm_T2 and therm_1<therm_T3 )
       {
         
         digitalWrite(tax_03,HIGH);
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_01,LOW);
         digitalWrite(tax_02,LOW);
         lcd.setCursor(0,2);
        lcd.print("12__");
    }
        

    // 3 taxytita
    if (therm_1>=therm_T3 and therm_1<therm_T4 )
       {
         
         digitalWrite(tax_04,HIGH);
         delay(2000);
         digitalWrite(tax_01,LOW);
         digitalWrite(tax_02,LOW);
         digitalWrite(tax_03,LOW);
         lcd.setCursor(0,2);
        lcd.print("123_");
       }
    // 4 taxytita
    if (therm_1>=therm_T4 )
       {
        delay(2000);
         digitalWrite(tax_01,LOW);
         digitalWrite(tax_02,LOW);
         digitalWrite(tax_03,LOW);
         digitalWrite(tax_04,LOW);
         lcd.setCursor(0,2);
        lcd.print("1234");
    }

  
      // kindinos xamili thermokrasia
      
     // kindinos xamili thermokrasia
      
    if (therm_1<=alarm_low)
      {  digitalWrite(s_xam,LOW);
      lcd.setCursor(4,3);
        lcd.print("sX");
    }
    else 
        {  digitalWrite(s_xam,HIGH);
        lcd.setCursor(4,3);
        lcd.print("  ");
    }

      // kindinos ypsili thermokrasia
      
    if (therm_1>=alarm_high)
      {  digitalWrite(s_yps,LOW);
      lcd.setCursor(6,3);
        lcd.print("sY");
    }
    else
        {digitalWrite(s_yps,HIGH);
        lcd.setCursor(6,3);
        lcd.print("  ");
    }

    //οταν πεφτει η θερμοκρασια ενεργοποιω τη ζεστη
    if (therm_1<= HEAT)
      {  digitalWrite(s_xam,LOW);
      lcd.setCursor(0,3);
        lcd.print("HT");
    }
    else 
        {  digitalWrite(s_xam,HIGH);
        lcd.setCursor(0,3);
        lcd.print("  ");
    }

    //οταν ανεβαινη η θερμοκρασια ενεργοποιω το κρυο
     if (therm_1>= COOL)
      {  digitalWrite(s_xam,LOW);
      lcd.setCursor(2,3);
        lcd.print("CL");
    }
    else 
        {  digitalWrite(s_xam,HIGH);
        lcd.setCursor(2,3);
        lcd.print("  ");
    }
}
}


//---------------------------------------------------------


void thermokrasion(){
  lcd.clear();
  lcd.setCursor(0,0);
      lcd.print("T1=");
      lcd.setCursor(3,0);
      lcd.print(String(therm_T1));
      lcd.setCursor(12,0);
      lcd.print("CL=");
      lcd.setCursor(15,0);
      lcd.print(String(COOL));
      lcd.setCursor(0,1);
      lcd.print("T2=");
      lcd.setCursor(3,1);
      lcd.print(String(therm_T2));
      lcd.setCursor(12,1);
      lcd.print("HT=");
      lcd.setCursor(15,1);
      lcd.print(String(HEAT));
      lcd.setCursor(0,2);
      lcd.print("T3=");
      lcd.setCursor(3,2);
      lcd.print(String(therm_T3));
      lcd.setCursor(12,2);
      lcd.print("sX=");
      lcd.setCursor(15,2);
      lcd.print(String(alarm_low));
      lcd.setCursor(0,3);
      lcd.print("T4=");
      lcd.setCursor(3,3);
      lcd.print(String(therm_T4));
      lcd.setCursor(12,3);
      lcd.print("sY=");
      lcd.setCursor(15,3);
      lcd.print(String(alarm_high));
}

//----------------------------------------------------

void maxatos(){
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("MAXATOS");
  lcd.setCursor(4,2);
  lcd.print("electronics");
  lcd.setCursor(8,3);
  lcd.print("version 6.4");
}
