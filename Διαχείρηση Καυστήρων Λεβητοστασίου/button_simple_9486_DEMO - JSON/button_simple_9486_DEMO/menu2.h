
//--------------------------------------------
void menu2(){
//--------------------------------------------
 wdt_disable(); // watchdog

 u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
 therm1_btn.initButton(&tft,  80, 100, 150, 40, WHITE, BLUE, BLACK, "", 2);
 therm2_btn.initButton(&tft,  80, 150, 150, 40, WHITE, BLUE, BLACK, "", 2);
 therm3_btn.initButton(&tft,  80, 200, 150, 40, WHITE, BLUE, BLACK, "", 2);
 therm1_btn.drawButton(false);
 therm2_btn.drawButton(false);
 therm3_btn.drawButton(false);

 PreviewMenu_btn.initButton(&tft,  40, 400, 50, 40, WHITE, CYAN, BLACK, "", 3);
 NextMenu_btn.initButton(&tft,    120, 400, 50, 40, WHITE, CYAN, BLACK, "", 3);
 PreviewMenu_btn.drawButton(false);
 NextMenu_btn.drawButton(false);

 bool save_therm1 = true ;
 dispMenu = true ;
 while (save_therm1) {
     bool menudown = Touch_getXY();
     therm1_btn.press(menudown && therm1_btn.contains(pixel_x, pixel_y));
     therm2_btn.press(menudown && therm2_btn.contains(pixel_x, pixel_y));
     therm3_btn.press(menudown && therm3_btn.contains(pixel_x, pixel_y));
     PreviewMenu_btn.press(menudown && PreviewMenu_btn.contains(pixel_x, pixel_y));
     NextMenu_btn.press(menudown && NextMenu_btn.contains(pixel_x, pixel_y));
     
   if (dispMenu){
     header1("θερμοκρασίες. Νερών ");
     PreviewMenu_btn.drawButton();
     NextMenu_btn.drawButton();
     dispMenu = false ;
 
     u8g2_for_adafruit_gfx.setFontMode(1); 
     u8g2_for_adafruit_gfx.setForegroundColor(WHITE);  
     u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
     tft.fillRect(50,250, 220,40,BLACK); 
     u8g2_for_adafruit_gfx.setCursor(50,280);             
     u8g2_for_adafruit_gfx.print( "θερμοκρασίες. Νερών "); 

     u8g2_for_adafruit_gfx.setCursor(20,100);                // start writing at this position
     u8g2_for_adafruit_gfx.print( "Λέβητα   ");  
     u8g2_for_adafruit_gfx.setCursor(20,150);                // start writing at this position
     u8g2_for_adafruit_gfx.print( "Μπόϊλερ  ");
     u8g2_for_adafruit_gfx.setCursor(20,201);                // start writing at this position
     u8g2_for_adafruit_gfx.print( "Επιστρ/να"); 

    }  

     //----------------------
      tft.fillCircle(40, 400, 30, BLUE);                    //seek down button
      tft.fillTriangle(35, 390, 25, 400, 35, 410, WHITE);
      tft.fillTriangle(50, 390, 40, 400, 50, 410, WHITE);
     //-----------------------
      tft.fillCircle(120, 400, 30, BLUE);                       //seek up button
      tft.fillTriangle(125, 390, 135, 400, 125, 410, WHITE);
      tft.fillTriangle(110, 390, 120, 400, 110, 410, WHITE);
     //-----------------------
  
       
    if (NextMenu_btn.justPressed()) {
        NextMenu_btn.drawButton(true);
        MenuCount++ ;
        if ( MenuCount  > 2  ) {
          MenuCount = 2 ;
        } 
        save_therm1 = false ;
    }  

    if (PreviewMenu_btn.justPressed()) {
        PreviewMenu_btn.drawButton(true);
        MenuCount-- ;
        if ( MenuCount < 1  ) {
          MenuCount = 1 ;
        }
        save_therm1 = false ;
     }


//    //->>>>> test Button 
//    if ( therm04 > 30 ) {
//      PreviewMenu_btn.drawButton(true);
//      MenuCount = 1 ;
//      save_therm1 = false ;
//    }
  
     
   //----------------------------------------------------------------------
      if (millis() - previousMillis2 >= (intervalDisp2 * timer2 )  ) {
        previousMillis2 = millis();   

         sensors1.requestTemperatures ();
         sensors2.requestTemperatures ();
         sensors3.requestTemperatures ();
         sensors4.requestTemperatures ();
         
         therm03=(sensors3.getTempCByIndex(0));
         therm04=(sensors4.getTempCByIndex(0));
         if (Pellet_on){
            therm0=(sensors1.getTempCByIndex(0));
         }
         else if (Oil_on) {  
            therm0=(sensors2.getTempCByIndex(0));
         }
          tft.setTextColor(WHITE);
         // tft.fillRoundRect(180, 80, 140, 60,20, BLUE);
          tft.fillRect(180, 80,140,60,BLACK);  
          tft.fillRect(180,140,140,60,BLACK); 
          tft.fillRect(180,190,140,60,BLACK); 
          tft.setTextSize(2);
          tft.setCursor(180,90);
          tft.print( therm0);
          tft.setCursor(180,140);
          tft.print( therm03);
          tft.setCursor(180,190);
          tft.print( therm04);

    
         tft.setTextColor(WHITE);
         tft.fillRect(80,300,120,50,BLACK);
         tft.setTextSize(3); 
         tft.setTextColor(WHITE);
         tft.setCursor(80,300);
         tft.print( therm0);
         tft.setTextSize(2);
       
       
     }
  //----------------------------------------------------------------------
 }  


    tft.fillRect(180, 80,140,60,BLACK);  
    tft.fillRect(180,140,140,60,BLACK); 
    tft.fillRect(180,190,140,60,BLACK); 
   
   
}
