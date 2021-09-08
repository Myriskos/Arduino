
//--------------------------------------------
void menu2(){
//--------------------------------------------

 therm1_btn.initButton(&tft,  60, 100, 120, 40, WHITE, CYAN, BLACK, "Lebhtas2", 2);
 therm2_btn.initButton(&tft,  60, 150, 120, 40, WHITE, CYAN, BLACK, "kiklofo2", 2);
 therm3_btn.initButton(&tft,  60, 200, 120, 40, WHITE, CYAN, BLACK, "boiller2", 2);
 therm1_btn.drawButton(false);
 therm2_btn.drawButton(false);
 therm3_btn.drawButton(false);

 PreviewMenu_btn.initButton(&tft,  40, 300, 50, 40, WHITE, CYAN, BLACK, " < ", 3);
 NextMenu_btn.initButton(&tft,    120, 300, 50, 40, WHITE, CYAN, BLACK, " > ", 3);
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

     header1("-EPILOGES2-");
     
     tft.setCursor(140,90);
     tft.print(  therm1  );
//     if ( therm0 >= therm1 ) {
//        tft.fillRect(210,90, 20,20, RED) ;    digitalWrite(Relay_01,HIGH);
//     }  
//     else if ( therm0 <= therm1-2 ) {  
//        tft.fillRect(210,90, 20,20, GREEN) ;  digitalWrite(Relay_01,LOW);
//     }   
//     else tft.fillRect(210,90, 20,20, YELLOW) ;
        
     tft.setCursor(140,140);
     tft.print(  therm2  );
//     if ( therm0 >= therm2 ) {
//        tft.fillRect(210,140, 20,20, GREEN);  digitalWrite(Relay_02,LOW);
//     }  
//     else if ( therm0 <= therm2-2 ) {  
//        tft.fillRect(210,140, 20,20, RED) ;   digitalWrite(Relay_02,HIGH);
//     }  
//     else tft.fillRect(210,140, 20,20, YELLOW) ; 
  
     tft.setCursor(140,190);
     tft.print(  therm3  );
//     if ( therm0 >= therm3 ) {
//        tft.fillRect(210,190, 20,20, GREEN);  digitalWrite(Relay_03,LOW);
//     }  
//     else if  ( therm0 <= therm3-2 ) {   
//        tft.fillRect(210,190, 20,20, RED)  ;  digitalWrite(Relay_03,HIGH);
//     }   
//     else tft.fillRect(210,190, 20,20, YELLOW)  ;
     
     tft.setTextSize(3); 
     tft.setCursor(80,240);
     tft.print(  therm0  );
     tft.setTextSize(2);
   //-------------------------------------------
//     tft.setFont(&Greek_Sigismundus10pt7b);
//     tft.setTextSize(1);
//     tft.setTextColor(BLACK);
    
     therm1_btn.drawButton();
     therm2_btn.drawButton();
     therm3_btn.drawButton();
     PreviewMenu_btn.drawButton();
     NextMenu_btn.drawButton();
//
//     tft.setFont();
//     tft.setTextSize(2);
   //----------------------------------------
     
     dispMenu = false ;
    }  
    
    if (therm1_btn.justPressed()) {
        therm1_btn.drawButton(true);
        therm1 =   therm_setup( "Lebhtas2" , therm1   ) ;
        EEPROM.put( 10,therm1);
    }
    if (therm2_btn.justPressed()) {
        therm2_btn.drawButton(true);
        therm2 =   therm_setup( "Kykloforhths2" , therm2   ) ;
        EEPROM.put( 20,therm2);
    }
    if (therm3_btn.justPressed()) {
        therm3_btn.drawButton(true);
        therm3 =   therm_setup( "Boyller2" , therm3   ) ;
        EEPROM.put( 30,therm3);
    }  

    if (NextMenu_btn.justPressed()) {
        NextMenu_btn.drawButton(true);
        MenuCount++ ;
        if ( MenuCount  > 2  ) {
          MenuCount = 2 ;
        } 
        therm0 = therm0 +0.50 ; dispMenu = true ; tft.fillRect(80,240, 100,20,BLACK);
        //  therm0++ ; dispMenu = true ; tft.fillRect(80,240, 100,20,BLACK);
        save_therm1 = false ;
    }  

    if (PreviewMenu_btn.justPressed()) {
        PreviewMenu_btn.drawButton(true);
        MenuCount-- ;
        if ( MenuCount < 1  ) {
          MenuCount = 1 ;
        }
        therm0 = therm0 -0.50 ; dispMenu = true ; tft.fillRect(80,240, 100,20,BLACK);
        //therm0-- ; dispMenu = true ; tft.fillRect(80,240, 100,20,BLACK);
        save_therm1 = false ;
    }
  
 }   
   
}
