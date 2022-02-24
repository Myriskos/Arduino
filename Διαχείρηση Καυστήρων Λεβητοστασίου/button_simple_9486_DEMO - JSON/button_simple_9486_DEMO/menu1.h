bool ESP_Live = false ;
//--------------------------------------------
void menu1(){
//--------------------------------------------
//#include "bitmap_mono.h"
 therm1_btn.initButton(&tft,  80, 100, 150, 40, WHITE, RED, BLACK, "", 2);
 therm2_btn.initButton(&tft,  80, 150, 150, 40, WHITE, RED, BLACK, "", 2);
 therm3_btn.initButton(&tft,  80, 200, 150, 40, WHITE, RED, BLACK, "", 2);
 therm1_btn.drawButton(false);
 therm2_btn.drawButton(false);
 therm3_btn.drawButton(false);

 PreviewMenu_btn.initButton(&tft,  40, 400, 50, 40, WHITE, CYAN, BLACK, "<", 3);
 NextMenu_btn.initButton(&tft,    120, 400, 50, 40, WHITE, CYAN, BLACK, ">", 3);
 mode_btn.initButton(&tft,    280, 400, 50, 40, WHITE, RED, BLACK, "Mode", 2);
 PreviewMenu_btn.drawButton(false);
 NextMenu_btn.drawButton(false);
 mode_btn.drawButton(false);
 
     u8g2_for_adafruit_gfx.setFontMode(1); 
     u8g2_for_adafruit_gfx.setForegroundColor(WHITE);
     u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 


 bool While_menu = true ;
 dispMenu = true ;
 while (While_menu) {
     bool menudown = Touch_getXY();
     therm1_btn.press(menudown && therm1_btn.contains(pixel_x, pixel_y));
     therm2_btn.press(menudown && therm2_btn.contains(pixel_x, pixel_y));
     therm3_btn.press(menudown && therm3_btn.contains(pixel_x, pixel_y));
     PreviewMenu_btn.press(menudown && PreviewMenu_btn.contains(pixel_x, pixel_y));
     NextMenu_btn.press(menudown && NextMenu_btn.contains(pixel_x, pixel_y));
     mode_btn.press(menudown && mode_btn.contains(pixel_x, pixel_y));
     
 if (dispMenu){
 
      ReadSensor: 
      sensors1.requestTemperatures ();
      sensors2.requestTemperatures ();
      sensors3.requestTemperatures ();
      sensors4.requestTemperatures ();
    //  therm03=(sensors3.getTempCByIndex(0)); 
 
    String Shead = "" ;
    if (Pellet_on){
     Shead =  "Pellet" ;
    // therm0=(sensors1.getTempCByIndex(0));  
    // delay(100) ;
    }
    else if (Oil_on) {
     Shead =  " Oil  " ; 
    // therm0=(sensors2.getTempCByIndex(0));  
    // delay(100) ;
   }
    else {
     Shead =  " No Mode " ; 
    }
  
     header1( "Επιλογή->"+ Shead );
  
       therm1_btn.drawButton();   
       therm2_btn.drawButton();   
       therm3_btn.drawButton(); 

       u8g2_for_adafruit_gfx.setCursor(20,100);                // start writing at this position
       u8g2_for_adafruit_gfx.print( "Λέβητας");  
       u8g2_for_adafruit_gfx.setCursor(20,150);                // start writing at this position
       u8g2_for_adafruit_gfx.print( "Κυκλοφοριτής");
       u8g2_for_adafruit_gfx.setCursor(20,201);                // start writing at this position
       u8g2_for_adafruit_gfx.print( "Μπόϊλερ    "); 

      tft.fillRect(50,250, 220,40,BLACK); 
      u8g2_for_adafruit_gfx.setCursor(50,280);                
      u8g2_for_adafruit_gfx.print( "θερμ. Νερών Λέβητα");
 
       u8g2_for_adafruit_gfx.setFont(u8g2_font_unifont_h_symbols); 
       u8g2_for_adafruit_gfx.drawGlyph(35,400,0x23f4);  
       u8g2_for_adafruit_gfx.drawGlyph(115,400,0x23f5);  
       u8g2_for_adafruit_gfx.setFontMode(1);
       u8g2_for_adafruit_gfx.setForegroundColor(WHITE); 
       u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
     
       tft.setFont() ;

       PreviewMenu_btn.drawButton();
       NextMenu_btn.drawButton();
       mode_btn.drawButton();



   // if (therm0 < 0 ) ; goto ReadSensor ; 
   
     if (therm0 < 0 ){ 
      continue;
     }
     dispMenu = false ;
   
 }  
       //------------------------ Εικονικες θερμοκρασίες ----
       if (millis() - previousMillis2 >= (intervalDisp2 * timer2 )  ) {
           previousMillis2 = millis();   
          if (Up)   therm0 = therm0 + 0.50 ; 
          if (Down) therm0 = therm0 - 0.50 ;
          if ( therm0 >= 80 ){
            Down = true ; Up   = false ; 
          }
          if ( therm0 <= 30 ){
            Up   = true ; Down = false ; 
          }
       }  
       //---------------------------------------------------
 
            //sensors3.requestTemperatures ();
            //therm03=(sensors3.getTempCByIndex(0));
              String Shead = "" ;
              if (Pellet_on){
               Shead =  "Pellet" ;
               Levitas = "L01" ;
              // therm0=(sensors1.getTempCByIndex(0));  
              // delay(100) ;
              }
              else if (Oil_on) {
               Shead =  " Oil  " ;
               Levitas = "L02" ; 
              // therm0=(sensors2.getTempCByIndex(0));  
              // delay(100) ;
             }
              else {
               Shead =  " No Mode " ; 
              }
         //------------Sent Data with String-------------------------------
               strSendSereal = String('T')+String(therm0)+String('T')+String(therm03); 
               strSendSereal+= String('T')+String(therm1)+String('T')+String(therm2)+String('T')+String(therm3); 
               strSendSereal+= String( Levitas ) ;
               strSendSereal+= String( CL )+String( CK)+String( CB ) ;

         //------------Sent Data with json-------------------------------  
              // Send Data from ArduinoMega Serial3 to Esp8266 
              StaticJsonBuffer<1000> jsonBuffer;
              JsonObject& root = jsonBuffer.createObject();
              root["therm0"]  = String(therm0);
              root["therm03"] = String(therm03);
              root["therm1"]  = String(therm1);
              root["therm2"]  = String(therm2);
              root["therm3"]  = String(therm3);
              root["Levitas"] = String( Levitas );
              root["CL"] = String(CL);
              root["CK"] = String(CK);
              root["CB"] = String(CB);
             

           if (millis() - previousMillis3 >= (intervalDisp3 * timer3 )  ) {
             previousMillis3 = millis();  
           
             Serial3.println(strSendSereal);
             Serial.println(strSendSereal);

            //---  watchdog --------------------
              int watchdog_delimiter1, watchdog_delimiter2;
              String watchdog = "0" ;
              String watchdog_Read =  Serial2.readString() ;
              watchdog_delimiter1 = watchdog_Read.indexOf("%");
              watchdog_delimiter2 = watchdog_Read.indexOf("%", watchdog_delimiter1 + 1);
              watchdog = watchdog_Read.substring(watchdog_delimiter1 + 1, watchdog_delimiter2);
              if ( watchdog == "1"){
                ESP_Live = true ;
              }
               
             Serial.println(watchdog);

                   if ( watchdog != "1"   ) {  
                     tft.fillRect(20, 45, 300 , 20, BLACK);
                     u8g2_for_adafruit_gfx.setFontMode(1);
                     u8g2_for_adafruit_gfx.setForegroundColor(WHITE); 
                     u8g2_for_adafruit_gfx.setCursor(30,70);  
                     u8g2_for_adafruit_gfx.print( "ESP_is_dead");
                                        
                   } 
                   else {
                     tft.fillRect(20, 45, 300 , 20, BLACK);
                     u8g2_for_adafruit_gfx.setFontMode(1);
                     u8g2_for_adafruit_gfx.setForegroundColor(WHITE); 
                     u8g2_for_adafruit_gfx.setCursor(30,70);  
                     u8g2_for_adafruit_gfx.print( "ESP_is_Live ");
                  }
                   
                  if (ESP_Live  && watchdog != "1"   ) {
                     ESP_Reset() ;
                    
                  }

                     
           }
          
           if (millis() - previousMillis >= (intervalDisp * timer )  ) {
             previousMillis = millis();  
             dispScreen() ; 
           }
  
         //---------------------------------------------
  
    if (therm1_btn.justPressed()) {
        therm1_btn.drawButton(true);
        therm1 =   therm_setup( "Λέβητας" , therm1   ) ;
        EEPROM.put( 10,therm1);
    }
    if (therm2_btn.justPressed()) {
        therm2_btn.drawButton(true);
        therm2 =   therm_setup( "Κυκλοφοριτής" , therm2   ) ;
        EEPROM.put( 20,therm2);
    }
    if (therm3_btn.justPressed()) {
        therm3_btn.drawButton(true);
        therm3 =   therm_setup( "Μπόϊλερ" , therm3   ) ;
        EEPROM.put( 30,therm3);
    }  

    if (NextMenu_btn.justPressed()) {
        NextMenu_btn.drawButton(true);
        MenuCount++ ;
        if ( MenuCount  > 2  ) {
          MenuCount = 2 ;
        } 
        While_menu = false ;
    }  

    if (PreviewMenu_btn.justPressed()) {
        PreviewMenu_btn.drawButton(true);
        MenuCount-- ;
        if ( MenuCount < 1  ) {
          MenuCount = 1 ;
        }
        While_menu = false ;
    }
    if (mode_btn.justPressed()) {
        mode_btn.drawButton(true);
        mode_setup() ;
        While_menu = false ;
    }
  
 }   
   
}
