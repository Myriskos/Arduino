//#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#include "Greek_Sigismundus8pt7b.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial SerialMega(16,17);   // TX-RX 5,6

/*
  MEGA        ESP8266 NODE MCU
  TX16 -----> D6
  RX17 -----> D5

  SoftwareSerial SerialMega(16,17);    // TX-RX 5,6   ΣΤΟ MEGA
  SoftwareSerial ArduinoMega(D5,D6);   // TX-RX 16,17 ΣΤΟ ESP 
  
*/ 
 
// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>
//αισθητηρας θερμοκρασιας DS18B20
 #define ONE_WIRE_BUS  40   //D3 //δηλωση pin 
 OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature

#define MINPRESSURE 200
#define MAXPRESSURE 1000
#define DPI 141 // Approximate res. of Adafruit 2.8" TFT
// ALL Touch panels and wiring is DIFFERENT
//--------------------------------

// COPY-PASTE from Serial Terminal:
//const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9325
//const int TS_LEFT=893,TS_RT=108,TS_TOP=931,TS_BOT=120;
const int XP=6,XM=A2,YP=A1,YM=7; //240x400 ID=0x9327
const int TS_LEFT=915,TS_RT=135,TS_TOP=956,TS_BOT=113;

//-------------------------------------------------
//TouchScreen.h GFX Calibration
//Making all control and bus pins INPUT_PULLUP
//Typical 30k Analog pullup with corresponding pin
//would read low when digital is written LOW
//e.g. reads ~25 for 300R X direction
//e.g. reads ~30 for 500R Y direction
//
//Testing : (A1, D7) = 28
//Testing : (A2, D6) = 23
//ID = 0x9327
//
//cx=881 cy=938 cz=475  X, Y, Pressure
//cx=882 cy=526 cz=589  X, Y, Pressure
//cx=886 cy=131 cz=667  X, Y, Pressure
//cx=530 cy=933 cz=354  X, Y, Pressure
//cx=527 cy=137 cz=583  X, Y, Pressure
//cx=178 cy=934 cz=222  X, Y, Pressure
//cx=169 cy=534 cz=437  X, Y, Pressure
//cx=157 cy=137 cz=571  X, Y, Pressure
//
//*** COPY-PASTE from Serial Terminal:
//const int XP=6,XM=A2,YP=A1,YM=7; //240x400 ID=0x9327
//const int TS_LEFT=915,TS_RT=135,TS_TOP=956,TS_BOT=113;
//
//PORTRAIT  CALIBRATION     240 x 400
//x = map(p.x, LEFT=915, RT=135, 0, 240)
//y = map(p.y, TOP=956, BOT=113, 0, 400)
//
//LANDSCAPE CALIBRATION     400 x 240
//x = map(p.y, LEFT=956, RT=113, 0, 400)
//y = map(p.x, TOP=135, BOT=915, 0, 240)


//--------------------------------------------------
float therm0 = 22.50 ; 
float therm03 = 22.50 ;  //  Νερά Μπόϊλερ
float therm1 = 75.50 ; 
float therm2 = 40.50 ; 
float therm3 = 55.50 ;
int MenuCount = 1 ;


//ορισμος εξοδων ρελε
int  Relay_01 = A8 ;
int  Relay_02 = A9 ;
int  Relay_03 = A10 ;
int  Relay_04 = A11 ;     // του boiller

bool Relay_01_on = false ;
bool Relay_02_on = false ;
bool Relay_03_on = false ;
bool Relay_04_on = false ;


 bool Up   = true  ;
 bool Down = false ;

 bool Pellet_on  ;
 bool Oil_on     ;
 String strSendSereal;


 String Levitas = "L01" ;   // L01 = "Pellet"  L02="Oil"
 String CL , CK , CB ;      // CL =Λέβητα , CK = Κυκλοφοριτή , CB = Μπόϊλερ

 unsigned long previousMillis = 0; 
 const    long intervalDisp = 100;
 int  timer = 10 ;

 unsigned long previousMillis2 = 0; 
 const    long intervalDisp2 = 100;
 int  timer2 = 10 ;

//----------------------------------
 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button  Pellet_btn , Oil_btn  ,  therm1_btn , therm2_btn , therm3_btn , on_btn, off_btn , exit_btn , mode_btn , NextMenu_btn , PreviewMenu_btn ;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool dispMenu = true ;

bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
      //  pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
      //  pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());

       //PORTRAIT  CALIBRATION     240 x 320
       pixel_x = map(p.x, TS_LEFT, TS_RT, 0, 240) ;
       pixel_y = map(p.y, TS_TOP , TS_BOT,0, 400) ;

    }
    return pressed;
}

#define BLACK   0x0000
//#define BLUE    0x001F
int BLUE = tft.color565(50, 50, 255);
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BLUEBAR_MINX 180
#define BAR_MINY 30

#include "menu1.h"
#include "menu2.h"

//--------------------------------------------
void setup(void)
//--------------------------------------------
{
  
    SerialMega.begin(9600);
//      while (!SerialMega) {
//      Serial.print( "."  );  
//   }  
    
    Serial.begin(9600);
//     while (!Serial) {
//        ;  
//   }  
   
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");

   // ID = 0x9325; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            // 0= PORTRAIT  3 = LANDSCAPE
    tft.fillScreen(BLACK);

    pinMode(Relay_01,OUTPUT);
    pinMode(Relay_02,OUTPUT);
    pinMode(Relay_03,OUTPUT); 
    pinMode(Relay_04,OUTPUT); 

    digitalWrite(Relay_01,HIGH);     
    digitalWrite(Relay_02,HIGH);     
    digitalWrite(Relay_03,HIGH);      
    digitalWrite(Relay_04,HIGH);      
     
    EEPROM.get(10,therm1); 
    if ( therm1 > 0 ) {
     EEPROM.get( 10,therm1);
     EEPROM.get( 20,therm2);
     EEPROM.get( 30,therm3);
     EEPROM.get( 40,Pellet_on);
     EEPROM.get( 50,Oil_on);
    } 
    else { 
     therm1 = 65.00 ; 
     therm2 = 40.00 ; 
     therm3 = 45.00 ;
     Pellet_on = true ;
     Oil_on    = false ; 
     EEPROM.put( 10,therm1);
     EEPROM.put( 20,therm2);
     EEPROM.put( 30,therm3);
     EEPROM.put( 40,Pellet_on);
     EEPROM.put( 50,Oil_on);
    }

bootSreen() ;
   
}

//--------------------------------------------
void loop(void){
//--------------------------------------------
   
  switch(MenuCount){
   case 1:
      menu1();
      break;
   case 2:
      menu2();
      break;   
  }
}

//--------------------------------------------
float therm_setup( String HeadMsg , float therm ){
//--------------------------------------------

    bool save_therm = true ;
    tft.fillScreen(BLACK);

    on_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "+", 3);
    off_btn.initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "-", 3);
    exit_btn.initButton(&tft, 120, 250, 150, 40, WHITE, CYAN, BLACK, "Save", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    exit_btn.drawButton(false);

   header1(HeadMsg);

  tft.fillRect(40, 80, 160, 80, RED);
  while (save_therm) {  
    tft.setCursor(50,100);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    tft.print(  therm  );
    
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    exit_btn.press(down && exit_btn.contains(pixel_x, pixel_y));
     
   
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (off_btn.justReleased())
        off_btn.drawButton();
    if (exit_btn.justReleased())
        exit_btn.drawButton();
   
        
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, RED);
        //  therm++ ;
        therm = therm +0.50 ;
    }
    if (off_btn.justPressed()) {
          off_btn.drawButton(true);
          tft.fillRect(40, 80, 160, 80, RED);
          //therm-- ;
          therm = therm -0.50 ;
    }
    if (exit_btn.justPressed()) {
        exit_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, MAGENTA);
        save_therm = false ;
    }
  }
  tft.fillScreen(BLACK);
  dispMenu = true ;

 return( therm ) ;

}

//--------------------------------------------
float mode_setup( ){
//--------------------------------------------

    bool save_therm = true ;
    tft.fillScreen(BLACK);

    Pellet_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "Pellet", 2);
    Oil_btn.initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK," Oil  ", 2);
    exit_btn.initButton(&tft, 120, 250, 150, 40, WHITE, CYAN, BLACK, "Save", 2);
    Pellet_btn.drawButton(false);
    Oil_btn.drawButton(false);
    exit_btn.drawButton(false);

   header1("mode_setup");

  tft.fillRect(40, 80, 160, 80, RED);
  while (save_therm) {  
    tft.setCursor(50,100);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    
    if (Pellet_on){
     tft.print(  "Pellet"  );
     Levitas = "L01" ;
     Oil_on = false ;
     digitalWrite(Relay_02,HIGH);
     digitalWrite(Relay_01,LOW);
    }
    else if (Oil_on) {
     tft.print(  " Oil  "  );
     Levitas = "L02" ;
     Pellet_on = false ;
     digitalWrite(Relay_01,HIGH);
     digitalWrite(Relay_02,LOW);
    }
    else {
     tft.print(  " No Mode "  ); 
    }
    bool down = Touch_getXY();
    Pellet_btn.press(down && Pellet_btn.contains(pixel_x, pixel_y));
    Oil_btn.press(down && Oil_btn.contains(pixel_x, pixel_y));
    exit_btn.press(down && exit_btn.contains(pixel_x, pixel_y));
     
   
    if (Pellet_btn.justReleased())
        Pellet_btn.drawButton();
    if (Oil_btn.justReleased())
        Oil_btn.drawButton();
    if (exit_btn.justReleased())
        exit_btn.drawButton();
           
    if (Pellet_btn.justPressed()) {
        Pellet_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, RED);
        // grafh sto fillRect thn epilogh
        Pellet_on = true ;
        Oil_on = false ;
    }
    if (Oil_btn.justPressed()) {
          Oil_btn.drawButton(true);
          tft.fillRect(40, 80, 160, 80, RED);
        // grafh sto fillRect thn epilogh 
        Pellet_on = false ;
        Oil_on = true ;
    }
    if (exit_btn.justPressed()) {
        exit_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, MAGENTA);
        save_therm = false ;
       EEPROM.put( 40,Pellet_on);
       EEPROM.put( 50,Oil_on);
      MenuCount = 1 ;
      exit ;
    }
  
  }
  tft.fillScreen(BLACK);
  dispMenu = true ;
}

//-------------------------------------------
void header1( String  Msg   ) {  
//-------------------------------------------  
     tft.fillRect(20, 10, 200 , 40, RED);
     tft.setCursor(30,30);
     tft.setFont(&Greek_Sigismundus8pt7b);
     tft.setTextSize(1);
     tft.setTextColor(WHITE);
         
     tft.print( Msg  );
     tft.setFont();
     tft.setTextSize(2);
}
//----------------------------------------
void dispScreen(){
//----------------------------------------
//---------Διαχ/ση Relay Λέβητα ( Pellet ή Oil  )------ 
     tft.setCursor(140,90);
     tft.print(  therm1  );
     
     if ( therm0 >= therm1 ) {
       if (Pellet_on) {
        tft.fillRect(210,90, 20,20, RED) ; 
        digitalWrite(Relay_01,HIGH);
        CL = "L02" ;
       } 
       else if(Oil_on) {
        tft.fillRect(210,90, 20,20, RED) ; 
        digitalWrite(Relay_02,HIGH);  
        CL = "L02" ;
      }
     }  
     else if ( therm0 <= therm1-2 ) {  
       if (Pellet_on) {
        tft.fillRect(210,90, 20,20, GREEN) ; 
        digitalWrite(Relay_01,LOW);
        CL = "L01" ;
       }
       else if (Oil_on) {
        tft.fillRect(210,90, 20,20, GREEN) ; 
        digitalWrite(Relay_02,LOW);
        CL = "L01" ;
       }
     }   
     else tft.fillRect(210,90, 20,20, YELLOW) ;
   //---------Διαχ/ση Relay Κυκλοφοριτή----------------     
     tft.setCursor(140,140);
     tft.print(  therm2  );
     if ( therm0 >= therm2 ) {
        tft.fillRect(210,140, 20,20, GREEN);
        digitalWrite(Relay_03,LOW);
        CK = "K01" ;
     }  
     else if ( therm0 <= therm2-2 ) {  
        tft.fillRect(210,140, 20,20, RED) ; 
        digitalWrite(Relay_03,HIGH);
        CK = "K02" ;
     }  
     else tft.fillRect(210,140, 20,20, YELLOW) ; 
  //---------Διαχ/ση Relay Boiller   ----------------- 
     tft.setCursor(140,190);
     tft.print(  therm3  );
     if ( therm0 >= therm3 ) {
        tft.fillRect(210,190, 20,20, GREEN);
        digitalWrite(Relay_04,LOW);
        CB = "B01" ;
     }  
     else if  ( therm0 <= therm3-2 ) {   
        tft.fillRect(210,190, 20,20, RED)  ; 
        digitalWrite(Relay_04,HIGH);
        CB = "B02" ;
     }   
     else tft.fillRect(210,190, 20,20, YELLOW)  ;
   //---------------------------------------------   
 
     tft.fillRect(80,240, 120,20,BLACK);
     tft.setTextSize(3); 
     tft.setTextColor(WHITE);
     tft.setCursor(80,240);
     tft.print(  therm0  );
     tft.setTextSize(2);
}

//-----------------------------------
void bootSreen() {
//-----------------------------------
  
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(50, 140);
  tft.print("Loading...");

  tft.setTextColor(tft.color565(255, 255, 0));
  tft.setCursor(30, 70);
  tft.print("By:");

  tft.setCursor(30, 100);
  tft.print("Myriskos John");

  for (int i; i < 200; i++)
  {
    tft.fillRect(BAR_MINY - 10, BLUEBAR_MINX, i, 10, BLUE);
     delay(10);    
  }

  delay(500) ;
  
  tft.fillScreen(BLACK);
}

//#endif
