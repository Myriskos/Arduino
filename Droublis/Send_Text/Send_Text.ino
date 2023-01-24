

/**
 * This example showes how to send text Email.
 *
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: suwatchai@outlook.com
 *
 * Github: https://github.com/mobizt/ESP-Mail-Client
 *
 * Copyright (c) 2022 mobizt
 *
 */

//-------------------------------------------------------------
//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
//#define REMOTEXY__DEBUGLOG 

#if defined (ESP8266)
  #include <ESP8266WiFi.h>
#elif defined (ESP32)
  #include <WiFi.h>  
#endif

#include <RemoteXY.h>

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,1,0,27,0,10,13,2,
  1,0,9,9,46,46,6,7,50,50,
  2,31,88,0,65,4,62,16,31,31,
  14,62,35,35 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 

    // output variables
  uint8_t led_1_r; // =0..255 LED Red brightness 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)



/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

//-------auto connect---------------------------
  #include <WiFiManager.h>
  char con_ssid[32]; //will hold the ssid of the wlan to which it is connectd
  char con_psk[64];  // ^^ private shared key for the wlan (password)
 //------- end auto connect-------------------------
//--------------------------------------------------------------
/////---#include <Arduino.h>

#include <ESP_Mail_Client.h>

//#define con_ssid "VODAFONE_0112"
//#define con_psk "hu2tar4f5542smcc"

/** For Gmail, the app password will be used for log in
 *  Check out https://github.com/mobizt/ESP-Mail-Client#gmail-smtp-and-imap-required-app-passwords-to-sign-in
 *
 * For Yahoo mail, log in to your yahoo mail in web browser and generate app password by go to
 * https://login.yahoo.com/account/security/app-passwords/add/confirm?src=noSrc
 *
 * To use Gmai and Yahoo's App Password to sign in, define the AUTHOR_PASSWORD with your App Password
 * and AUTHOR_EMAIL with your account email.
 */

/** The smtp host name e.g. smtp.gmail.com for GMail or smtp.office365.com for Outlook or smtp.mail.yahoo.com */
#define SMTP_HOST "smtp.mail.yahoo.com"

/** The smtp port e.g.
 * 25  or esp_mail_smtp_port_25
 * 465 or esp_mail_smtp_port_465
 * 587 or esp_mail_smtp_port_587
 */
#define SMTP_PORT esp_mail_smtp_port_25 // port 465 is not available for Outlook.com

/* The log in credentials */
#define AUTHOR_EMAIL "myriskos@yahoo.gr"
#define AUTHOR_PASSWORD "zylnocgpmjiqtdzg"

/* Declare the global used SMTPSession object for SMTP transport */
SMTPSession smtp;

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);

const char rootCACert[] PROGMEM = "-----BEGIN CERTIFICATE-----\n"
                                  "-----END CERTIFICATE-----\n";
CRemoteXY *remotexy;

bool lSend = false ;

void setup(){

  Serial.begin(115200);

#if defined(ARDUINO_ARCH_SAMD)
  while (!Serial)
    ;
  Serial.println();
  Serial.println("**** Custom built WiFiNINA firmware need to be installed.****\nTo install firmware, read the instruction here, https://github.com/mobizt/ESP-Mail-Client#install-custom-built-wifinina-firmware");
#endif

  Serial.println();
  Serial.print("Connecting to AP");
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);  //  
  StartConect();
  StartRemoteXY();

}

void loop(){

   remotexy->handler ();
  
  if (RemoteXY.button_1){
    RemoteXY.led_1_r = 255;
     if (!lSend ){  
        SendMail(" Αυτό ειναι ενα Δοκιμαστικο Mail απο το ESP8266");
        delay(100);
        lSend = true ;
     }
  }
  else {
    RemoteXY.led_1_r = 0 ;
    lSend = false ;
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

void StartRemoteXY(){

 CRemoteXYComm_WiFi * wifi =  new CRemoteXYComm_WiFi (
    con_ssid,                            // REMOTEXY_WIFI_SSID
    con_psk                                 // REMOTEXY_WIFI_PASSWORD
  );
  
  remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, "");
  
  remotexy->addConnection (new CRemoteXYConnectionServer ( wifi, 
    6377                                      // REMOTEXY_SERVER_PORT
  ));
  
  remotexy->addConnection (new CRemoteXYConnectionCloud ( wifi, 
    "cloud.remotexy.com",                     // REMOTEXY_CLOUD_SERVER 
    6376,                                     // REMOTEXY_CLOUD_PORT
    "fe907fb1cef195e8720675bdee8c869e"                // REMOTEXY_CLOUD_TOKEN
  ));
}



//------------send mail-------------  
void SendMail( String textMsg  ){
   /*  Set the network reconnection option */
  MailClient.networkReconnect(true);

  /** Enable the debug via Serial port
   * 0 for no debugging
   * 1 for basic level debugging
   *
   * Debug port can be changed via ESP_MAIL_DEFAULT_DEBUG_PORT in ESP_Mail_FS.h
   */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the ESP_Mail_Session for user defined session credentials */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = F("yahoo.gr");

  /* Set the NTP config time */
  session.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  session.time.gmt_offset = 3;
  session.time.day_light_offset = 0;

  /** In ESP32, timezone environment will not keep after wake up boot from sleep.
   * The local time will equal to GMT time.
   *
   * To sync or set time with NTP server with the valid local time after wake up boot,
   * set both gmt and day light offsets to 0 and assign the timezone environment string e.g.

     session.time.ntp_server = F("pool.ntp.org,time.nist.gov");
     session.time.gmt_offset = 0;
     session.time.day_light_offset = 0;
     session.time.timezone_env_string = "JST-9"; // for Tokyo

   * The library will get (sync) the time from NTP server without GMT time offset adjustment
   * and set the timezone environment variable later.
   *
   * This timezone environment string will be stored to flash or SD file named "/tz_env.txt"
   * which set via session.time.timezone_file.
   *
   * See the timezone environment string list from
   * https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
   *
   */

  /* Declare the message class */
  SMTP_Message message;
  message.text.charSet = F("UTF-8");
  /* Set the message headers */
  message.sender.name = F("ESP Mail"); // This witll be used with 'MAIL FROM' command and 'From' header field.
  message.sender.email = AUTHOR_EMAIL; // This witll be used with 'From' header field.
  message.subject = F("ESP8266 sending plain text Email");
  message.addRecipient(F("Afoi Droumplh OE "), F("info@dbsoft.gr")); // This will be used with RCPT TO command and 'To' header field.

  //String textMsg = " Αυτό ειναι ενα Δοκιμαστικο Mail απο το ESP8266";
  message.text.content = textMsg;

  /** If the message to send is a large string, to reduce the memory used from internal copying  while sending,
   * you can assign string to message.text.blob by cast your string to uint8_t array like this
   *
   * String myBigString = "..... ......";
   * message.text.blob.data = (uint8_t *)myBigString.c_str();
   * message.text.blob.size = myBigString.length();
   *
   * or assign string to message.text.nonCopyContent, like this
   *
   * message.text.nonCopyContent = myBigString.c_str();
   *
   * Only base64 encoding is supported for content transfer encoding in this case.
   */

  /** The Plain text message character set e.g.
   * us-ascii
   * utf-8
   * utf-7
   * The default value is utf-8
   */

  /** The content transfer encoding e.g.
   * enc_7bit or "7bit" (not encoded)
   * enc_qp or "quoted-printable" (encoded)   
   * enc_base64 or "base64" (encoded)
   * enc_binary or "binary" (not encoded)
   * enc_8bit or "8bit" (not encoded)
   * The default value is "7bit"
   */
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
 
  // If this is a reply message
  // message.in_reply_to = "<parent message id>";
  // message.references = "<parent references> <parent message id>";

  /** The message priority
   * esp_mail_smtp_priority_high or 1
   * esp_mail_smtp_priority_normal or 3
   * esp_mail_smtp_priority_low or 5
   * The default value is esp_mail_smtp_priority_low
   */
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;

  // message.response.reply_to = "myriskosarduino@gmail.com ";
  // message.response.return_path = "someone@somemail.com";

  /** The Delivery Status Notifications e.g.
   * esp_mail_smtp_notify_never
   * esp_mail_smtp_notify_success
   * esp_mail_smtp_notify_failure
   * esp_mail_smtp_notify_delay
   * The default value is esp_mail_smtp_notify_never
   */
  // message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Set the custom message header */
  message.addHeader(F("Message-ID: <info.dbsoft@gmail.com>"));

  // For Root CA certificate verification (ESP8266 and ESP32 only)
  // session.certificate.cert_data = rootCACert;
  // or
  // session.certificate.cert_file = "/path/to/der/file";
  // session.certificate.cert_file_storage_type = esp_mail_file_storage_type_flash; // esp_mail_file_storage_type_sd
  // session.certificate.verify = true;

  // The WiFiNINA firmware the Root CA certification can be added via the option in Firmware update tool in Arduino IDE

  /* Connect to server with the session config */

  // Library will be trying to sync the time with NTP server if time is never sync or set.
  // This is 10 seconds blocking process.
  // If time synching was timed out, the error "NTP server time synching timed out" will show via debug and callback function.
  // You can manually sync time by yourself with NTP library or calling configTime in ESP32 and ESP8266.
  // Time can be set manually with provided timestamp to function smtp.setSystemTime.

 
  /* Connect to the server */
  if (!smtp.connect(&session /* session credentials */))
      return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

  // to clear sending result log
  // smtp.sendingResult.clear();

  ESP_MAIL_PRINTF("Free Heap: %d\n", MailClient.getFreeHeap());

  //---------- end send mail--------------



}


/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status)
{
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success())
  {
    // ESP_MAIL_PRINTF used in the examples is for format printing via debug Serial port
    // that works for all supported Arduino platform SDKs e.g. AVR, SAMD, ESP32 and ESP8266.
    // In ESP8266 and ESP32, you can use Serial.printf directly.

    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
    Serial.println("----------------\n");

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);

      // In case, ESP32, ESP8266 and SAMD device, the timestamp get from result.timestamp should be valid if
      // your device time was synched with NTP server.
      // Other devices may show invalid timestamp as the device time was not set i.e. it will show Jan 1, 1970.
      // You can call smtp.setSystemTime(xxx) to set device time manually. Where xxx is timestamp (seconds since Jan 1, 1970)
      time_t ts = (time_t)result.timestamp;

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %s\n", asctime(localtime(&ts)));
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");

    // You need to clear sending result as the memory usage will grow up.
    smtp.sendingResult.clear();
  }
}
