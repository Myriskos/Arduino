//#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#include "U8g2_for_Adafruit_GFX.h"
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;


#include <TouchScreen.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
//SoftwareSerial SerialMega(16,17);   // TX-RX 5,6
//SoftwareSerial SerialMega(14,15);   // TX-RX 5,6


#include <ArduinoJson.h>   // Ver 5.xx

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
  #define ONE_WIRE_BUS1 39   //δηλωση pin αισθητηρα Πετρελαίου
 OneWire oneWire1(ONE_WIRE_BUS1);
 DallasTemperature sensors1(&oneWire1); //Σχετίζουμε την Onewire στον Dallas Temperature
 #define ONE_WIRE_BUS2  41   //δηλωση pin αισθητηρα Πέλλετ
 OneWire oneWire2(ONE_WIRE_BUS2);
 DallasTemperature sensors2(&oneWire2); //Σχετίζουμε την Onewire στον Dallas Temperature
 #define ONE_WIRE_BUS3  43   //δηλωση pin αισθητηρα Μπόϊλερ
 OneWire oneWire3(ONE_WIRE_BUS3);
 DallasTemperature sensors3(&oneWire3); //Σχετίζουμε την Onewire στον Dallas Temperature
  #define ONE_WIRE_BUS4 45   //δηλωση pin αισθητηρα Επισρεφόμενα Νερά
 OneWire oneWire4(ONE_WIRE_BUS4);
 DallasTemperature sensors4(&oneWire4); //Σχετίζουμε την Onewire στον Dallas Temperature 



#define MINPRESSURE 200
#define MAXPRESSURE 1000
#define DPI 141 // Approximate res. of Adafruit 2.8" TFT
// ALL Touch panels and wiring is DIFFERENT
//--------------------------------

// COPY-PASTE from Serial Terminal:
const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9325
const int TS_LEFT=893,TS_RT=108,TS_TOP=931,TS_BOT=120;

//PORTRAIT  CALIBRATION     240 x 320
//x = map(p.x, LEFT=893, RT=108, 0, 240)
//y = map(p.y, TOP=931, BOT=120, 0, 320)
//
//LANDSCAPE CALIBRATION     320 x 240
//x = map(p.y, LEFT=931, RT=120, 0, 320)
//y = map(p.x, TOP=108, BOT=893, 0, 240)



float therm0 = 22.50 ; 
float therm1 = 75.50 ; 
float therm2 = 40.50 ; 
float therm3 = 55.50 ;
//float therm03 = 48.50 ;
float therm03 = 40.00 ;
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
 String CL , CK , CB ;

 unsigned long previousMillis = 0; 
 const    long intervalDisp = 100;
 int  timer = 10 ;

 unsigned long previousMillis2 = 0; 
 const    long intervalDisp2 = 100;
 int  timer2 = 10 ;

 unsigned long previousMillis3 = 0; 
 const    long intervalDisp3 = 100;
 int  timer3 = 15 ;
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
       pixel_y = map(p.y, TS_TOP , TS_BOT,0, 320) ;

     //LANDSCAPE CALIBRATION     320 x 240
     //  pixel_x = map(p.y, TS_LEFT, TS_RT, 0, 320) ;
     //  pixel_y = map(p.x, TS_TOP, TS_BOT, 0, 240) ;
        
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
  
   Serial.begin(9600);
   Serial2.begin(9600);
   Serial3.begin(9600);
   
   
    
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");

   // ID = 0x9325; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            // 0= PORTRAIT  3 = LANDSCAPE
    tft.fillScreen(BLACK);
u8g2_for_adafruit_gfx.begin(tft); 
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

   u8g2_for_adafruit_gfx.setFontMode(1);                 // use u8g2 none transparent mode
  u8g2_for_adafruit_gfx.setFontDirection(0);            // left to right (this is default)
  u8g2_for_adafruit_gfx.setForegroundColor(WHITE);      // apply Adafruit GFX color
  
 // u8g2_for_adafruit_gfx.setFont(u8g2_font_cu12_t_greek);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
 // u8g2_for_adafruit_gfx.setFont(u8g2_font_unifont_t_greek);
 
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

    on_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK,  "+", 3);
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
      //  tft.fillRect(40, 80, 160, 80, MAGENTA);
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
    String Shead = "" ;
    Shead =  " Mode Setup " ;  
    header1( "Επιλογή->"+ Shead );
   
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
       // tft.fillRect(40, 80, 160, 80, MAGENTA);
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
       
    tft.setTextSize(5);
    tft.setTextColor(WHITE);
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setForegroundColor(WHITE); 
    u8g2_for_adafruit_gfx.setCursor(30,30);                // start writing at this position
    u8g2_for_adafruit_gfx.print( Msg);    
    u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
    
    u8g2_for_adafruit_gfx.drawUTF8( 60,450, "Μυρίσκος Ιωάννης" );
    u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setForegroundColor(WHITE); 
   
     tft.setTextSize(2);
}
//----------------------------------------
void dispScreen(){
//----------------------------------------
//---------Διαχ/ση Relay Λέβητα ( Pellet ή Oil  )------ 
     tft.setCursor(160,90);
     tft.print(  therm1  );
     if ( therm0 >= therm1 ) {
       if (Pellet_on) {
       // tft.fillRect(220,90, 15,15, RED) ; 
        tft.fillCircle(230, 95, 8, RED);
        digitalWrite(Relay_01,HIGH);
        CL = "L02" ;
       } 
       else if(Oil_on) {
        //tft.fillRect(220,90, 15,15, RED) ; 
		tft.fillCircle(230, 95, 8, RED);
        digitalWrite(Relay_02,HIGH);  
        CL = "L02" ;
      }
     }  
     else if ( therm0 <= therm1-1 ) {  
       if (Pellet_on) {
       // tft.fillRect(220,90, 15,15, GREEN) ; 
        tft.fillCircle(230, 95, 8, GREEN);
        digitalWrite(Relay_01,LOW);
        CL = "L01" ;
       }
       else if (Oil_on) {
        //tft.fillRect(220,90, 15,15, GREEN) ; 
        tft.fillCircle(230, 95, 8, GREEN);
        digitalWrite(Relay_02,LOW);
        CL = "L01" ;
       }
     }   
     //else tft.fillRect(260,90, 15,15, YELLOW) ;
     else tft.fillCircle(230, 95, 8, YELLOW);   
   //---------Διαχ/ση Relay Κυκλοφοριτή----------------     
     tft.setCursor(160,140);
     tft.print(  therm2  );
     if ( therm0 >= therm2 ) {
        //tft.fillRect(220,140, 15,15, GREEN);
        tft.fillCircle(230,145, 8, GREEN);
        digitalWrite(Relay_03,LOW);
        CK = "K01" ;
     }  
     else if ( therm0 <= therm2- 0.50 ) {  
        //tft.fillRect(220,140, 15,15, RED) ; 
        tft.fillCircle(230,145, 8, RED);
        digitalWrite(Relay_03,HIGH);
        CK = "K02" ;
     }  
     //else tft.fillRect(220,140, 15,15, YELLOW) ; 
     else tft.fillCircle(230,145, 8, YELLOW); 
  //---------Διαχ/ση Relay Boiller   ----------------- 
     tft.setCursor(160,190);
     tft.print(  therm3  );
     if ( therm0 >= therm03 && therm0 >= therm3  ) {
        //tft.fillRect(220,190, 15,15, GREEN);
        tft.fillCircle(230,195, 8, GREEN);
        digitalWrite(Relay_04,LOW);
        CB = "B01" ;
     }  
    // else if  ( therm0 <= therm3- 0.50 ) {   
      else if ( therm0 <= therm03- 0.50 || therm0 <= therm3- 0.50  ) {
        //tft.fillRect(220,190, 15,15, RED)  ;
        tft.fillCircle(230,195, 8, RED); 
        digitalWrite(Relay_04,HIGH);
        CB = "B02" ;
     }   
     //else tft.fillRect(220,190, 15,15, YELLOW)  ;
     else tft.fillCircle(230,195, 8, YELLOW); 
   //---------------------------------------------   
  
     tft.setTextColor(WHITE);
     tft.fillRect(80,240,120,40,BLACK);
     tft.setTextSize(3); 
     tft.setTextColor(YELLOW);
     tft.setCursor(80,245);
     tft.print( therm0);
     tft.setTextColor(WHITE);
   
//     u8g2_for_adafruit_gfx.setFont(u8g2_font_unifont_t_weather ); 
//     u8g2_for_adafruit_gfx.setCursor(40,250);                
//     u8g2_for_adafruit_gfx.print( 1 );
     u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek);
     tft.setTextSize(2); 
}

/// GFX drawBitmap() expects each row to be on 8-bit boundary.  i.e. pad = 7
// Mono BMP rows are on 32-bit boundary. i.e. pad = 31,  rows are in RVS order.
// FreeFont bitmaps have no padding.  i.e. pad = 0.   e.g. 5x4 bitmap is in 3 bytes
//-----------------------------------
void showbgd(int x, int y, const uint8_t *bmp, int w, int h, uint16_t color, uint16_t bg, uint8_t pad = 7){
//-----------------------------------  
    int yy, xx;
    uint8_t first = 1, RVS = pad & 0x80;
    uint16_t pixel;
    pad &= 31;
    uint16_t wid = (w + pad) & ~pad;                    //bits per row
    tft.setAddrWindow(x, y, x + w - 1, y + h - 1); //
    for (yy = 0; yy < h; yy++) {
        uint32_t ofs = (RVS ? (h - yy - 1) : yy) * wid; //bit offset
        const uint8_t *p = bmp + (ofs >> 3);            //flash address
        uint8_t mask = 0x80 >> (ofs & 7);               //bit mask
        uint8_t c = pgm_read_byte(p++);
        for (xx = 0; xx < w; xx++) {
            if (mask == 0) {
                c = pgm_read_byte(p++);
                mask = 0x80;
            }
            pixel = (c & mask) ? color : bg;
            tft.pushColors(&pixel, 1, first);
            first = 0;
            mask >>= 1;
        }
    }
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
}
//-----------------------------------
void msg_time(int x, int y, String msg, uint32_t t) {
//-----------------------------------  
    t = millis() - t;
    tft.setCursor(x, y);
    tft.print(msg);
    tft.print(t);
    tft.print(F("ms"));
}


//-----------------------------------
void ESP_Reset(){
//-----------------------------------  

  Serial.print( "ESP_Reset."  );  

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
