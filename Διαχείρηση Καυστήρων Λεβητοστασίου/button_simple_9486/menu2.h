
//--------------------------------------------
void menu2(){
//--------------------------------------------

 u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
 therm1_btn.initButton(&tft,  80, 100, 150, 40, WHITE, BLACK, BLACK, "", 2);
 therm2_btn.initButton(&tft,  80, 150, 150, 40, WHITE, BLACK, BLACK, "", 2);
 therm3_btn.initButton(&tft,  80, 200, 150, 40, WHITE, BLACK, BLACK, "", 2);
 therm1_btn.drawButton(false);
 therm2_btn.drawButton(false);
 therm3_btn.drawButton(false);

 PreviewMenu_btn.initButton(&tft,  40, 400, 50, 40, WHITE, CYAN, BLACK, " < ", 3);
 NextMenu_btn.initButton(&tft,    120, 400, 50, 40, WHITE, CYAN, BLACK, " > ", 3);
 PreviewMenu_btn.drawButton(false);
 NextMenu_btn.drawButton(false);

//tft.drawBitmap(220, 0, tractor_128x64, 128, 64, GREEN);

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
     header1("Μπόϊλερ");
     PreviewMenu_btn.drawButton();
     NextMenu_btn.drawButton();
     dispMenu = false ;
 
     u8g2_for_adafruit_gfx.setFontMode(1); 
     u8g2_for_adafruit_gfx.setForegroundColor(WHITE);  
     u8g2_for_adafruit_gfx.setFont(u8g2_font_10x20_t_greek); 
     tft.fillRect(50,250, 220,40,BLACK); 
     u8g2_for_adafruit_gfx.setCursor(50,280);             
     u8g2_for_adafruit_gfx.print( "θερμ. Νερών Μπόϊλερ"); 

     u8g2_for_adafruit_gfx.setCursor(20,100);                // start writing at this position
     u8g2_for_adafruit_gfx.print( "Λέβητας");  
     u8g2_for_adafruit_gfx.setCursor(20,150);                // start writing at this position
     u8g2_for_adafruit_gfx.print( "Κυκλοφοριτής");
     u8g2_for_adafruit_gfx.setCursor(20,201);                // start writing at this position
     u8g2_for_adafruit_gfx.print( "Μπόϊλερ    "); 

    }  
       
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
   //---------------------- θερμοκρασία ΜπόΙλερ---------------------------
      if (millis() - previousMillis2 >= (intervalDisp2 * timer2 )  ) {
        previousMillis2 = millis();   

        sensors.requestTemperatures ();
        therm03=(sensors.getTempCByIndex(2)); 
        delay(100) ;       

       tft.setTextColor(WHITE);
       tft.fillRect(80,300,120,50,BLACK);
       tft.setTextSize(3); 
       tft.setTextColor(WHITE);
       tft.setCursor(80,300);
       tft.print( therm03);
       tft.setTextSize(2);
     }
  //----------------------------------------------------------------------
 }   
   
}
