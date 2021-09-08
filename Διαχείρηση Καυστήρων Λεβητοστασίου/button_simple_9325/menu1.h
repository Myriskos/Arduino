//--------------------------------------------
void menu1(){
//--------------------------------------------

 therm1_btn.initButton(&tft,  60, 100, 100, 40, WHITE, CYAN, BLACK, "levitas1", 2);
 therm2_btn.initButton(&tft,  60, 150, 100, 40, WHITE, CYAN, BLACK, "kiklofo1", 2);
 therm3_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "boiller1", 2);
 therm1_btn.drawButton(false);
 therm2_btn.drawButton(false);
 therm3_btn.drawButton(false);

 PreviewMenu_btn.initButton(&tft,  40, 300, 50, 40, WHITE, CYAN, BLACK, " < ", 3);
 NextMenu_btn.initButton(&tft,    120, 300, 50, 40, WHITE, CYAN, BLACK, " > ", 3);
 mode_btn.initButton(&tft,    200, 300, 50, 40, WHITE, RED, BLACK, "Mode", 2);
 PreviewMenu_btn.drawButton(false);
 NextMenu_btn.drawButton(false);
 mode_btn.drawButton(false);


 bool While_menu = true ;
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
      sensors.requestTemperatures ();
    //  therm03=(sensors.getTempCByIndex(2)); 
 
    String Shead = "" ;
    if (Pellet_on){
     Shead =  "Pellet" ;
    // therm0=(sensors.getTempCByIndex(0));  
    // delay(100) ;
    }
    else if (Oil_on) {
     Shead =  " Oil  " ; 
    // therm0=(sensors.getTempCByIndex(1));  
    // delay(100) ;
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
       mode_btn.drawButton();

   // if (therm0 < 0 ) ; goto ReadSensor ; 
   
     if (therm0 < 0 ){ 
      continue;
     }
     dispMenu = false ;
   
 }  
       //------------------------ ��������� ������������ ----
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
 
            //sensors.requestTemperatures ();
            //therm03=(sensors.getTempCByIndex(2));
              String Shead = "" ;
              if (Pellet_on){
               Shead =  "Pellet" ;
               Levitas = "L01" ;
              // therm0=(sensors.getTempCByIndex(0));  
              // delay(100) ;
              }
              else if (Oil_on) {
               Shead =  " Oil  " ;
               Levitas = "L02" ; 
              // therm0=(sensors.getTempCByIndex(1));  
              // delay(100) ;
             }
              else {
               Shead =  " No Mode " ; 
              }
         //-------------------------------------------
       
           strSendSereal = String('T')+String(therm0)+String('T')+String(therm3); 
           strSendSereal+= String('T')+String(therm1)+String('T')+String(therm2)+String('T')+String(therm3); 
           strSendSereal+= String( Levitas ) ;
           strSendSereal+= String( CL )+String( CK)+String( CB ) ;
           SerialMega.println(strSendSereal);
        Serial.println(strSendSereal);
           if (millis() - previousMillis >= (intervalDisp * timer )  ) {
             previousMillis = millis();  
             dispScreen() ; 
           }
  
         //---------------------------------------------
  
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
