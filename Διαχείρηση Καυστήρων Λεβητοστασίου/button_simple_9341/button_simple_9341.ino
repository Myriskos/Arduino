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

// COPY-PASTE from Serial Terminal:
const int XP=7,XM=A1,YP=A2,YM=6; //240x320 ID=0x9341
const int TS_LEFT=171,TS_RT=904,TS_TOP=138,TS_BOT=895;

float therm0  = 22.50 ;  //  Νερά Λέβητα
float therm03 = 22.50 ;  //  Νερά Μπόϊλερ
float therm1  = 70.00 ;  //  Θερμοκρασία που κλήνει ο Λέβητας
float therm2  = 40.00 ;  //  Θερμοκρασία που ανοίγει ο Κυκλοφοριτής
float therm3  = 45.00 ;  //  Θερμοκρασία που ανοίγει η ηλεκτροβάνα του Boiller
int MenuCount = 1 ;


//ορισμος εξοδων ρελε
int  Relay_01 = A8 ;      // του λέβητα Pellet
int  Relay_02 = A9 ;      // του λέβητα Πετρελαίου
int  Relay_03 = A10 ;     // του κυκλοφοριτή
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
String CL , CK , CB ;

unsigned long previousMillisScreen = 0; 
const long intervalScreen = 1000;
bool lfores = true ;
int  timer = 1 ;
//----------------------------------

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button  Pellet_btn , Oil_btn  , therm1_btn , therm2_btn , therm3_btn , on_btn, off_btn , exit_btn , NextMenu_btn , PreviewMenu_btn ;

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
        //pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        //pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());

        //PORTRAIT  CALIBRATION     240 x 320
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, 240) ;
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, 320) ;
        
//        //LANDSCAPE CALIBRATION     320 x 240
//        pixel_x = map(p.y, TS_LEFT=138, TS_RT=895, 0, 320) ;
//        pixel_y = map(p.x, TS_TOP=904, TS_BOT=171, 0, 240) ;
     
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

//#include "function.h"

//--------------------------------------------
void setup(void)
//--------------------------------------------
{
    
    SerialMega.begin(115200);
    Serial.begin(115200);
    uint16_t ID = tft.readID();
//    Serial.print("TFT ID = 0x");
//    Serial.println(ID, HEX);
//    Serial.println("Calibrate for your Touch Panel");
    
    ID = 0x9341; // write-only shield
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
     // menu2();
     mode_setup() ;
      break;   
  }
}

//--------------------------------------------
void menu1(){
//--------------------------------------------

 therm1_btn.initButton(&tft,  60, 100, 100, 40, WHITE, CYAN, BLACK, "Levitas1", 2);
 therm2_btn.initButton(&tft,  60, 150, 100, 40, WHITE, CYAN, BLACK, "Kyklofor3", 2);
 therm3_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "Boiler4", 2);
 therm1_btn.drawButton(false);
 therm2_btn.drawButton(false);
 therm3_btn.drawButton(false);

 PreviewMenu_btn.initButton(&tft,  60, 300, 50, 40, WHITE, CYAN, BLACK, " < ", 3);
 NextMenu_btn.initButton(&tft,    160, 300, 50, 40, WHITE, CYAN, BLACK, " > ", 3);
 PreviewMenu_btn.drawButton(false);
 NextMenu_btn.drawButton(false);


 bool save_therm1 = true ;
 while (save_therm1) {

     bool menudown = Touch_getXY();
     therm1_btn.press(menudown && therm1_btn.contains(pixel_x, pixel_y));
     therm2_btn.press(menudown && therm2_btn.contains(pixel_x, pixel_y));
     therm3_btn.press(menudown && therm3_btn.contains(pixel_x, pixel_y));
     PreviewMenu_btn.press(menudown && PreviewMenu_btn.contains(pixel_x, pixel_y));
     NextMenu_btn.press(menudown && NextMenu_btn.contains(pixel_x, pixel_y));
         
     if (dispMenu){
          dispMenu = false ;
          sensors.requestTemperatures ();
          therm03=(sensors.getTempCByIndex(2));  
     
        String Shead = "" ;
        if (Pellet_on){
         Shead =  "Pellet" ;
         therm0=(sensors.getTempCByIndex(0));  
         delay(100) ;
        }
        else if (Oil_on) {
         Shead =  " Oil  " ; 
         therm0=(sensors.getTempCByIndex(1));  
         delay(100) ;
       }
        else {
         Shead =  " No Mode " ; 
        }
      
         header1("EPILOGH->"+ Shead );
          
         therm1_btn.drawButton();
         therm2_btn.drawButton();
         therm3_btn.drawButton();
         tft.setFont() ;
         PreviewMenu_btn.drawButton();
         NextMenu_btn.drawButton();

     }

        if (therm1_btn.justPressed()) {
        therm1_btn.drawButton(true);
        therm1 =   therm_setup( "Lebhtas" , therm1   ) ;
        EEPROM.put( 10,therm1);
    }
    if (therm2_btn.justPressed()) {
        therm2_btn.drawButton(true);
        therm2 =   therm_setup( "Kykloforiths" , therm2   ) ;
        EEPROM.put( 20,therm2);
    }
    if (therm3_btn.justPressed()) {
        therm3_btn.drawButton(true);
        therm3 =   therm_setup( "Boiler" , therm3   ) ;
        EEPROM.put( 30,therm3);
    }  

    if (NextMenu_btn.justPressed()) {
        NextMenu_btn.drawButton(true);
        MenuCount++ ;
        if ( MenuCount  > 2  ) {
          MenuCount = 2 ;
        } 
          tft.setTextSize(2);
          save_therm1 = false ;
          continue;
    }  

    if (PreviewMenu_btn.justPressed()) {
        PreviewMenu_btn.drawButton(true);
        MenuCount-- ;
        if ( MenuCount < 1  ) {
          MenuCount = 1 ;
        }
        save_therm1 = false ;
    }


     

//------------------------ Εικονικες θερμοκρασίες ----
//     int Stimer = 0 ;
//     bool lfores = true ;
//     while (  lfores  )  {
//        Stimer++ ; 
//       if ( Stimer >= 1000 ) lfores = false ;

       Delay_Sreen() ;
       
       if ( !lfores ) {
          lfores = true ;
//          if (Up)   therm0 = therm0 + 0.50 ; 
//          if (Down) therm0 = therm0 - 0.50 ;
//          
//          if ( therm0 >= 80 ){
//            Down = true ; Up   = false ; 
//          }
//          if ( therm0 <= 30 ){
//            Up   = true ; Down = false ; 
//          }
         
          //------------------------------------------
            sensors.requestTemperatures ();
            therm03=(sensors.getTempCByIndex(2));
              String Shead = "" ;
              if (Pellet_on){
               Shead =  "Pellet" ;
               Levitas = "L01" ;
               therm0=(sensors.getTempCByIndex(0));  
               delay(100) ;
              }
              else if (Oil_on) {
               Shead =  " Oil  " ;
               Levitas = "L02" ; 
               therm0=(sensors.getTempCByIndex(1));  
               delay(100) ;
             }
              else {
               Shead =  " No Mode " ; 
              }

             if (therm0 < 0 )continue;
             
              
         //-------------------------------------------
         
           strSendSereal = String('T')+String(therm0)+String('T')+String(therm03); 
           strSendSereal+= String('T')+String(therm1)+String('T')+String(therm2)+String('T')+String(therm3); 
           strSendSereal+= String( Levitas ) ;
           strSendSereal+= String( CL )+String( CK)+String( CB ) ;
           SerialMega.println(strSendSereal);
           delay(500);
              
           dispScreen() ;
       }
    //   } // while (  lfores  )
      delay(500) ;

  
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

//   PreviewMenu_btn.initButton(&tft,  60, 300, 50, 40, WHITE, CYAN, BLACK, " < ", 3);
//   NextMenu_btn.initButton(&tft,    160, 300, 50, 40, WHITE, CYAN, BLACK, " > ", 3);
//   PreviewMenu_btn.drawButton(false);
//   NextMenu_btn.drawButton(false);

    

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

//    if (NextMenu_btn.justPressed()) {
//        NextMenu_btn.drawButton(true);
//        MenuCount++ ;
//        if ( MenuCount  > 2  ) {
//          MenuCount = 2 ;
//        } 
//        save_therm = false ;
//    }  
//
//    if (PreviewMenu_btn.justPressed()) {
//        PreviewMenu_btn.drawButton(true);
//        MenuCount-- ;
//        if ( MenuCount < 1  ) {
//          MenuCount = 1 ;
//        }
//       save_therm = false ;
//    }

    
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
     else if ( therm0 <= therm1-0.50 ) {  
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
     else if ( therm0 <= therm2-0.50 ) {  
        tft.fillRect(210,140, 20,20, RED) ; 
        digitalWrite(Relay_03,HIGH);
        CK = "K02" ;
     }  
     else tft.fillRect(210,140, 20,20, YELLOW) ; 
  //---------Διαχ/ση Relay Boiller   ----------------- 
     tft.setCursor(140,190);
     tft.print(  therm3  );
     if ( therm0 >= therm03 ) {
        tft.fillRect(210,190, 20,20, GREEN);
        digitalWrite(Relay_04,LOW);
        CB = "B01" ;
     }  
     else if  ( therm0 <= therm03-0.50 ) {   
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

//--------------------------------------------
void Delay_Sreen() {
//--------------------------------------------  
    // Μαυτο τον τρόπο δεν σταματάει η ροη του προγράμματος
    // ενω με την daley()  σταματάει
    unsigned long currentMillisScreen = millis();
  
  if (currentMillisScreen - previousMillisScreen >= (intervalScreen * timer )  ) {
      previousMillisScreen = currentMillisScreen;
      lfores = false ;
  }
}

//#endif
