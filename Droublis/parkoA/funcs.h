
//-----------------
String macToStr(const uint8_t* mac){
//-----------------  
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  
  return result;
}

//------------------------------------------
 void MailYahoo( String mess ){
//------------------------------------------
   // WiFi.begin(con_ssid, con_psk);
    EMailSender::EMailMessage message;
    message.subject = "Esp8266NodeMCU";
    message.mime = MIME_TEXT_PLAIN;   //
    message.message = mess ;
 
    EMailSender::Response resp = emailSend.send("info.dbsoft@gmail.com", message);
 //   EMailSender::Response resp2 = emailSend.send("myriskos@yahoo.gr", message);
 //   EMailSender::Response resp2 = emailSend.send("afoidroubli@gmail.com", message);
  
    Serial.println("Sending status: ");
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);

 //   Serial.println(resp2.status);
 //   Serial.println(resp2.code);
 //   Serial.println(resp2.desc); 
    
    myData.b = resp.status ;
}
//------------------------------------------ 
 void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
//------------------------------------------
  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.mess);
  
//  Serial.print("Bool: ");
//  Serial.println(myData.panelA);
 
  mac_esp = macToStr(mac) ;
  Serial.println( macToStr(mac) ); 
  Serial.println();

   if  ( macToStr(mac) == "a4:cf:12:df:58:21"  && myData.panelA  ) {
       trap_A = true ;       
   }
   else {
      trap_A = false ;
   }
   
   if  ( macToStr(mac) == "a4:cf:12:df:58:22"  && myData.panelB  ) {
       trap_B = true ;
   }
    else {
      trap_B = false ;
   }
   
   if  ( macToStr(mac) == "98:f4:ab:b3:8f:b8"  && myData.panelC  ) {
       trap_C = true ;
   }
   if  ( macToStr(mac) == "2c:f4:32:7a:5:18"  && myData.panelD  ) {
       trap_D = true ;
   }
   
    strcpy( RemoteXY.text_1 , myData.mess );
    strcpy (RemoteXY.text_2 ,con_ssid  ) ;
    
   //---------------------------------------
   if ( trap_A ) {
    RemoteXY.led_2=1;
    strcpy(myData.mess, "Το PANEL A εχει πρόβλημα") ;
    strcpy( RemoteXY.text_1 , myData.mess );
   }
   else {
    RemoteXY.led_2=0;
    if ( trap_A ) {
     Serial.println( "Το πρόβλημα στο PANEL A αποκαταστάθηκε " );
     Serial.println();
    }
    trap_A = false ;
   }
  //--------------------------------------------
  if ( trap_B ) {
    RemoteXY.led_3=1;
    strcpy(myData.mess, "Το PANEL B εχει πρόβλημα") ;
    strcpy( RemoteXY.text_1 , myData.mess );
   }
   else {
    RemoteXY.led_3=0;
    if ( trap_B ) {
     Serial.println( "Το πρόβλημα στο PANEL B αποκαταστάθηκε " );
     Serial.println();
    }
    trap_B = false ;
   }
  //--------------------------------------------

  if ( parkoA ) {
    strcpy(myData.mess, "Διακοπη στο πάρκο A");
    strcpy( RemoteXY.text_1 , myData.mess );
  }
}


void StartConect(){
    //------------Start autoConnect---- 
    WiFiManager wifiManager;
    // wifiManager.resetSettings();
    wifiManager.setTimeout(180); 
    if (!wifiManager.autoConnect("WiFi-ESP_A", "12345678")) // credenziali per accedere alla modalità AP
    {
      delay(3000);
      ESP.reset();
      delay(5000);
    }
    WiFi.SSID().toCharArray(con_ssid, 32);
    WiFi.psk().toCharArray(con_psk, 64);
     
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
   //------------end autoConnect-----------
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
