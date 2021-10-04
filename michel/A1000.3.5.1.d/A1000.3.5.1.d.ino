
//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ETHERNET_LIB_CLOUD
#include <Ethernet.h>
/* Ethernet shield used pins: 10(SS) */
#include <SPI.h>
/* SPI interface used pins: 51(MOSI), 50(MISO), 52(SCK) */

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_ETHERNET_MAC "FA:CE:AA:10:00:0A"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "ae12ea2b904f223f14264c281398a999"


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255, 101, 0, 174, 0, 167, 4, 11, 13, 4,
  67, 5, 28, 0, 42, 13, 1, 2, 26, 6,
  65, 36, 8, 0, 9, 9, 1, 65, 36, 81,
  0, 9, 9, 1, 65, 6, 9, 13, 8, 8,
  1, 65, 2, 29, 17, 6, 6, 1, 65, 2,
  41, 17, 6, 6, 1, 65, 2, 52, 17, 6,
  6, 1, 65, 2, 64, 17, 6, 6, 1, 65,
  6, 81, 13, 8, 8, 1, 129, 0, 10, 9,
  7, 4, 1, 17, 97, 95, 76, 0, 129, 0,
  8, 21, 10, 4, 1, 17, 72, 69, 65, 84,
  0, 129, 0, 82, 9, 7, 4, 1, 17, 97,
  95, 72, 0, 129, 0, 80, 21, 10, 4, 1,
  17, 67, 79, 79, 76, 0, 129, 0, 31, 14,
  2, 3, 1, 17, 49, 0, 129, 0, 43, 14,
  2, 3, 1, 17, 50, 0, 129, 0, 54, 14,
  2, 3, 1, 17, 51, 0, 129, 0, 66, 14,
  2, 3, 1, 17, 52, 0, 131, 1, 1, 53,
  17, 7, 1, 2, 31, 72, 79, 77, 69, 0,
  131, 0, 22, 53, 17, 7, 2, 2, 31, 84,
  69, 77, 80, 0, 7, 45, 51, 6, 20, 6,
  2, 2, 26, 2, 5, 7, 45, 51, 18, 20,
  6, 2, 2, 26, 2, 5, 7, 45, 51, 30,
  20, 6, 2, 2, 26, 2, 5, 7, 45, 51,
  42, 20, 6, 2, 2, 26, 2, 5, 7, 45,
  51, 6, 20, 6, 3, 2, 26, 2, 5, 7,
  45, 51, 18, 20, 6, 3, 2, 26, 2, 5,
  7, 45, 51, 30, 20, 6, 3, 2, 26, 2,
  5, 7, 45, 51, 42, 20, 6, 3, 2, 26,
  2, 5, 129, 0, 60, 2, 2, 4, 2, 17,
  49, 0, 129, 0, 57, 14, 6, 4, 2, 17,
  49, 45, 50, 0, 129, 0, 57, 26, 6, 4,
  2, 17, 50, 45, 51, 0, 129, 0, 57, 38,
  6, 4, 2, 17, 51, 45, 52, 0, 129, 0,
  36, 3, 11, 4, 3, 17, 67, 79, 79, 76,
  0, 129, 0, 37, 15, 10, 4, 3, 17, 72,
  69, 65, 84, 0, 129, 0, 39, 27, 7, 4,
  3, 17, 97, 95, 72, 0, 129, 0, 39, 38,
  7, 4, 3, 17, 97, 95, 76, 0, 67, 5,
  19, 6, 14, 6, 2, 2, 26, 6, 67, 5,
  19, 18, 14, 6, 2, 2, 26, 6, 67, 5,
  19, 30, 14, 6, 2, 2, 26, 6, 67, 5,
  19, 42, 14, 6, 2, 2, 26, 6, 67, 5,
  19, 6, 14, 6, 3, 2, 26, 6, 67, 5,
  19, 18, 14, 6, 3, 2, 26, 6, 67, 5,
  19, 30, 14, 6, 3, 2, 26, 6, 67, 5,
  19, 42, 14, 6, 3, 2, 26, 6, 129, 0,
  25, 2, 2, 4, 2, 17, 49, 0, 129, 0,
  25, 14, 2, 4, 2, 17, 50, 0, 129, 0,
  25, 26, 2, 4, 2, 17, 51, 0, 129, 0,
  25, 38, 2, 4, 2, 17, 52, 0, 1, 1,
  81, 5, 10, 8, 2, 1, 31, 79, 75, 0,
  131, 0, 42, 53, 17, 7, 3, 2, 31, 65,
  76, 65, 82, 0, 7, 37, 44, 6, 48, 6,
  4, 2, 26, 2, 14, 129, 0, 26, 1, 41,
  6, 4, 17, 84, 69, 76, 69, 80, 72, 79,
  78, 69, 32, 49, 0, 7, 37, 44, 19, 48,
  6, 4, 2, 26, 2, 14, 129, 0, 27, 14,
  41, 6, 4, 17, 84, 69, 76, 69, 80, 72,
  79, 78, 69, 32, 50, 0, 7, 37, 44, 32,
  48, 6, 4, 2, 26, 2, 14, 129, 0, 27,
  27, 41, 6, 4, 17, 84, 69, 76, 69, 80,
  72, 79, 78, 69, 32, 51, 0, 7, 53, 53,
  44, 21, 6, 4, 2, 26, 2, 129, 0, 40,
  39, 15, 6, 4, 17, 66, 69, 76, 76, 0,
  1, 1, 78, 43, 10, 8, 4, 1, 31, 79,
  75, 0, 67, 5, 0, 6, 42, 6, 4, 2,
  26, 14, 67, 5, -1, 19, 43, 6, 4, 2,
  26, 14, 67, 5, -1, 32, 43, 6, 4, 2,
  26, 14, 67, 5, 23, 44, 20, 6, 4, 2,
  26, 11, 65, 44, 57, 23, 8, 6, 1, 129,
  0, 55, 29, 12, 2, 1, 17, 80, 79, 87,
  69, 82, 45, 79, 70, 70, 0, 1, 1, 93,
  5, 12, 8, 4, 1, 31, 79, 75, 0, 1,
  1, 93, 18, 12, 8, 4, 1, 31, 79, 75,
  0, 1, 1, 93, 31, 12, 8, 4, 1, 31,
  79, 75, 0, 2, 1, 0, 35, 22, 11, 1,
  1, 89, 31, 31, 79, 78, 0, 79, 70, 70,
  0, 2, 1, 78, 35, 22, 11, 1, 1, 89,
  31, 31, 79, 78, 0, 79, 70, 70, 0, 129,
  0, 8, 32, 7, 3, 1, 17, 69, 88, 45,
  49, 0, 129, 0, 86, 32, 8, 3, 1, 17,
  69, 88, 45, 50, 0, 129, 0, 41, 48, 19,
  4, 1, 95, 206, 156, 206, 145, 206, 167, 206,
  145, 206, 164, 206, 159, 206, 163, 0, 65, 44,
  34, 23, 8, 6, 1, 129, 0, 32, 29, 11,
  2, 1, 17, 111, 110, 108, 121, 66, 97, 116,
  116, 101, 114, 121, 0, 1, 1, 81, 17, 10,
  8, 2, 1, 31, 79, 75, 0, 1, 1, 81,
  29, 10, 8, 2, 1, 31, 79, 75, 0, 1,
  1, 81, 41, 10, 8, 2, 1, 31, 79, 75,
  0, 1, 1, 81, 5, 10, 8, 3, 1, 31,
  79, 75, 0, 1, 1, 81, 17, 10, 8, 3,
  1, 31, 79, 75, 0, 1, 1, 81, 29, 10,
  8, 3, 1, 31, 79, 75, 0, 1, 1, 81,
  41, 10, 8, 3, 1, 31, 79, 75, 0, 131,
  0, 62, 53, 17, 7, 4, 2, 31, 84, 69,
  76, 0, 2, 0, 51, 42, 20, 6, 5, 229,
  91, 31, 31, 79, 78, 0, 79, 70, 70, 0,
  131, 0, 82, 53, 17, 7, 5, 2, 31, 84,
  73, 77, 69, 0, 129, 0, 45, 34, 9, 3,
  1, 17, 84, 73, 77, 69, 82, 0, 129, 0,
  34, 2, 17, 5, 5, 17, 82, 69, 76, 65,
  89, 0, 129, 0, 32, 14, 19, 5, 5, 17,
  116, 105, 109, 101, 32, 79, 78, 0, 67, 5,
  19, 6, 14, 6, 5, 2, 26, 11, 67, 5,
  19, 18, 14, 6, 5, 2, 26, 11, 7, 53,
  51, 6, 20, 6, 5, 2, 26, 2, 7, 53,
  51, 18, 20, 6, 5, 2, 26, 2, 1, 1,
  81, 5, 10, 8, 5, 1, 31, 79, 75, 0,
  1, 1, 81, 17, 10, 8, 5, 1, 31, 79,
  75, 0, 67, 5, 19, 42, 14, 6, 5, 2,
  26, 11, 129, 0, 33, 38, 19, 5, 5, 17,
  79, 78, 47, 79, 70, 70, 0, 1, 1, 81,
  41, 10, 8, 5, 1, 31, 79, 75, 0, 67,
  5, 42, 37, 16, 7, 1, 18, 26, 11, 7,
  53, 51, 30, 20, 6, 5, 2, 26, 2, 1,
  1, 81, 29, 10, 8, 5, 1, 31, 79, 75,
  0, 67, 5, 19, 30, 14, 6, 5, 2, 26,
  11, 129, 0, 32, 26, 22, 5, 5, 17, 116,
  105, 109, 101, 32, 79, 70, 70, 0
};

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  float edit_1;
  float edit_2;
  float edit_3;
  float edit_4;
  float edit_5;
  float edit_6;
  float edit_7;
  float edit_8;
  uint8_t therm; // =1 if button pressed, else =0
  char tel_1_edit[14];  // string UTF8 end zero
  char tel_2_edit[14];  // string UTF8 end zero
  char tel_3_edit[14];  // string UTF8 end zero
  int16_t bell_edit;  // 32767.. +32767
  uint8_t button_2; // =1 if button pressed, else =0
  uint8_t button_3; // =1 if button pressed, else =0
  uint8_t button_4; // =1 if button pressed, else =0
  uint8_t button_5; // =1 if button pressed, else =0
  uint8_t ex_1; // =1 if switch ON and =0 if OFF
  uint8_t ex_2; // =1 if switch ON and =0 if OFF
  uint8_t diff_1; // =1 if button pressed, else =0
  uint8_t diff_2; // =1 if button pressed, else =0
  uint8_t diff_3; // =1 if button pressed, else =0
  uint8_t cool; // =1 if button pressed, else =0
  uint8_t heat; // =1 if button pressed, else =0
  uint8_t a_H; // =1 if button pressed, else =0
  uint8_t a_L; // =1 if button pressed, else =0
  uint8_t timerONOFF; // =1 if switch ON and =0 if OFF
  int16_t edit_9;  // 32767.. +32767
  int16_t edit_10;  // 32767.. +32767
  uint8_t button_1; // =1 if button pressed, else =0
  uint8_t button_6; // =1 if button pressed, else =0
  uint8_t button_mem_time; // =1 if button pressed, else =0
  int16_t edit_11;  // 32767.. +32767
  uint8_t button_7; // =1 if button pressed, else =0

  // output variables
  char text_1[6];  // string UTF8 end zero
  uint8_t led_1_r; // =0..255 LED Red brightness
  uint8_t led_2_r; // =0..255 LED Red brightness
  uint8_t led_3_r; // =0..255 LED Red brightness
  uint8_t led_3_g; // =0..255 LED Green brightness
  uint8_t led_4_g; // =0..255 LED Green brightness
  uint8_t led_5_g; // =0..255 LED Green brightness
  uint8_t led_6_g; // =0..255 LED Green brightness
  uint8_t led_7_g; // =0..255 LED Green brightness
  uint8_t led_8_r; // =0..255 LED Red brightness
  uint8_t led_8_g; // =0..255 LED Green brightness
  char text_2[6];  // string UTF8 end zero
  char text_3[6];  // string UTF8 end zero
  char text_4[6];  // string UTF8 end zero
  char text_5[6];  // string UTF8 end zero
  char text_6[6];  // string UTF8 end zero
  char text_7[6];  // string UTF8 end zero
  char text_8[6];  // string UTF8 end zero
  char text_9[6];  // string UTF8 end zero
  char tel_1_text[14];  // string UTF8 end zero
  char tel_2_text[14];  // string UTF8 end zero
  char tel_3_text[14];  // string UTF8 end zero
  char bell_text[11];  // string UTF8 end zero
  uint8_t led_power_r; // =0..255 LED Red brightness
  uint8_t onlyBattery_led_r; // =0..255 LED Red brightness
  char text_10[11];  // string UTF8 end zero
  char text_11[11];  // string UTF8 end zero
  char text_12[11];  // string UTF8 end zero
  char text_13[11];  // string UTF8 end zero
  char text_14[11];  // string UTF8 end zero

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////




//βιβλιοθηκη για αποθηκευση στην EEPROM
#include <EEPROM.h>

//βιβλιοθηκη για σειριακη
//#include <SoftwareSerial.h>

// βιβλιοθηκη για οθονη LCD I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// βιβλιοθηκη για αισθητηρας θερμοκρασιας DS18B20
#include <DallasTemperature.h>
#include <OneWire.h>

//Create software serial object to communicate with SIM800L
//SoftwareSerial mySerial(18, 19); //SIM800L (Rx,Tx  > Tx,Rx)is connected to Arduino #3 & #2

//οθονη LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); //δηλωση πινακων I2C

//αισθητηρας θερμοκρασιας DS18B20
#define ONE_WIRE_BUS 14 //δηλωση pin δεδομενων στο 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); //Σχετίζουμε την Onewire στον Dallas Temperature

//δικοι μου χαρακτηρες
uint8_t pano[] = {0x04, 0x0E, 0x0E, 0x1F, 0x1F, 0x04, 0x04, 0x04};
uint8_t kato[] = {0x04, 0x04, 0x04, 0x1F, 0x1F, 0x0E, 0x0E, 0x04};
uint8_t velos_aristera[] = {0x02, 0x06, 0x0E, 0x1F, 0x1F, 0x0E, 0x06, 0x02};
uint8_t velos_dexia[] = {0x08, 0x0C, 0x0E, 0x1F, 0x1F, 0x0E, 0x0C, 0x08};
uint8_t priza[] = {0x06, 0x08, 0x04, 0x0E, 0x1F, 0x1F, 0x0A, 0x0A};
uint8_t keraunos[] = {0x03, 0x06, 0x08, 0x04, 0x02, 0x14, 0x18, 0x1C};
uint8_t diktis[] = {0x00, 0x18, 0x1C, 0x1E, 0x1E, 0x1C, 0x18, 0x00};
uint8_t kampana[] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};

//ορισμος θερμομετρου
float therm_1;

//ορισμος τιμων θερμοκρασιων
float therm_T1    ;
float proti_D ;
float deuteri_D  ;
float triti_D  ;
float alarm_high ;
float alarm_low ;
float therm_T2 ;
float therm_T3 ;
float therm_T4 ;
float COOL ;
float HEAT ;

//ποσο αυξομοιωσης θερμοκρασιων
float how_match = 0.10 ;
// μεγιστη και ελαχιστη διαφορα μεταξη των θερμοκρασιων
float temp_diff_min = 1.50;
float temp_diff_max = 9.00;

//το mode χρησιμοποιητε για τον τροπο λειτουργιας ρελε
uint8_t mode ;

//το menu χρησιμοποιητε για τα μπουτον του menu
uint8_t menu = 0;
bool central_menu = false;
int DelayMenu = 150;
// για ενεργοποιηση κεντρικης οθονης
bool update_Screen = true ;
//για ενεργοποιηση των μοτερ με θερμοκρασιες
bool Moto_Run      = true ;

//ορισμος εξοδων ρελε
const int tax_01 = A15 ;
const int tax_02 = A14 ;
const int tax_03 = A13 ;
const int tax_04 = A12 ;
const int heat  = A11 ;
const int cool = A10 ;
const int ex_1 = A9 ;
const int ex_2 = A8 ;

//δηλωση επαφων των μπουτον menu
const int buttonPin1 = A3;
const int buttonPin2 = A2;
const int buttonPin3 = A1;
const int buttonPin4 = A0;

//δηλωση επαφης εντωλης διακοπης ρευματος
const int power_pin = 16;
//δηλωση επαφης εντωλης διακοπης τροφοδοσιας
const int onlyBattery_pin = 17;
//δηλωση επαφης εντωλης φωτιας
const int fire_pin = 15;

// δηλωση μεταβλητης διακοπης ρευματος
int power_state ;
// δηλωση μεταβλητης διακοπης τροφοδοσιας
int onlyBattery ;
// δηλωση μεταβλητης φωτιας
int fire_state ;

//τα μπουτον να ειναι σε κατασταση 0 στην εκκινηση
int buttonState1 = 1;
int buttonState2 = 1;
int buttonState3 = 1;
int buttonState4 = 1;

//μεταβλητες τηλεφωνου
bool phone_flag_1  ;//για το μενου για αποθηκευση τηλ νουμερο
bool phone_flag_2  ;//
bool phone_flag_3  ;//
bool b_ATD_1 = true; //να κανει κληση τηλεφωνου και να περνω το millis για το χρονο κλησης
bool b_ATD_2 = true; //στη διακοπη
bool b_ATD_3 = true; //
bool b_gsm_flag_power = false;    // μετρητης για εκκηνηση και τερματισμο κλησης για διακοπη ρευματος
bool b_gsm_flag_power_ok = false; //  μετρητης αποστολη μηνηματος επιδιορθοσης διακοπης ρευματος
bool b_sms_t2_ok = false; //εαν θα στειλη sms στο 2 νουμερο για ok διακοπης ρευματος
bool b_sms_t3_ok = false; //εαν θα στειλη sms στο 3 νουμερο για ok διακοπης ρευματος
bool b_ATD_therm_1 = true; //να κανει κληση τηλεφωνου και να περνω το millis για το χρονο κλησης
bool b_ATD_therm_2 = true; //στη θερμοκρασια
bool b_ATD_therm_3 = true; //
bool b_gsm_flag_therm = false ;  // μετρητης για εκκηνηση και τερματισμο κλησης για θερμοκρασια
bool b_gsm_flag_therm_ok = false;  //  μετρητης αποστολη μηνηματος επιδιορθοσης χαμηλης κ υψηλης θερμοκρασιας
bool b_sms_t2_therm_ok = false; //εαν θα στειλη sms στο 2 νουμερο για ok θερμοκρασια
bool b_sms_t3_therm_ok = false; //εαν θα στειλη sms στο 3 νουμερο για ok θερμοκρασια
bool b_ATD_fire_1 = true; //να κανει κληση τηλεφωνου και να περνω το millis για το χρονο κλησης
bool b_ATD_fire_2 = true; //στη φωτια
bool b_ATD_fire_3 = true; //
bool b_gsm_flag_fire = false; // μετρητης για εκκηνηση και τερματισμο κλησης για φωτια
bool b_gsm_flag_fire_ok = false; //  μετρητης αποστολη μηνηματος επιδιορθοσης φωτιας
bool b_sms_t2_fire_ok = false; //εαν θα στειλη sms στο 2 νουμερο για ok φωτια
bool b_sms_t3_fire_ok = false; //εαν θα στειλη sms στο 3 νουμερο για ok φωτια
String TEL_1 = "";     // 1 τηλεφωνο
String TEL_2 = "";     // 2 τηλεφωνο
String TEL_3 = "";     // 3 τηλεφωνο
String TEL_adiaforo = "+000000000000"; //να μην κανει κληση
String mySerial_data = "";//String για DTMF
String symbol_data = "";//
String symbol = "";//
uint8_t bell ;             // ποσες φορες θα καλει τα τηλεφωνα
uint8_t bell_min = 2;      //ελαχιστος αριθμος κλησεων
uint8_t bell_max = 20;     //μεγιστος  αριθμος κλησεων
unsigned long startMillisTEL;   //χρονος εκκηνησης για το χρονο διαρκειας κλησης
const unsigned long periodTEL = 30000 ;  //ποσα δευτερολεπτα θα διαρκει η κληση
bool b_incall = false;//να περνω το millis για το χρονο κλησης καλουντος
uint8_t bell_therm_1 = bell;   // ποσες φορες θα καλει τα τηλεφωνα για θερμοκρασια
uint8_t bell_therm_2 = bell;//
uint8_t bell_therm_3 = bell;//
uint8_t bell_Power_1 = bell ;  // ποσες φορες θα καλει τα τηλεφωνα για διακοπη ρευματος
uint8_t bell_Power_2 = bell; //
uint8_t bell_Power_3 = bell; //
uint8_t bell_fire_1 = bell ;  // ποσες φορες θα καλει τα τηλεφωνα για φωτια
uint8_t bell_fire_2 = bell; //
uint8_t bell_fire_3 = bell; //
int delay_GSM = 600; //χρονοκαθηστερηση αναμεσα στης εντολες sim800l
uint8_t flag_telephone_power = 1; //αριθμηση για κληση 1ο 2ο 3ο τηλεφωνο
uint8_t flag_telephone_therm = 1;
uint8_t flag_telephone_fire = 1;
uint8_t flag_telephone_loop_power = 1; //αριθμηση για ξανα κλησης  τηλεφωνων
uint8_t flag_telephone_loop_therm = 1;
uint8_t flag_telephone_loop_fire = 1;
uint8_t max_flag_telephone_loop = 2;//μεγιστος χρονος επαναληψεων κλησεων π.χ.20

//μεταβλητες για αυτοματο κλεισημο του menu
unsigned long startMillis;   //χρονος εκκηνησης
const unsigned long period = 120000;  //χρονος καθηστερησης
const unsigned long periodtestrelay = 300000;

//για mode=3 για ελεγχο των ρελε
int  test_relay = 0;
//για χειρησμο relay ΕΧ1 ΕΧ2 απο πληκτρα
bool start_EX = true;//να περνη στην εναρξη την μνημη και να ενημερωνη την εφαρμογη
uint8_t ex1 = 0;
uint8_t booex1 = 0 ;
uint8_t ex2 = 0;
uint8_t booex2 = 0 ;
bool memEX1 = false;
bool memEX2 = false;
//για χειρησμο relay ΕΧ1 ΕΧ2 απο τηλεφωνο
String number_data = "";
String number = "";//το τηλ.νουμερο του καλουντος απο αναγνωριση κλησης χωρις το προθεμα της χωρας (π.χ.+30)
//String number_30 = "";//το τηλ.νουμερο του καλουντος απο αναγνωριση κλησης με το προθεμα της χωρας
String number_TEL = "";//τοποθετουμαι το αποθηκευμενο τηλ.νουμερο για αποστολη μηνηματος ενεργοποιησης η απενεργοποιησης EX1 EX2
String number_TEL_1 = "";//το αποθηκευμενο τηλ.νουμερο χωρις
String number_TEL_2 = "";//το προθεμα της χωρας (π.χ.+30)
String number_TEL_3 = "";//
unsigned long startMillisTELincall;//αυτοματο κλεισημο κλεισης καλουντος
const unsigned long periodTELincall = 40000;//χρονος καθηστερησης
unsigned long startMillisTELincall_RING;//μηδενισμος RING εαν ειναι μικροτερο του 3
const unsigned long periodTELincall_RING = 15000;//χρονος καθηστερησης

//χειρησμος Timer
bool startsTimer = true ;//για να περνη τον αρχικο χρονο millis
int timerONOFF = 0 ;
uint8_t timerRelay = 1;
long timerON ;//χρονος ανοιχτου ρελε
long timerOFF ;//χρονος κλειστου ρελε
unsigned long previousTimerMillis ;//βαζουμε το χρονο millis και με την διαφορα τους περνουμε το χρονο ON OFF
unsigned long longTimerTimeON ;
unsigned long longTimerTimeOFF ;
int timerTimeMax = 1200;//μεγιστος χρονος timer relay
int flashTimerRelay = 1;//κατασταση ρελε 0=OFF 1=ON timer relay
//για να μην ανοιγοκλοινουν τα ρελε οταν η θερμοκρασια τρεμοπαιζει
float tiktak_diafora_temp = 1.00;//σε περιπτωση συναγερμου
float tiktak_diafora = 0.27;//για αλλαγη ταχυτητων
uint8_t tiktak = 0 ;
uint8_t tiktak_Heat = 0 ;
uint8_t tiktak_Cool = 0;
uint8_t tiktak_alarm_LOW = 0;
uint8_t tiktak_alarm_HIGH = 0;

//αριθμος μνημων
unsigned int e_therm_T1 = 10;
unsigned int e_proti_D = 20;
unsigned int e_deuteri_D = 30;
unsigned int e_triti_D = 40;
unsigned int e_COOL = 50;
unsigned int e_HEAT = 60;
unsigned int e_alarm_low = 70;
unsigned int e_alarm_high = 80;
unsigned int e_mode = 90;
unsigned int e_TEL_1 = 100;
unsigned int e_TEL_2 = 120;
unsigned int e_TEL_3 = 140;
unsigned int e_bell = 160;
unsigned int e_timerONOFF = 170;
unsigned int e_timerRelay = 180;
unsigned int e_timerON = 190;
unsigned int e_timerOFF = 200;
unsigned int e_booex1 = 210;
unsigned int e_booex2 = 220;
//μεταβλητες για καθηστερηση συναγερμου διακοπης
unsigned long startMillisPOWER;   //χρονος εκκηνησης
const unsigned long periodPOWER = 60000;  //χρονος καθηστερησης
bool b_diakopi = false;

bool b_tiktak_setup = true;
bool b_TikTak_ALARM_setup = true;

//αναγνωση σηματος gsm στην εκκινηση
unsigned long start_currentSignalMillis;
unsigned long start_previousSignalMillis = 0;
const unsigned long start_GsmInterval = 30000;
//αναγνωση σηματος gsm καθε 5 λεπτα
unsigned long currentSignalMillis;
unsigned long previousSignalMillis = 0;
const unsigned long GsmInterval = 300000;

String Signal_gsm_contition = "";
String Signal_gsm = "";
String Ber_gsm = "";
String Gsm_sim_contact = "";
String Gsm_Ring = "";
int count_Ring = 0;
int int_Signal_gsm;
int int_Ber_gsm;
bool b_Signal_Sim800l;//εαν εχει καλο σημα
bool b_Ber_Sim800l;//και καλη ποιοτητα να βγαλει ενδειξη στην οθονη Y
bool b_gsm_sim;//εαν συνδεθηκε στο τηλεφωνικο δυκτιο για ενδειξη στην οθονη
bool b_start_contition_signal_Gsm = true;//αναγνωση σηματος gsm στην εκκινηση
String error_data = "";//εαν βγει ERROR στη σειριακη
String NoCarrier_data = ""; //εαν βγει NO CARRIER στη σειριακη

void setup() {

  RemoteXY_Init (); //αρχικοποιηση εκκινηση RemoteXY
  //------------------------------
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  Serial1.begin(9600);

  // χρονοκαθυστέρηση για να βρει δικτυο το sim800l
  delay(1000);

  lcd.init();  /* αρχικοποιηση εκκινηση οθονης */
  lcd.backlight();  /* ενεργοποιηση οπισθιου φωτισμου */

  //οροσμος pin εισοδων μπουτον
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  // ορισμος επαφης εισοδου διακοπης ρευμαυτος
  pinMode(power_pin, INPUT_PULLUP);

  //ορισμος επαφης εισοδου λειτουργιας μονο με μπαταρια
  pinMode(onlyBattery, INPUT);

  //ορισμος επαφης εισοδου φωτιας
  pinMode(fire_pin, INPUT_PULLUP);

  /*ορισμος pin  εξοδων για ρελε */
  pinMode(tax_01, OUTPUT);
  pinMode(tax_02, OUTPUT);
  pinMode(tax_03, OUTPUT);
  pinMode(tax_04, OUTPUT);
  pinMode(cool, OUTPUT) ;
  pinMode(heat, OUTPUT) ;
  pinMode(ex_1, OUTPUT);
  pinMode(ex_2, OUTPUT);

  /* οριζουμε οι εξοδοι να ειναι σε κατασταση HIGH για να ειναι
    απενεργοποιοιμενα τα ρελε κατα την εκκινηση του κωδικα και
    σε καθε επανεκκινηση του arduino,ετσι δουλευουν τα πλακετακια
    των ρελε*/
  digitalWrite(tax_01, HIGH);
  digitalWrite(tax_02, HIGH);
  digitalWrite(tax_03, HIGH);
  digitalWrite(tax_04, HIGH);
  digitalWrite(cool, HIGH);
  digitalWrite(heat, HIGH);
  digitalWrite(ex_1, HIGH);
  digitalWrite(ex_2, HIGH);

  /*να παρει απο την διευθηνση μνημης 10 την τιμη
    therm_T1 κατα την εκκηνιση*/
  EEPROM.get(e_therm_T1, therm_T1);
  //  Serial.println( therm_T1 );
  /*εαν η τιμη στη διευθηνση μνημης 10 ειναι μεγαλητερη του 0
    σημενη οτι εχουν μπη τιμες στις διευθηνσης απο προηγουμενη
    χρηση και να παρη της τιμες απο τις τιμες για proti_D
    ,deuteri_D,triti_D,alarm_high,alarm_low αλλιως να βαλει
    της κατωθη τιμες */

  if (therm_T1 > -30.00) {
    EEPROM.get(e_therm_T1, therm_T1);
    EEPROM.get(e_proti_D, proti_D);
    EEPROM.get(e_deuteri_D, deuteri_D);
    EEPROM.get(e_triti_D, triti_D);
    EEPROM.get(e_COOL, COOL);
    EEPROM.get(e_HEAT, HEAT);
    EEPROM.get(e_alarm_low, alarm_low);
    EEPROM.get(e_alarm_high, alarm_high);
    EEPROM.get(e_mode, mode);

    for (byte b_1 = 0 ; b_1 < 13 ; b_1++) { //13 is the maximum lenght of an IP adress with dots
      char f_1 = EEPROM.read(e_TEL_1 + b_1);
      TEL_1 += (f_1);
    }
    for (byte b_2 = 0 ; b_2 < 13 ; b_2++) { //13 is the maximum lenght of an IP adress with dots
      char f_2 = EEPROM.read(e_TEL_2 + b_2);
      TEL_2 += (f_2);
    }
    for (byte b_3 = 0 ; b_3 < 13 ; b_3++) { //13 is the maximum lenght of an IP adress with dots
      char f_3 = EEPROM.read(e_TEL_3 + b_3);
      TEL_3 += (f_3);
    }
    EEPROM.get(e_bell, bell);
    EEPROM.get(e_timerONOFF, timerONOFF);
    EEPROM.get(e_timerRelay, timerRelay);
    EEPROM.get(e_timerON, timerON);
    EEPROM.get(e_timerOFF, timerOFF);
    EEPROM.get(e_booex1, booex1);
    EEPROM.get(e_booex2, booex2);

  }
  else {
    therm_T1  = 20.00 ;
    proti_D  = 2.00 ;
    deuteri_D  = 2.00 ;
    triti_D  = 2.00 ;
    COOL = 28.00 ;
    HEAT = 18.00 ;
    alarm_high = 30.00 ;
    alarm_low = 16.00 ;
    mode = 1 ;
    bell = 5 ;
    TEL_1 = TEL_adiaforo ;
    TEL_2 = TEL_adiaforo ;
    TEL_3 = TEL_adiaforo ;
    timerONOFF = 0;
    timerRelay = 1;
    timerON = 300;
    timerOFF = 300;
    e_booex1 = 0;
    e_booex2 = 0;
    EEPROM.put(e_therm_T1, therm_T1);
    EEPROM.put(e_proti_D, proti_D);
    EEPROM.put(e_deuteri_D, deuteri_D);
    EEPROM.put(e_triti_D, triti_D);
    EEPROM.put(e_COOL, COOL);
    EEPROM.put(e_HEAT, HEAT);
    EEPROM.put(e_alarm_low, alarm_low);
    EEPROM.put(e_alarm_high, alarm_high);
    EEPROM.put(e_mode, mode);
    EEPROM.put(e_bell, bell);
    EEPROM.put(e_timerONOFF, timerONOFF);
    EEPROM.put(e_timerRelay, timerRelay);
    EEPROM.put(e_timerON, timerON);
    EEPROM.put(e_timerOFF, timerOFF);
    EEPROM.put(e_booex1, booex1);
    EEPROM.put(e_booex2, booex2);
    for (int i_1 = 0 ; i_1 < TEL_1.length() ; i_1++)
    {
      EEPROM.write( e_TEL_1 + i_1, TEL_1[i_1] );
    }
    for (int i_2 = 0 ; i_2 < TEL_2.length() ; i_2++)
    {
      EEPROM.write( e_TEL_2 + i_2, TEL_2[i_2] );
    }
    for (int i_3 = 0 ; i_3 < TEL_3.length() ; i_3++)
    {
      EEPROM.write( e_TEL_3 + i_3, TEL_3[i_3] );
    }
  }

  RemoteXY.edit_1 = EEPROM.get(e_therm_T1, therm_T1);
  RemoteXY.edit_2 = EEPROM.get(e_proti_D, proti_D);
  RemoteXY.edit_3 = EEPROM.get(e_deuteri_D, deuteri_D);
  RemoteXY.edit_4 = EEPROM.get(e_triti_D, triti_D);
  RemoteXY.edit_5 = EEPROM.get(e_COOL, COOL);
  RemoteXY.edit_6 = EEPROM.get(e_HEAT, HEAT);
  RemoteXY.edit_8 = EEPROM.get(e_alarm_low, alarm_low);
  RemoteXY.edit_7 = EEPROM.get(e_alarm_high, alarm_high);
  RemoteXY.bell_edit = EEPROM.get(e_bell, bell);
  RemoteXY.edit_9 = EEPROM.get(e_timerRelay, timerRelay);
  RemoteXY.edit_10 = EEPROM.get(e_timerON, timerON);
  RemoteXY.edit_11 = EEPROM.get(e_timerOFF, timerOFF);

  //δικοι μου χαρακτηρες
  lcd.createChar(0, priza);
  // lcd.createChar(1, pano);
  // lcd.createChar(2, kato);
  // lcd.createChar(3, velos_aristera);
  // lcd.createChar(4, velos_dexia);
  lcd.createChar(5, keraunos);
  lcd.createChar(6, kampana);
  // lcd.createChar(7, diktis);
  //lcd.home();
  //  startTimerMillis = millis();//για να περνη τον αρχικο χρονο millis
  //εκκινηση λογοτηπου οθονης
  maxatos();
  delay(5000);

  //delay(delay_GSM);
  //Serial1.println("AT"); //Once the handshake test is successful, it will back to OK
  delay(delay_GSM);
  Serial1.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(delay_GSM);
  Serial1.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  delay(delay_GSM);
  Serial1.println("AT+CMGD=1,4");//DELETE all sms
  delay(delay_GSM);
  Serial1.println("AT+DDET=1");//DTMF
  delay(delay_GSM);
  Serial1.println("ATS0=3");//απαντά αυτόματα στην κλήση μετά από 3 κουδούνισμα
  delay(delay_GSM);
  Serial1.println("AT+CLIP=1");//αναγνωριση κλησεων

  sensors.begin(); /* Εκκίνηση της βιβλιοθήκης για DS18B20 */
  //εκκινηση αρχικης οθονης
  lcd.clear();

  updateScreen() ;
  //Serial.println(booex1);
  // Serial.println(booex2);

}

void loop() {


  RemoteXY_Handler ();

  //τημες ταχυτητων
  therm_T2 = (therm_T1 + proti_D);
  therm_T3 = (therm_T2 + deuteri_D);
  therm_T4 = (therm_T3 + triti_D);

  //χρονος TIMER
  longTimerTimeON = (1000 * timerON);
  longTimerTimeOFF = (1000 * timerOFF);

  //να διαβαση την εισοδο του οτι δουλευει μονο η μπαταρια
  onlyBattery = digitalRead(onlyBattery_pin);

  //να διαβαση την εισοδο του διακοπης στο power_state
  power_state = digitalRead(power_pin);

  //να διαβαση την εισοδο της φωτιας
  fire_state = digitalRead(fire_pin);

  //void για ενεργοποιηση συναγερμου χωρις απανωτα ανοιγοκλοιματα
  //TikTak_ALARM_setup το χρησιμοποιο μονο στην εκκινηση
  //γιατι εαν η θερμοκρασια συμπεση με την θερμοκρασια
  //του κενου που διμιουργιτε με το tiktak_diafora
  //δεν θα ξεκινηση κανενα μοτερ,μονο οταν η θερμοκρασια
  //μεταβληθη απο αυη την διαφορα
  if (b_TikTak_ALARM_setup) {
    TikTak_ALARM_setup();
    b_TikTak_ALARM_setup = false;
  }
  else {
    TikTak_ALARM();
  }

  //ενεργποιηση κεντρικης οθονης
  if ( update_Screen == true) {
    updateScreen() ;
  }

  // ENERGOLOIHSH MOTER
  if (Moto_Run == true) {
    //void για ενεργοποιηση ρελε χωρις απανωτα ανοιγοκλοιματα
    //TikTak_setup το χρησιμοποιο μονο στην εκκινηση
    //γιατι εαν η θερμοκρασια συμπεση με την θερμοκρασια
    //του κενου που διμιουργιτε με το tiktak_diafora
    //δεν θα ξεκινηση κανενα μοτερ,μονο οταν η θερμοκρασια
    //μεταβληθη απο αυη την διαφορα
    if (b_tiktak_setup) {
      TikTak_setup();
      b_tiktak_setup = false;
    }
    else {
      TikTak();
    }
    motoboot();
  }
  //void για τα ρελε EX μονο για την εκκινηση
  start_loop_EX();

  //να διαβαση τις εισοδους των μπουτον στα buttonState
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  // delay(DelayMenu); //μικρη χρονοκαθηστερηση
  ex_Void_button();//διαχειριση εξωτερικα ρελε μεσω πληκτρων
  EX_screen_relay();//ενδειξη και ρελε εξωτερικα ρελε
  ex_Void_app();//διαχειριση εξωτερικα ρελε μεσω εφαρμογης
  //για την εφαρμογη RemoteXY
  // RemoteXY.level_1 = therm_1;
  dtostrf(therm_1, 4, 2, RemoteXY.text_1);
  dtostrf(therm_T1, 4, 2, RemoteXY.text_2);
  dtostrf(therm_T2, 4, 2, RemoteXY.text_3);
  dtostrf(therm_T3, 4, 2, RemoteXY.text_4);
  dtostrf(therm_T4, 4, 2, RemoteXY.text_5);
  dtostrf(COOL, 4, 2, RemoteXY.text_6);
  dtostrf(HEAT, 4, 2, RemoteXY.text_7);
  dtostrf(alarm_high, 4, 2, RemoteXY.text_8);
  dtostrf(alarm_low, 4, 2, RemoteXY.text_9);
  itoa(bell, RemoteXY.bell_text, 10);
  itoa(timerRelay, RemoteXY.text_10, 10);
  itoa(timerON, RemoteXY.text_11, 10);
  itoa(timerOFF, RemoteXY.text_14, 10);

  strcpy  (RemoteXY.tel_1_text, TEL_1.c_str()); //μετατροπη string σε char
  strcpy  (RemoteXY.tel_2_text, TEL_2.c_str()); //μετατροπη string σε char
  strcpy  (RemoteXY.tel_3_text, TEL_3.c_str()); //μετατροπη string σε char

  if (timerONOFF == 0) {
    strcpy  (RemoteXY.text_12, "OFF");
    strcpy  (RemoteXY.text_13, "OFF");
  }
  else {
    strcpy  (RemoteXY.text_12, "ON");
    if (timerRelay == 1) {
      strcpy  (RemoteXY.text_13, "T1");
    }
    else if (timerRelay == 2) {
      strcpy  (RemoteXY.text_13, "T2");
    }
    else if (timerRelay == 3) {
      strcpy  (RemoteXY.text_13, "T3");
    }
    else if (timerRelay == 4) {
      strcpy  (RemoteXY.text_13, "T4");
    }
  }
  //τα αποθηκευμενα νουμερα χωρις +30
  number_TEL_1 = TEL_1.substring(3, 13);
  number_TEL_2 = TEL_2.substring(3, 13);
  number_TEL_3 = TEL_3.substring(3, 13);

  //void για την εφαρμογη RemoteXY
  app_control();

  //αρχικη εντολη για κατασταση δυκτιου και σηματος για τηλεφωνητη
  //για να δηνω εντολες για κατασταση δυκτιου και σηματος για τηλεφωνητη
  //ανα χρονικα διαστηματα
  start_currentSignalMillis = millis();
  if ((b_start_contition_signal_Gsm) && (start_currentSignalMillis - start_previousSignalMillis >= start_GsmInterval)) {
    delay(delay_GSM);
    Serial1.println("AT+CSQ");
    delay(delay_GSM);
    Serial1.println("AT+CREG?");
    b_start_contition_signal_Gsm = false;
  }
  currentSignalMillis = millis();
  if (currentSignalMillis - previousSignalMillis >= GsmInterval) {
    previousSignalMillis += GsmInterval;
    if ((fire_state == 1) && (power_state == 1 && onlyBattery == 1)
        && (tiktak_alarm_LOW == 0 && tiktak_alarm_HIGH == 0) && (count_Ring == 0)) {
      delay(delay_GSM);
      Serial1.println("AT+CSQ");
      delay(delay_GSM);
      Serial1.println("AT+CREG?");
    }
  }
  //να μηδενηση το count_Ring κ number_TEL εαν κλειση το τηλ πριντις τρεις
  //κλησης καιαπαντηση ,για να ειναι ετοιμο για την επομενη κλεισει
  if (count_Ring > 0 && count_Ring < 3 && !b_incall) {
    if ( millis() - startMillisTELincall_RING > periodTELincall_RING) {
      number_TEL = "";
      count_Ring = 0;
    }
  }
  //να κλειση το τηλ μετα απο 40" στην αποστολη DTMF
  if (( millis() - startMillisTELincall > periodTELincall) && b_incall) {
    if (count_Ring > 0) {
      delay(delay_GSM);
      Serial1.println("ATH"); //hang up
      count_Ring = 0;
    }
    number_TEL = "";
    b_incall = false;
  }

  if (Serial1.available()) {
    mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
    Serial.println(mySerial_data);

    number_data = mySerial_data.substring(mySerial_data.indexOf("+CLIP:"));
    symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
    Signal_gsm_contition = mySerial_data.substring(mySerial_data.indexOf("+CSQ:"));
    Gsm_sim_contact = mySerial_data.substring(mySerial_data.indexOf("+CREG:"));
    error_data = mySerial_data.substring(mySerial_data.indexOf("ERROR"));
    NoCarrier_data = mySerial_data.substring(mySerial_data.indexOf("NO CARRIER"));

    //να μετρα τους χτυπους και να περνη το χρονο μηδενισμου χτηπων RING
    //εαν κλησουμε το τηλ πριν το σηκωση και το χρονο μηδενισμου του RING
    //και κλεισημο κλησης μετα απο 60"
    if (mySerial_data.indexOf("RING") > -1) {
      count_Ring++;
      if (count_Ring == 1) {
        startMillisTELincall_RING = millis();
        // Serial.println(startMillisTELincall_RING);
      }
      if (count_Ring >= 3) {
        b_incall = true;
        startMillisTELincall = millis();
        // Serial.println(startMillisTELincall);
      }
      mySerial_data = "";
    }
  }

  //αναγνωση αριθμου καλουντως
  if (number_data.startsWith("+CLIP:")) {
    int first_is = number_data.indexOf('"');
    int last_is = number_data.indexOf('"', first_is + 1);
    number = number_data.substring(first_is + 1, last_is);
    if (number == number_TEL_1 ) {
      number_TEL = TEL_1;
    }
    else if (number == number_TEL_2 ) {
      number_TEL = TEL_2;
    }
    else if (number == number_TEL_3 ) {
      number_TEL = TEL_3;
    }
    else if (number == TEL_1 ) {
      number_TEL = TEL_1;
    }
    else if (number == TEL_2 ) {
      number_TEL = TEL_2;
    }
    else if (number == TEL_3 ) {
      number_TEL = TEL_3;
    }
    else {
      if (count_Ring > 0) {
        delay(delay_GSM);
        Serial1.println("ATH"); //hang up
        b_incall = false;
        number_TEL = "";
        count_Ring = 0;
      }
    }
  }
  //εαν κλησουμε εμεις το τηλ μετα απο την κληση μας να κανει τα ακολουθα
  if (NoCarrier_data == "NO CARRIER" && count_Ring > 0) {
    if (b_incall) {
      b_incall = false;
    }
    number_TEL = "";
    count_Ring = 0;
    NoCarrier_data = "";
  }
  //εαν την στιγμη που καλουμε την συσκευη μας καλεση και αυτη για βλαβη
  // να κληση την γραμη και να συνεχηση της κλησης βλαβης
  if (error_data == "ERROR" && count_Ring > 0) {
    delay(delay_GSM);
    Serial1.println("ATH"); //hang up
    if (b_incall) {
      b_incall = false;
    }
    number_TEL = "";
    count_Ring = 0;
    error_data = "";
  }
  //αναγνωση αριθμου DTMF
  if (symbol_data.startsWith("+DTMF:")) {
    symbol = symbol_data.substring(7, 8);
    Serial.println(symbol);
    incall_TEL_DTMF();
  }
  //αναγνωση αριθμου ισχης και ποιοτητας σηματος
  if (Signal_gsm_contition.startsWith("+CSQ:")) {
    Signal_gsm = Signal_gsm_contition.substring(Signal_gsm_contition.indexOf(":"), Signal_gsm_contition.indexOf(','));
    Signal_gsm = Signal_gsm.substring(1);
    Signal_gsm.trim();
    Ber_gsm = Signal_gsm_contition.substring(Signal_gsm_contition.indexOf(','));
    Ber_gsm = Ber_gsm.substring(1);
    // Ber_gsm.trim();
    int_Signal_gsm = Signal_gsm.toInt();
    int_Ber_gsm = Ber_gsm.toInt();

    if (int_Signal_gsm >= 10) {
      b_Signal_Sim800l = true;
    }
    else if (int_Signal_gsm < 10) {
      b_Signal_Sim800l = false;
    }
    if (int_Ber_gsm >= 0 && int_Ber_gsm <= 7) {
      b_Ber_Sim800l = true;
    }
    else {
      b_Ber_Sim800l = false;
    }
    /* Serial.println(Signal_gsm);
      Serial.println(int_Signal_gsm);
      Serial.println(Ber_gsm);
      Serial.println(int_Ber_gsm );
      Serial.println(b_Signal_Sim800l);
      Serial.println(b_Ber_Sim800l);*/
    Signal_gsm_contition = "";
    Signal_gsm = "";
    Ber_gsm = "";
  }
  //αναγνωση συνδεσης στο δικτιο
  if (Gsm_sim_contact.startsWith("+CREG:")) {
    if (Gsm_sim_contact.indexOf("+CREG: 0,1") > -1) {
      b_gsm_sim = true;
    }
    else {
      b_gsm_sim = false;
    }
    // Serial.println(b_gsm_sim);
  }

  //εντολες για menu

  if (buttonState4 == LOW) {
    update_Screen = false ;
    Moto_Run = false ;
    lcd.clear();
    menu = 17 ;
    central_menu = true;
    startMillis = millis();  //save the start time
  }

  while ( central_menu ) {
    //αναγνωση πληκτρων
    buttonVooidMenu();

    //δικοι μου χαρακτηρες
    lcd.createChar(3, velos_aristera);
    lcd.createChar(4, velos_dexia);

    //EXIT menu με χρονομετρο
    if (  millis() - startMillis > period) { //true until the period elapses.  Note that this is the reverse of BWOD
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print(">>>EXIT<<<");
      delay(2000);
      lcd.clear();
      EEPROM.get(e_therm_T1, therm_T1);
      EEPROM.get(e_proti_D, proti_D);
      EEPROM.get(e_deuteri_D, deuteri_D);
      EEPROM.get(e_triti_D, triti_D);
      EEPROM.get(e_COOL, COOL);
      EEPROM.get(e_HEAT, HEAT);
      EEPROM.get(e_alarm_low, alarm_low);
      EEPROM.get(e_alarm_high, alarm_high);
      EEPROM.get(e_mode, mode);
      central_menu = false;
      update_Screen = true ;
      Moto_Run = true ;
      break;
    }
    if (buttonState1 == LOW) {
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print(">>>EXIT<<<");
      delay(2000);
      lcd.clear();
      EEPROM.get(e_therm_T1, therm_T1);
      EEPROM.get(e_proti_D, proti_D);
      EEPROM.get(e_deuteri_D, deuteri_D);
      EEPROM.get(e_triti_D, triti_D);
      EEPROM.get(e_COOL, COOL);
      EEPROM.get(e_HEAT, HEAT);
      EEPROM.get(e_alarm_low, alarm_low);
      EEPROM.get(e_alarm_high, alarm_high);
      EEPROM.get(e_mode, mode);
      central_menu = false;
      update_Screen = true ;
      Moto_Run = true ;
      break;
    }
    if (buttonState2 == LOW) {
      menu-- ;
      if ( menu < 1 ) {
        menu = 17 ;
      }
    }
    if (buttonState3 == LOW) {
      menu++ ;
      if ( menu > 17 ) {
        menu = 1 ;
      }
    }
    CASE_menu();
    if (buttonState4 == LOW) {
      if (menu > 0 && menu < 17) {
        central_menu = false;
        Setup_therm();
        break;
      }
    }

  }

  ////////////////////////////////////////
  //σε αυτες τις περιπτωσης να σταματηση ολα τα ρελε εκτος EX1 EX2
  if (fire_state == 0 || therm_1 == 85.00 || therm_1 == -127.00) {
    Moto_Run = false ;
    voidfire();
  }
  else {
    if (!central_menu) {
      Moto_Run = true ;
    }
  }
  ////////////////////////////////////////////
  // τηλεφωνο και μηνημα σε χαμηλη  και υψυλη θερμοκρασια
  if (tiktak_alarm_LOW == 0 && tiktak_alarm_HIGH == 0) {
    //εαν εχει κανει κληση τηλεφ. και επανερθει η θερμοκρασια
    //να κλειση το τηλεφ.
    while (!b_ATD_therm_1 || !b_ATD_therm_2 || !b_ATD_therm_3) {
      delay(delay_GSM);
      Serial1.println("ATH"); //hang up
      b_ATD_therm_1 = true;
      b_ATD_therm_2 = true;
      b_ATD_therm_3 = true;
      break;
    }
    flag_telephone_therm = 1;
    flag_telephone_loop_therm = 1;
    b_gsm_flag_therm = false;
    bell_therm_1 = bell;
    bell_therm_2 = bell;
    bell_therm_3 = bell;
  }

  while ((tiktak_alarm_LOW == 1 || tiktak_alarm_HIGH == 1) && b_gsm_flag_therm == false && TEL_1 != TEL_adiaforo) {
    //εκκηνηση θερμοστατη
    sensors.requestTemperatures ();
    therm_1 = (sensors.getTempCByIndex(0));
    TikTak_ALARM();

    if (flag_telephone_loop_therm >= 1 && flag_telephone_loop_therm <= max_flag_telephone_loop) {
      if (flag_telephone_therm == 1) {
        if (  bell_therm_1 > 0) {

          if (b_ATD_therm_1) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_1 + ";");
            b_ATD_therm_1 = false;
            break;
          }
          else if (!b_ATD_therm_1) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                if (flag_telephone_loop_therm == 1) {
                  gsm_sms_1();//αποστολη μηνηματος
                }
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_gsm_flag_therm_ok = true;
                b_ATD_therm_1 = true;
                b_gsm_flag_therm = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_therm_1) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_therm_1--;
            b_ATD_therm_1 = true;
            break;
          }
        }
        else if (bell_therm_1 == 0) {
          if (flag_telephone_loop_therm == 1) {
            gsm_sms_1();
            b_gsm_flag_therm_ok = true;
          }
          delay(delay_GSM);
          if (TEL_2 != TEL_adiaforo) {
            ++flag_telephone_therm;
            bell_therm_1 = bell;
            break;
          }
          else if (TEL_2 == TEL_adiaforo) {
            ++flag_telephone_loop_therm;
            bell_therm_1 = bell;
            break;
          }
          break;
        }
      }
      else if (flag_telephone_therm == 2) {
        if (bell_therm_2 > 0) {
          if (b_ATD_therm_2) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_2 + ";");
            b_ATD_therm_2 = false;
            break;
          }
          else if (!b_ATD_therm_2) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                gsm_sms_2();//αποστολη μηνηματος
                b_sms_t2_therm_ok = true;
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_ATD_therm_2 = true;
                b_gsm_flag_therm = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_therm_2) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_therm_2--;
            b_ATD_therm_2 = true;
            break;
          }
        }
        else if (bell_therm_2 == 0) {
          if (TEL_3 != TEL_adiaforo) {
            ++flag_telephone_therm;
            bell_therm_2 = bell;
            break;
          }
          else if (TEL_3 == TEL_adiaforo) {
            ++flag_telephone_loop_therm;
            flag_telephone_therm = 1;
            bell_therm_2 = bell;
            break;
          }
          break;
        }
      }
      else if (flag_telephone_therm == 3) {
        if (bell_therm_3 > 0) {
          if (b_ATD_therm_3) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_3 + ";");
            b_ATD_therm_3 = false;
            break;
          }
          else if (!b_ATD_therm_3) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                gsm_sms_3();//αποστολη μηνηματος
                b_sms_t3_therm_ok = true;
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_ATD_therm_3 = true;
                b_gsm_flag_therm = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_therm_3) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_therm_3--;
            b_ATD_therm_3 = true;
            break;
          }
        }
        else if (bell_therm_3 == 0) {
          ++flag_telephone_loop_therm;
          flag_telephone_therm = 1;
          bell_therm_3 = bell;
          break;
        }
      }
    }
    else if (flag_telephone_loop_therm > max_flag_telephone_loop) {
      b_gsm_flag_therm = true;
      break;
    }
  }

  while ((tiktak_alarm_LOW == 0 && tiktak_alarm_HIGH == 0) && b_gsm_flag_therm_ok == true) {
    gsm_sms_ok_1_temp();
    delay(5000);
    if (b_sms_t2_therm_ok) {
      gsm_sms_ok_2_temp();
      b_sms_t2_therm_ok = false;
    }
    else if (b_sms_t3_therm_ok) {
      gsm_sms_ok_3_temp();
      b_sms_t3_therm_ok = false;
    }
    b_gsm_flag_therm_ok = 0 ;
    break;
  }
  /////////////////////////////////////

  // τηλεφωνο και μηνημα σε διακοπη ρευματος εσωτερικη εξωτερικη

  //οταν δεν εχουμε διακοπη
  if (power_state == 1 && onlyBattery == 1) {
    //εαν εχει κανει κληση τηλεφ. και επανερθει το ρευμα
    //να κλειση το τηλεφ.
    while (!b_ATD_1 || !b_ATD_2 || !b_ATD_3) {
      delay(delay_GSM);
      Serial1.println("ATH"); //hang up
      b_ATD_1 = true;
      b_ATD_2 = true;
      b_ATD_3 = true;
      break;
    }
    flag_telephone_power = 1; //αριθμηση για κληση 1ο 2ο 3ο τηλεφωνο
    flag_telephone_loop_power = 1; //αριθμηση για ξανα κλησης  τηλεφωνων
    b_gsm_flag_power = false ;
    b_diakopi = false;
  }
  //οταν εχουμε διακοπη
  while ((power_state == 0 || onlyBattery == 0) && !b_diakopi) {
    startMillisPOWER = millis();
    bell_Power_1 = bell;
    bell_Power_2 = bell;
    bell_Power_3 = bell;
    b_diakopi = true;
    break;
  }

  while ((  millis() - startMillisPOWER > periodPOWER) && (power_state == 0 || onlyBattery == 0)
         && !b_gsm_flag_power && TEL_1 != TEL_adiaforo) {

    //να διαβαση την εισοδο του οτι δουλευει μονο η μπαταρια
    onlyBattery = digitalRead(onlyBattery_pin);

    //να διαβαση την εισοδο του διακοπης στο power_state
    power_state = digitalRead(power_pin);

    if (flag_telephone_loop_power >= 1 && flag_telephone_loop_power <= max_flag_telephone_loop) {
      if (flag_telephone_power == 1) {
        if (  bell_Power_1 > 0) {

          if (b_ATD_1) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_1 + ";");
            b_ATD_1 = false;
            break;
          }
          else if (!b_ATD_1) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                if (flag_telephone_loop_power == 1) {
                  gsm_sms_power_1();//αποστολη μηνηματος
                }
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_gsm_flag_power_ok = true;
                b_ATD_1 = true;
                b_gsm_flag_power = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_1) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_Power_1--;
            b_ATD_1 = true;
            break;
          }
        }
        else if (bell_Power_1 == 0) {
          if (flag_telephone_loop_power == 1) {
            gsm_sms_power_1();
            b_gsm_flag_power_ok = true;
          }
          delay(delay_GSM);
          if (TEL_2 != TEL_adiaforo) {
            ++flag_telephone_power;
            bell_Power_1 = bell;
            break;
          }
          else if (TEL_2 == TEL_adiaforo) {
            ++flag_telephone_loop_power;
            bell_Power_1 = bell;
            break;
          }
          break;
        }
      }
      else if (flag_telephone_power == 2) {
        if (bell_Power_2 > 0 ) {
          if (b_ATD_2) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_2 + ";");
            b_ATD_2 = false;
            break;
          }
          else if (!b_ATD_2) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                gsm_sms_power_2();//αποστολη μηνηματος
                b_sms_t2_ok = true;
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_ATD_2 = true;
                b_gsm_flag_power = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_2) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_Power_2--;
            b_ATD_2 = true;
            break;
          }
        }
        else if (bell_Power_2 == 0) {
          if (TEL_3 != TEL_adiaforo) {
            ++flag_telephone_power;
            bell_Power_2 = bell;
            break;
          }
          else if (TEL_3 == TEL_adiaforo) {
            ++flag_telephone_loop_power;
            flag_telephone_power = 1;
            bell_Power_2 = bell;
            break;
          }
          break;
        }
      }
      else if ( flag_telephone_power == 3) {
        if (bell_Power_3 > 0) {
          if (b_ATD_3) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_3 + ";");
            b_ATD_3 = false;
            break;
          }
          else if (!b_ATD_3) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                gsm_sms_power_3();//αποστολη μηνηματος
                b_sms_t3_ok = true;
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_ATD_3 = true;
                b_gsm_flag_power = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_3) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_Power_3--;
            b_ATD_3 = true;
            break;
          }
        }
        else if (bell_Power_3 == 0) {
          ++flag_telephone_loop_power;
          flag_telephone_power = 1;
          bell_Power_3 = bell;
          break;
        }
      }
    }
    else if (flag_telephone_loop_power > max_flag_telephone_loop) {
      b_gsm_flag_power = true;
      break;
    }
  }


  while (power_state == 1 && onlyBattery == 1  && b_gsm_flag_power_ok == true) {
    gsm_sms_ok_1_power();
    delay(5000);
    if (b_sms_t2_ok) {
      gsm_sms_ok_2_power();
      b_sms_t2_ok = false;
    }
    else if (b_sms_t3_ok) {
      gsm_sms_ok_3_power();
      b_sms_t3_ok = false;
    }
    b_gsm_flag_power_ok = false ;
    break;
  }


  ////////////////////////////////////

  // τηλεφωνο , μηνημα και διακοπη
  // λειτουργιας ανεμηστηρων σε φωτια

  if (fire_state == 1) {
    //εαν εχει κανει κληση τηλεφ. και επανερθει η βλαβη φωτιας
    //να κλειση το τηλεφ.
    while (!b_ATD_fire_1 || !b_ATD_fire_2 || !b_ATD_fire_3) {
      delay(delay_GSM);
      Serial1.println("ATH"); //hang up
      b_ATD_fire_1 = true;
      b_ATD_fire_2 = true;
      b_ATD_fire_3 = true;
      break;
    }
    b_gsm_flag_fire = false ;
    flag_telephone_loop_fire = 1;
    flag_telephone_fire = 1;
    bell_fire_1 = bell ;
    bell_fire_2 = bell;
    bell_fire_3 = bell;
  }

  while (fire_state == 0 && b_gsm_flag_fire == false && TEL_1 != TEL_adiaforo) {

    //να διαβαση την εισοδο της φωτιας
    fire_state = digitalRead(fire_pin);

    if (flag_telephone_loop_fire >= 1 && flag_telephone_loop_fire <= max_flag_telephone_loop) {
      if (flag_telephone_fire == 1) {
        if (bell_fire_1 > 0) {

          if (b_ATD_fire_1) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_1 + ";");
            b_ATD_fire_1 = false;
            break;
          }
          else if (!b_ATD_fire_1) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                if (flag_telephone_loop_fire == 1) {
                  gsm_sms_fire_1();
                }
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_gsm_flag_fire_ok = true;
                b_ATD_fire_1 = true;
                b_gsm_flag_fire = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_fire_1) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_fire_1--;
            b_ATD_fire_1 = true;
            break;
          }
        }
        else if (bell_fire_1 == 0) {
          if (flag_telephone_loop_fire == 1) {
            gsm_sms_fire_1();
            b_gsm_flag_fire_ok = true;
          }
          delay(delay_GSM);
          if (TEL_2 != TEL_adiaforo) {
            ++flag_telephone_fire ;
            bell_fire_1 = bell;
            break;
          }
          else if (TEL_2 == TEL_adiaforo) {
            ++flag_telephone_loop_fire;
            bell_fire_1 = bell;
            break;
          }
          break;
        }
      }
      else if (flag_telephone_fire == 2) {
        if (bell_fire_2 > 0) {
          if (b_ATD_fire_2) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_2 + ";");
            b_ATD_fire_2 = false;
            break;
          }
          else if (!b_ATD_fire_2) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                gsm_sms_fire_2();//αποστολη μηνηματος
                b_sms_t2_fire_ok = true;
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_ATD_fire_2 = true;
                b_gsm_flag_fire = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_fire_2) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_fire_2--;
            b_ATD_fire_2 = true;
            break;
          }
        }
        else if (bell_fire_2 == 0) {
          if (TEL_3 != TEL_adiaforo) {
            ++flag_telephone_fire ;
            bell_fire_2 = bell;
            break;
          }
          else if (TEL_3 == TEL_adiaforo) {
            ++flag_telephone_loop_fire;
            flag_telephone_fire = 1;
            bell_fire_2 = bell;
            break;
          }
          break;
        }
      }
      else if (flag_telephone_fire == 3) {
        if (bell_fire_3 > 0) {
          if (b_ATD_fire_3) {
            startMillisTEL = millis();
            delay(delay_GSM);
            Serial1.println("ATD+ " + TEL_3 + ";");
            b_ATD_fire_3 = false;
            break;
          }
          else if (!b_ATD_fire_3) {
            if (Serial1.available()) {
              mySerial_data = Serial1.readString(); // to hold incomming communication from GSM module
              Serial.println(mySerial_data);
              symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
              symbol = symbol_data.substring(7, 8);
              Serial.println(symbol);

              if (symbol == "*" ) {
                delay(delay_GSM);
                Serial1.println("ATH"); //hang up
                gsm_sms_fire_3();//αποστολη μηνηματος
                b_sms_t3_fire_ok = true;
                mySerial_data = "";
                symbol_data = "";
                symbol = "";
                b_ATD_fire_3 = true;
                b_gsm_flag_fire = true;
                break;
              }
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !b_ATD_fire_3) {
            delay(delay_GSM);
            Serial1.println("ATH"); //hang up
            bell_fire_3--;
            b_ATD_fire_3 = true;
            break;
          }
        }
        else if (bell_fire_3 == 0) {
          ++flag_telephone_loop_fire;
          flag_telephone_fire = 1;
          bell_fire_3 = bell;
          break;
        }
      }
    }
    else if (flag_telephone_loop_fire > max_flag_telephone_loop) {
      b_gsm_flag_fire = true;
      break;
    }
  }
  while (fire_state == 1 && b_gsm_flag_fire_ok == true) {
    gsm_sms_ok_1_fire();
    delay(5000);
    if (b_sms_t2_fire_ok) {
      gsm_sms_ok_2_fire();
      b_sms_t2_fire_ok = false;
    }
    else if (b_sms_t3_fire_ok) {
      gsm_sms_ok_3_fire();
      b_sms_t3_fire_ok = false;
    }
    b_gsm_flag_fire_ok = false ;
    break;
  }
}

///////////////////////////////////////////

void Setup_therm() {
  bool   Setup_flag = true;
  while (Setup_flag) {
    //EXIT menu με χρονομετρο η buttonState1
    if  ( millis() - startMillis > period) { //true until the period elapses.  Note that this is the reverse of BWOD
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print(">>>EXIT<<<");
      delay(2000);
      lcd.clear();
      EEPROM.get(e_therm_T1, therm_T1);
      EEPROM.get(e_proti_D, proti_D);
      EEPROM.get(e_deuteri_D, deuteri_D);
      EEPROM.get(e_triti_D, triti_D);
      EEPROM.get(e_COOL, COOL);
      EEPROM.get(e_HEAT, HEAT);
      EEPROM.get(e_alarm_low, alarm_low);
      EEPROM.get(e_alarm_high, alarm_high);
      EEPROM.get(e_mode, mode);
      Setup_flag = false;
      central_menu = false;
      update_Screen = true ;
      Moto_Run = true ;
      break;
    }

    if (menu == 1) {
      bool bool_T1 = true;
      lcd.clear();
      delay(1000);

      while (bool_T1) {
        lcd.setCursor(6, 0);
        lcd.print("TEMP_T1");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        if (therm_T1 >= 0) {
          lcd.setCursor(9, 1);
          lcd.print(" ");
          lcd.setCursor(10, 1);
          lcd.print(therm_T1);
        }
        else  {
          lcd.setCursor(9, 1);
          lcd.print(therm_T1);
        }

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_therm_T1, therm_T1);
          delay(2000);
          lcd.clear();
          bool_T1 = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_therm_T1, therm_T1);
          delay(2000);
          lcd.clear();
          bool_T1 = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
        }

        if ( buttonState2 == LOW   ) {
          therm_T1 = therm_T1 + how_match ;
        }
        if ( buttonState3 == LOW   ) {
          therm_T1 = therm_T1 - how_match ;
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_therm_T1, therm_T1);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_therm_T1, therm_T1);
          bool_T1 = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 2) {
      bool bool_proti_D = true;
      lcd.clear();
      delay(1000);

      while (bool_proti_D) {
        lcd.setCursor(6, 0);
        lcd.print("STEP 1");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        lcd.setCursor(10, 1);
        lcd.print(proti_D);

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_proti_D, proti_D);
          delay(2000);
          lcd.clear();
          bool_proti_D = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_proti_D, proti_D);
          delay(2000);
          lcd.clear();
          bool_proti_D = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }

        if ( buttonState2 == LOW   ) {
          proti_D = proti_D + how_match ;
          if ( proti_D > temp_diff_max ) {
            proti_D = temp_diff_max;
          }
        }
        if ( buttonState3 == LOW   ) {
          proti_D = proti_D - how_match ;
          if ( proti_D < temp_diff_min ) {
            proti_D = temp_diff_min;
          }
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_proti_D, proti_D);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_proti_D, proti_D);
          bool_proti_D = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 3) {
      bool bool_deuteri_D = true;;
      lcd.clear();
      delay(1000);

      while (bool_deuteri_D) {
        lcd.setCursor(6, 0);
        lcd.print("STEP 2");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        lcd.setCursor(10, 1);
        lcd.print(deuteri_D);

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_deuteri_D, deuteri_D);
          delay(2000);
          lcd.clear();
          bool_deuteri_D = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_deuteri_D, deuteri_D);
          delay(2000);
          lcd.clear();
          bool_deuteri_D = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          deuteri_D = deuteri_D + how_match ;
          if ( deuteri_D > temp_diff_max ) {
            deuteri_D = temp_diff_max;
          }
        }
        if ( buttonState3 == LOW   ) {
          deuteri_D = deuteri_D - how_match ;
          if ( deuteri_D < temp_diff_min ) {
            deuteri_D = temp_diff_min;
          }
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_deuteri_D, deuteri_D);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_deuteri_D, deuteri_D);
          bool_deuteri_D = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 4) {
      bool bool_triti_D = true;;
      lcd.clear();
      delay(1000);

      while (bool_triti_D) {
        lcd.setCursor(6, 0);
        lcd.print("STEP 3");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        lcd.setCursor(10, 1);
        lcd.print(triti_D);

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_triti_D, triti_D);
          delay(2000);
          lcd.clear();
          bool_triti_D = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_triti_D, triti_D);
          delay(2000);
          lcd.clear();
          bool_triti_D = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          triti_D = triti_D + how_match ;
          if ( triti_D > temp_diff_max ) {
            triti_D = temp_diff_max;
          }
        }
        if ( buttonState3 == LOW   ) {
          triti_D = triti_D - how_match ;
          if ( triti_D < temp_diff_min ) {
            triti_D = temp_diff_min;
          }
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_triti_D, triti_D);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_triti_D, triti_D);
          bool_triti_D = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 5) {
      bool bool_COOL = true;
      lcd.clear();
      delay(1000);

      while (bool_COOL) {
        lcd.setCursor(7, 0);
        lcd.print("COOL");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        if (COOL >= 0) {
          lcd.setCursor(9, 1);
          lcd.print(" ");
          lcd.setCursor(10, 1);
          lcd.print(COOL);
        }
        else  {
          lcd.setCursor(9, 1);
          lcd.print(COOL);
        }

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_COOL, COOL);
          delay(2000);
          lcd.clear();
          bool_COOL = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_COOL, COOL);
          delay(2000);
          lcd.clear();
          bool_COOL = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          COOL = COOL + how_match ;
        }
        if ( buttonState3 == LOW   ) {
          COOL = COOL - how_match ;
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_COOL, COOL);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_COOL, COOL);
          bool_COOL = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 6) {
      bool bool_HEAT = true;
      lcd.clear();
      delay(1000);

      while (bool_HEAT) {
        lcd.setCursor(7, 0);
        lcd.print("HEAT");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        if (HEAT >= 0) {
          lcd.setCursor(9, 1);
          lcd.print(" ");
          lcd.setCursor(10, 1);
          lcd.print(HEAT);
        }
        else  {
          lcd.setCursor(9, 1);
          lcd.print(HEAT);
        }

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_HEAT, HEAT);
          delay(2000);
          lcd.clear();
          bool_HEAT = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_HEAT, HEAT);
          delay(2000);
          lcd.clear();
          bool_HEAT = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          HEAT = HEAT + how_match ;
        }
        if ( buttonState3 == LOW   ) {
          HEAT = HEAT - how_match ;
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_HEAT, HEAT);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_HEAT, HEAT);
          bool_HEAT = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 7) {
      bool bool_alarm_low = true;
      lcd.clear();
      delay(1000);

      while (bool_alarm_low) {
        lcd.setCursor(5, 0);
        lcd.print("ALARM LOW");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        if (alarm_low >= 0) {
          lcd.setCursor(9, 1);
          lcd.print(" ");
          lcd.setCursor(10, 1);
          lcd.print(alarm_low);
        }
        else  {
          lcd.setCursor(0, 1);
          lcd.print(alarm_low);
        }

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_alarm_low, alarm_low);
          delay(2000);
          lcd.clear();
          bool_alarm_low = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_alarm_low, alarm_low);
          delay(2000);
          lcd.clear();
          bool_alarm_low = false ;
          Setup_flag = false;
          central_menu = true;
          /*update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          alarm_low = alarm_low + how_match ;
        }
        if ( buttonState3 == LOW   ) {
          alarm_low = alarm_low - how_match ;
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_alarm_low, alarm_low);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_alarm_low, alarm_low);
          bool_alarm_low = false ;
          Setup_flag = false;
          central_menu = true;
          /*update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 8) {
      bool bool_alarm_high = true;
      lcd.clear();
      delay(1000);

      while (bool_alarm_high) {
        lcd.setCursor(5, 0);
        lcd.print("ALARM HIGH");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        if (alarm_high >= 0) {
          lcd.setCursor(9, 1);
          lcd.print(" ");
          lcd.setCursor(10, 1);
          lcd.print(alarm_high);
        }
        else  {
          lcd.setCursor(9, 1);
          lcd.print(alarm_high);
        }

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_alarm_high, alarm_high);
          delay(2000);
          lcd.clear();
          bool_alarm_high = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_alarm_high, alarm_high);
          delay(2000);
          lcd.clear();
          bool_alarm_high = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          alarm_high = alarm_high + how_match ;
        }
        if ( buttonState3 == LOW   ) {
          alarm_high = alarm_high - how_match ;
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_alarm_high, alarm_high);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_alarm_high, alarm_high);
          bool_alarm_high = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 9) {
      bool bool_mode = true;
      lcd.clear();
      delay(1000);

      while (bool_mode) {
        lcd.setCursor(7, 0);
        lcd.print("MODE");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        lcd.setCursor(10, 1);
        lcd.print(mode);

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_mode, mode);
          delay(2000);
          lcd.clear();
          bool_mode = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_mode, mode);
          delay(2000);
          lcd.clear();
          bool_mode = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW   ) {
          mode = mode + 1 ;
          if ( mode > 2 ) {
            mode = 2;
          }
        }
        if ( buttonState3 == LOW   ) {
          mode = mode - 1 ;
          if ( mode < 1 ) {
            mode = 1;
          }
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_mode, mode);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_mode, mode);
          bool_mode = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 10) {
      String tel_1 = "+" ;
      uint8_t thesi_1 = 1 ;
      int numper_1 = 0 ;
      char numper1;
      phone_flag_1 = true ;
      lcd.clear();
      delay(1000);

      while (phone_flag_1) {
        lcd.setCursor(0, 1);
        lcd.print("+");
        lcd.setCursor(thesi_1, 1);
        lcd.print(numper1);
        lcd.setCursor(thesi_1, 2);
        lcd.print("^");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(6, 3);
        lcd.print("DEL");
        lcd.setCursor(12, 3);
        lcd.print("+");
        lcd.setCursor(18, 3);
        lcd.print("OK");

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (   millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          delay(2000);
          lcd.clear();
          phone_flag_1 = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (numper_1 == 0) {
          numper1 = '0';
        }
        if (numper_1 == 1) {
          numper1 = '1';
        }
        if (numper_1 == 2) {
          numper1 = '2';
        }
        if (numper_1 == 3) {
          numper1 = '3';
        }
        if (numper_1 == 4) {
          numper1 = '4';
        }
        if (numper_1 == 5) {
          numper1 = '5';
        }
        if (numper_1 == 6) {
          numper1 = '6';
        }
        if (numper_1 == 7) {
          numper1 = '7';
        }
        if (numper_1 == 8) {
          numper1 = '8';
        }
        if (numper_1 == 9) {
          numper1 = '9';
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          delay(2000);
          lcd.clear();
          phone_flag_1 = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if (buttonState2 == LOW) {
          thesi_1 = thesi_1 - 1 ;
          if (thesi_1 < 1) {
            thesi_1 = 1;
          }
          numper_1 = 0;
          tel_1.remove(thesi_1, 1);
          lcd.setCursor((thesi_1 + 1), 1);
          lcd.print(" ");
          lcd.setCursor((thesi_1 + 1), 2);
          lcd.print(" ");
          delay(150);
        }

        if (buttonState3 == LOW) {
          numper_1 = numper_1 + 1 ;
          if (numper_1 > 9) {
            numper_1 = 0 ;
          }
          delay(100);
        }

        if (buttonState4 == LOW) {
          tel_1 = tel_1 + numper1 ;
          thesi_1 = thesi_1 + 1 ;
          numper_1 = 0;
          lcd.setCursor((thesi_1 - 1), 2);
          lcd.print(" ");
          delay(150);
          if (thesi_1 > 12 ) {
            TEL_1 = "";
            lcd.clear(); lcd.setCursor(3, 0); lcd.print(String(tel_1));
            for (int i_1 = 0 ; i_1 < tel_1.length() ; i_1++)
            {
              EEPROM.write( e_TEL_1 + i_1, tel_1[i_1] );
            }
            tel_1 = "";
            delay(5000);
            for (byte b_1 = 0 ; b_1 < 13 ; b_1++) { //13 is the maximum lenght of an IP adress with dots
              char f_1 = EEPROM.read(e_TEL_1 + b_1);
              TEL_1 += (f_1);
            }
            phone_flag_1 = false ;
            Setup_flag = false;
            central_menu = true;
            /* update_Screen = true ;
              Moto_Run =  true ;*/
            break ;
          }
        }
      }
    }

    else if (menu == 11) {
      String tel_2 = "+" ;
      uint8_t thesi_2 = 1 ;
      int   numper_2 = 0 ;
      char numper2;
      phone_flag_2 = true ;
      lcd.clear();
      delay(1000);

      while (phone_flag_2) {
        lcd.setCursor(0, 1);
        lcd.print("+");
        lcd.setCursor(thesi_2, 1);
        lcd.print(numper2);
        lcd.setCursor(thesi_2, 2);
        lcd.print("^");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(6, 3);
        lcd.print("DEL");
        lcd.setCursor(12, 3);
        lcd.print("+");
        lcd.setCursor(18, 3);
        lcd.print("OK");

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          delay(2000);
          lcd.clear();
          phone_flag_2 = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (numper_2 == 0) {
          numper2 = '0';
        }
        if (numper_2 == 1) {
          numper2 = '1';
        }
        if (numper_2 == 2) {
          numper2 = '2';
        }
        if (numper_2 == 3) {
          numper2 = '3';
        }
        if (numper_2 == 4) {
          numper2 = '4';
        }
        if (numper_2 == 5) {
          numper2 = '5';
        }
        if (numper_2 == 6) {
          numper2 = '6';
        }
        if (numper_2 == 7) {
          numper2 = '7';
        }
        if (numper_2 == 8) {
          numper2 = '8';
        }
        if (numper_2 == 9) {
          numper2 = '9';
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          delay(2000);
          lcd.clear();
          phone_flag_2 = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if (buttonState2 == LOW) {
          thesi_2 = thesi_2 - 1 ;
          if (thesi_2 < 1) {
            thesi_2 = 1;
          }
          numper_2 = 0;
          tel_2.remove(thesi_2, 1);
          lcd.setCursor((thesi_2 + 1), 1);
          lcd.print(" ");
          lcd.setCursor((thesi_2 + 1), 2);
          lcd.print(" ");
          delay(150);
        }

        if (buttonState3 == LOW) {
          numper_2 = numper_2 + 1 ;
          if (numper_2 > 9) {
            numper_2 = 0 ;
          }
          delay(100);
        }

        if (buttonState4 == LOW) {
          tel_2 = tel_2 + numper2 ;
          thesi_2 = thesi_2 + 1 ;
          numper_2 = 0;
          lcd.setCursor((thesi_2 - 1), 2);
          lcd.print(" ");
          delay(150);
          if (thesi_2 > 12 ) {
            TEL_2 = "";
            lcd.clear(); lcd.setCursor(3, 0); lcd.print(String(tel_2));
            for (int i_2 = 0 ; i_2 < tel_2.length() ; i_2++)
            {
              EEPROM.write( e_TEL_2 + i_2, tel_2[i_2] );
            }
            tel_2 = "";
            delay(5000);
            for (byte b_2 = 0 ; b_2 < 13 ; b_2++) { //13 is the maximum lenght of an IP adress with dots
              char f_2 = EEPROM.read(e_TEL_2 + b_2);
              TEL_2 += (f_2);
            }
            phone_flag_2 = false ;
            Setup_flag = false;
            central_menu = true;
            /*  update_Screen = true ;
              Moto_Run =  true ;*/
            break ;
          }
        }
      }
    }


    else if (menu == 12) {
      String tel_3 = "+" ;
      uint8_t thesi_3 = 1 ;
      int   numper_3 = 0 ;
      char numper3;
      phone_flag_3 = true ;
      lcd.clear();
      delay(1000);

      while (phone_flag_3) {
        lcd.setCursor(0, 1);
        lcd.print("+");
        lcd.setCursor(thesi_3, 1);
        lcd.print(numper3);
        lcd.setCursor(thesi_3, 2);
        lcd.print("^");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(6, 3);
        lcd.print("DEL");
        lcd.setCursor(12, 3);
        lcd.print("+");
        lcd.setCursor(18, 3);
        lcd.print("OK");

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          delay(2000);
          lcd.clear();
          phone_flag_3 = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (numper_3 == 0) {
          numper3 = '0';
        }
        if (numper_3 == 1) {
          numper3 = '1';
        }
        if (numper_3 == 2) {
          numper3 = '2';
        }
        if (numper_3 == 3) {
          numper3 = '3';
        }
        if (numper_3 == 4) {
          numper3 = '4';
        }
        if (numper_3 == 5) {
          numper3 = '5';
        }
        if (numper_3 == 6) {
          numper3 = '6';
        }
        if (numper_3 == 7) {
          numper3 = '7';
        }
        if (numper_3 == 8) {
          numper3 = '8';
        }
        if (numper_3 == 9) {
          numper3 = '9';
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          delay(2000);
          lcd.clear();
          phone_flag_3 = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if (buttonState2 == LOW) {
          thesi_3 = thesi_3 - 1 ;
          if (thesi_3 < 1) {
            thesi_3 = 1;
          }
          numper_3 = 0;
          tel_3.remove(thesi_3, 1);
          lcd.setCursor((thesi_3 + 1), 1);
          lcd.print(" ");
          lcd.setCursor((thesi_3 + 1), 2);
          lcd.print(" ");
          delay(150);
        }

        if (buttonState3 == LOW) {
          numper_3 = numper_3 + 1 ;
          if (numper_3 > 9) {
            numper_3 = 0 ;
          }
          delay(100);
        }

        if (buttonState4 == LOW) {
          tel_3 = tel_3 + numper3 ;
          thesi_3 = thesi_3 + 1 ;
          numper_3 = 0;
          lcd.setCursor((thesi_3 - 1), 2);
          lcd.print(" ");
          delay(150);
          if (thesi_3 > 12 ) {
            TEL_3 = "";
            lcd.clear(); lcd.setCursor(3, 0); lcd.print(String(tel_3));
            for (int i_3 = 0 ; i_3 < tel_3.length() ; i_3++)
            {
              EEPROM.write( e_TEL_3 + i_3, tel_3[i_3] );
            }
            tel_3 = "";
            delay(5000);
            for (byte b_3 = 0 ; b_3 < 13 ; b_3++) { //13 is the maximum lenght of an IP adress with dots
              char f_3 = EEPROM.read(e_TEL_3 + b_3);
              TEL_3 += (f_3);
            }
            phone_flag_3 = false ;
            Setup_flag = false;
            central_menu = true;
            /*  update_Screen = true ;
              Moto_Run =  true ;*/
            break ;
          }
        }
      }
    }

    else if (menu == 13) {
      bool bool_bell = true;
      lcd.clear();
      delay(1000);

      while (bool_bell) {
        lcd.setCursor(7, 0);
        lcd.print("BELL");
        lcd.setCursor(5, 1);
        lcd.print("NEW:");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");
        lcd.setCursor(18, 3);
        lcd.print("OK");
        if (bell <= 9) {
          lcd.setCursor(9, 1);
          lcd.print(" ");
          lcd.setCursor(10, 1);
          lcd.print(bell);
        }
        else {
          lcd.setCursor(9, 1);
          lcd.print(bell);
        }

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          EEPROM.get(e_bell, bell);
          delay(2000);
          lcd.clear();
          bool_bell = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if ( buttonState1 == LOW   ) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          EEPROM.get(e_bell, bell);
          delay(2000);
          lcd.clear();
          bool_bell = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }

        if ( buttonState2 == LOW   ) {
          bell = bell + 1;
          if ( bell > bell_max ) {
            bell = bell_max;
          }
        }
        if ( buttonState3 == LOW   ) {
          bell = bell - 1;
          if ( bell < bell_min ) {
            bell = bell_min;
          }
        }

        if ( buttonState4 == LOW   ) {
          lcd.clear();
          lcd.setCursor(3, 1);
          lcd.print("***** OK *****");
          EEPROM.put(e_bell, bell);
          delay (2000);
          lcd.clear();
          EEPROM.get(e_bell, bell);
          bool_bell = false ;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break;
        }
      }
    }

    else if (menu == 14) {
      int menuTimer = 0;
      bool booTimerRelay = true;
      lcd.clear();
      delay(1000);

      while (booTimerRelay) {
        //δικοι μου χαρακτηρες
        lcd.createChar(1, pano);
        lcd.createChar(2, kato);
        lcd.createChar(7, diktis);

        if (menuTimer == 0) {
          lcd.setCursor(0, 0);
          lcd.write(7);
        }
        else {
          lcd.setCursor(0, 0);
          lcd.print(" ");
        }
        lcd.setCursor(1, 0);
        lcd.print("ON/OFF :");
        if (timerONOFF == 0) {
          lcd.setCursor(14, 0);
          lcd.print("OFF");
        }
        else {
          lcd.setCursor(14, 0);
          lcd.print("ON ");
        }
        if (menuTimer == 1) {
          lcd.setCursor(0, 1);
          lcd.write(7);
        }
        else {
          lcd.setCursor(0, 1);
          lcd.print(" ");
        }
        lcd.setCursor(1, 1);
        lcd.print("RELAY :");
        lcd.setCursor(14, 1);
        lcd.print(timerRelay);
        if (menuTimer == 2) {
          lcd.setCursor(0, 2);
          lcd.write(7);
        }
        else {
          lcd.setCursor(0, 2);
          lcd.print(" ");
        }
        lcd.setCursor(1, 2);
        lcd.print("TIME :");
        //lcd.setCursor(14, 2);
        //lcd.print(timerTIME);
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.write(2);
        lcd.setCursor(12, 3);
        lcd.write(1);
        lcd.setCursor(18, 3);
        lcd.print("OK");

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          delay(2000);
          lcd.clear();
          booTimerRelay = false;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if ( buttonState1 == LOW   ) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          delay(2000);
          lcd.clear();
          booTimerRelay = false;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }
        // lcd.clear();

        if (buttonState2 == 0) {
          menuTimer++;
          if (menuTimer > 2) {
            menuTimer = 0;
          }
        }
        if (buttonState3 == 0) {
          menuTimer--;
          if (menuTimer < 0) {
            menuTimer = 2;
          }
        }


        if (buttonState4 == 0 ) {
          if (menuTimer == 0) {
            bool menuTimer0 = true;
            lcd.clear();
            delay(1000);

            while (menuTimer0) {
              lcd.setCursor(7, 0);
              lcd.print("ON/OFF");
              lcd.setCursor(0, 3);
              lcd.print("BACK");
              lcd.setCursor(7, 3);
              lcd.print("ON");
              lcd.setCursor(12, 3);
              lcd.print("OFF");
              lcd.setCursor(18, 3);
              lcd.print("OK");

              //αναγνωση πληκτρων
              buttonVooidMenu();

              //EXIT menu με χρονομετρο
              if (  millis() - startMillis > period) {
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print(">>>EXIT<<<");
                delay(2000);
                lcd.clear();
                EEPROM.get(e_timerONOFF, timerONOFF);
                menuTimer0 = false;
                booTimerRelay = false;
                Setup_flag = false;
                central_menu = false;
                update_Screen = true ;
                Moto_Run =  true ;
                break ;
              }

              if ( buttonState1 == LOW   ) {
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print("--RETURN--");
                delay(2000);
                lcd.clear();
                EEPROM.get(e_timerONOFF, timerONOFF);
                menuTimer0 = false;
                /* booTimerRelay = false;
                  Setup_flag = false;
                  central_menu = false;
                  update_Screen = true ;
                  Moto_Run =  true ;*/
                break ;
              }

              if (buttonState2 == 0) {
                timerONOFF++;
                if (timerONOFF > 1) {
                  timerONOFF = 1;
                }
              }
              if (buttonState3 == 0) {
                timerONOFF--;
                if (timerONOFF < 0) {
                  timerONOFF = 0;
                }
              }
              if (timerONOFF == 0) {
                lcd.setCursor(9, 1);
                lcd.print("OFF");
              }
              else {
                lcd.setCursor(9, 1);
                lcd.print("ON ");
              }

              if (buttonState4 == 0) {
                lcd.clear();
                lcd.setCursor(3, 1);
                lcd.print("***** OK *****");
                EEPROM.put(e_timerONOFF, timerONOFF);
                delay (2000);
                lcd.clear();
                EEPROM.get(e_timerONOFF, timerONOFF);
                menuTimer0 = false;
                /* booTimerRelay = false;
                  Setup_flag = false;
                  central_menu = false;
                  update_Screen = true ;
                  Moto_Run =  true ;*/
                lcd.clear();
                break ;
              }
            }
          }
          else if (menuTimer == 1) {
            bool menuTimer1 = true;
            lcd.clear();
            delay(1000);

            while (menuTimer1) {
              lcd.setCursor(7, 0);
              lcd.print("RELAY");
              lcd.setCursor(0, 3);
              lcd.print("BACK");
              lcd.setCursor(7, 3);
              lcd.print("+");
              lcd.setCursor(12, 3);
              lcd.print("-");
              lcd.setCursor(18, 3);
              lcd.print("OK");

              //αναγνωση πληκτρων
              buttonVooidMenu();

              //EXIT menu με χρονομετρο
              if (  millis() - startMillis > period) {
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print(">>>EXIT<<<");
                delay(2000);
                lcd.clear();
                EEPROM.get(e_timerRelay, timerRelay);
                menuTimer1 = false;
                booTimerRelay = false;
                Setup_flag = false;
                central_menu = false;
                update_Screen = true ;
                Moto_Run =  true ;
                break ;
              }

              if ( buttonState1 == LOW   ) {
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print("--RETURN--");
                delay(2000);
                lcd.clear();
                EEPROM.get(e_timerRelay, timerRelay);
                menuTimer1 = false;
                /* booTimerRelay = false;
                  Setup_flag = false;
                  central_menu = false;
                  update_Screen = true ;
                  Moto_Run =  true ;*/
                break ;
              }

              if (buttonState2 == 0) {
                timerRelay++;
                if (timerRelay > 4) {
                  timerRelay = 1;
                }
              }
              if (buttonState3 == 0) {
                timerRelay--;
                if (timerRelay < 1) {
                  timerRelay = 4;
                }
              }
              lcd.setCursor(9, 1);
              lcd.print(timerRelay);

              if (buttonState4 == 0) {
                lcd.clear();
                lcd.setCursor(3, 1);
                lcd.print("***** OK *****");
                EEPROM.put(e_timerRelay, timerRelay);
                delay (2000);
                lcd.clear();
                EEPROM.get(e_timerRelay, timerRelay);
                menuTimer1 = false;
                /* booTimerRelay = false;
                  Setup_flag = false;
                  central_menu = false;
                  update_Screen = true ;
                  Moto_Run =  true ;*/
                break ;
              }
            }
          }
          else if (menuTimer == 2) {
            int menuTimerTime = 0;
            bool menuTimer2 = true;
            lcd.clear();
            delay(1000);

            while (menuTimer2) {
              //δικοι μου χαρακτηρες
              lcd.createChar(1, pano);
              lcd.createChar(2, kato);
              lcd.createChar(7, diktis);

              if (menuTimerTime == 0) {
                lcd.setCursor(0, 0);
                lcd.write(7);
              }
              else {
                lcd.setCursor(0, 0);
                lcd.print(" ");
              }
              lcd.setCursor(1, 0);
              lcd.print("time ON :");
              if (timerON < 10) {
                lcd.setCursor(10, 0);
                lcd.print("   ");
                lcd.setCursor(13, 0);
                lcd.print(timerON);
              }
              else if (timerON >= 10 && timerON < 100) {
                lcd.setCursor(10, 0);
                lcd.print("  ");
                lcd.setCursor(12, 0);
                lcd.print(timerON);
              }
              else if (timerON >= 100 && timerON < 1000) {
                lcd.setCursor(10, 0);
                lcd.print(" ");
                lcd.setCursor(11, 0);
                lcd.print(timerON);
              }
              else {
                lcd.setCursor(10, 0);
                lcd.print(timerON);
              }
              if (menuTimerTime == 1) {
                lcd.setCursor(0, 1);
                lcd.write(7);
              }
              else {
                lcd.setCursor(0, 1);
                lcd.print(" ");
              }
              lcd.setCursor(1, 1);
              lcd.print("time OFF:");
              if (timerOFF < 10) {
                lcd.setCursor(10, 1);
                lcd.print("   ");
                lcd.setCursor(13, 1);
                lcd.print(timerOFF);
              }
              else if (timerOFF >= 10 && timerOFF < 100) {
                lcd.setCursor(10, 1);
                lcd.print("  ");
                lcd.setCursor(12, 1);
                lcd.print(timerOFF);
              }
              else if (timerOFF >= 100 && timerOFF < 1000) {
                lcd.setCursor(10, 1);
                lcd.print(" ");
                lcd.setCursor(11, 1);
                lcd.print(timerOFF);
              }
              else {
                lcd.setCursor(10, 1);
                lcd.print(timerOFF);
              }
              lcd.setCursor(0, 3);
              lcd.print("BACK");
              lcd.setCursor(7, 3);
              lcd.write(2);
              lcd.setCursor(12, 3);
              lcd.write(1);
              lcd.setCursor(18, 3);
              lcd.print("OK");

              //αναγνωση πληκτρων
              buttonVooidMenu();

              //EXIT menu με χρονομετρο
              if (  millis() - startMillis > period) {
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print(">>>EXIT<<<");
                delay(2000);
                lcd.clear();
                EEPROM.get(e_timerON, timerON);
                EEPROM.get(e_timerOFF, timerOFF);
                menuTimer2 = false;
                booTimerRelay = false;
                Setup_flag = false;
                central_menu = false;
                update_Screen = true ;
                Moto_Run =  true ;
                break ;
              }

              if ( buttonState1 == LOW   ) {
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print("--RETURN--");
                delay(2000);
                lcd.clear();
                EEPROM.get(e_timerON, timerON);
                EEPROM.get(e_timerOFF, timerOFF);
                menuTimer2 = false;
                /* booTimerRelay = false;
                  Setup_flag = false;
                  central_menu = false;
                  update_Screen = true ;
                  Moto_Run =  true ;*/
                break ;
              }

              if (buttonState2 == 0) {
                menuTimerTime++;
                if (menuTimerTime > 1) {
                  menuTimerTime = 0;
                }
              }
              if (buttonState3 == 0) {
                menuTimerTime--;
                if (menuTimerTime < 0) {
                  menuTimerTime = 1;
                }
              }


              if (buttonState4 == 0) {
                if (menuTimerTime == 0) {
                  bool menuTimerTime0 = true;
                  lcd.clear();
                  delay(1000);

                  while (menuTimerTime0) {
                    lcd.setCursor(6, 0);
                    lcd.print("time ON");
                    lcd.setCursor(0, 3);
                    lcd.print("BACK");
                    lcd.setCursor(7, 3);
                    lcd.print("+");
                    lcd.setCursor(12, 3);
                    lcd.print("-");
                    lcd.setCursor(18, 3);
                    lcd.print("OK");

                    //αναγνωση πληκτρων
                    buttonVooidMenu();

                    //EXIT menu με χρονομετρο
                    if (  millis() - startMillis > period) {
                      lcd.clear();
                      lcd.setCursor(5, 1);
                      lcd.print(">>>EXIT<<<");
                      delay(2000);
                      lcd.clear();
                      EEPROM.get(e_timerON, timerON);
                      menuTimerTime0 = false;
                      menuTimer2 = false;
                      booTimerRelay = false;
                      Setup_flag = false;
                      central_menu = false;
                      update_Screen = true ;
                      Moto_Run =  true ;
                      break ;
                    }
                    if ( buttonState1 == LOW   ) {
                      lcd.clear();
                      lcd.setCursor(5, 1);
                      lcd.print("--RETURN--");
                      delay(2000);
                      lcd.clear();
                      EEPROM.get(e_timerON, timerON);
                      menuTimerTime0 = false;
                      /* menuTimer2 = false;
                        booTimerRelay = false;
                        Setup_flag = false;
                        central_menu = false;
                        update_Screen = true ;
                        Moto_Run =  true ;*/
                      break ;
                    }
                    if (buttonState2 == 0) {
                      timerON++;
                      if (timerON > timerTimeMax) {
                        timerON = 0;
                      }
                    }
                    if (buttonState3 == 0) {
                      timerON--;
                      if (timerON <= 0) {
                        timerON = timerTimeMax;
                      }
                    }
                    if (timerON < 10) {
                      lcd.setCursor(7, 1);
                      lcd.print("   ");
                      lcd.setCursor(10, 1);
                      lcd.print(timerON);
                    }
                    else if (timerON >= 10 && timerON < 100) {
                      lcd.setCursor(7, 1);
                      lcd.print("  ");
                      lcd.setCursor(9, 1);
                      lcd.print(timerON);
                    }
                    else if (timerON >= 100 && timerON < 1000) {
                      lcd.setCursor(7, 1);
                      lcd.print(" ");
                      lcd.setCursor(8, 1);
                      lcd.print(timerON);
                    }
                    else {
                      lcd.setCursor(7, 1);
                      lcd.print(timerON);
                    }

                    if (buttonState4 == 0) {
                      lcd.clear();
                      lcd.setCursor(3, 1);
                      lcd.print("***** OK *****");
                      EEPROM.put(e_timerON, timerON);
                      delay (2000);
                      lcd.clear();
                      EEPROM.get(e_timerON, timerON);
                      menuTimerTime0 = false;
                      /* menuTimer2 = false;
                        booTimerRelay = false;
                         Setup_flag = false;
                         central_menu = false;
                         update_Screen = true ;
                         Moto_Run =  true ;*/
                      break ;
                    }
                  }
                }
                if (menuTimerTime == 1) {
                  bool menuTimerTime1 = true;
                  lcd.clear();
                  delay(1000);

                  while (menuTimerTime1) {
                    lcd.setCursor(6, 0);
                    lcd.print("time OFF");
                    lcd.setCursor(0, 3);
                    lcd.print("BACK");
                    lcd.setCursor(7, 3);
                    lcd.print("+");
                    lcd.setCursor(12, 3);
                    lcd.print("-");
                    lcd.setCursor(18, 3);
                    lcd.print("OK");

                    //αναγνωση πληκτρων
                    buttonVooidMenu();

                    //EXIT menu με χρονομετρο
                    if (  millis() - startMillis > period) {
                      lcd.clear();
                      lcd.setCursor(5, 1);
                      lcd.print(">>>EXIT<<<");
                      delay(2000);
                      lcd.clear();
                      EEPROM.get(e_timerOFF, timerOFF);
                      menuTimerTime1 = false;
                      menuTimer2 = false;
                      booTimerRelay = false;
                      Setup_flag = false;
                      central_menu = false;
                      update_Screen = true ;
                      Moto_Run =  true ;
                      break ;
                    }
                    if ( buttonState1 == LOW   ) {
                      lcd.clear();
                      lcd.setCursor(5, 1);
                      lcd.print("--RETURN--");
                      delay(2000);
                      lcd.clear();
                      EEPROM.get(e_timerOFF, timerOFF);
                      menuTimerTime1 = false;
                      /* menuTimer2 = false;
                        booTimerRelay = false;
                        Setup_flag = false;
                        central_menu = false;
                        update_Screen = true ;
                        Moto_Run =  true ;*/
                      break ;
                    }
                    if (buttonState2 == 0) {
                      timerOFF++;
                      if (timerOFF > timerTimeMax) {
                        timerOFF = 0;
                      }
                    }
                    if (buttonState3 == 0) {
                      timerOFF--;
                      if (timerOFF <= 0) {
                        timerOFF = timerTimeMax;
                      }
                    }
                    if (timerOFF < 10) {
                      lcd.setCursor(7, 1);
                      lcd.print("   ");
                      lcd.setCursor(10, 1);
                      lcd.print(timerOFF);
                    }
                    else if (timerOFF >= 10 && timerOFF < 100) {
                      lcd.setCursor(7, 1);
                      lcd.print("  ");
                      lcd.setCursor(9, 1);
                      lcd.print(timerOFF);
                    }
                    else if (timerOFF >= 100 && timerOFF < 1000) {
                      lcd.setCursor(7, 1);
                      lcd.print(" ");
                      lcd.setCursor(8, 1);
                      lcd.print(timerOFF);
                    }
                    else {
                      lcd.setCursor(7, 1);
                      lcd.print(timerOFF);
                    }

                    if (buttonState4 == 0) {
                      lcd.clear();
                      lcd.setCursor(3, 1);
                      lcd.print("***** OK *****");
                      EEPROM.put(e_timerOFF, timerOFF);
                      delay (2000);
                      lcd.clear();
                      EEPROM.get(e_timerOFF, timerOFF);
                      menuTimerTime1 = false;
                      /* menuTimer2 = false;
                        booTimerRelay = false;
                         Setup_flag = false;
                         central_menu = false;
                         update_Screen = true ;
                         Moto_Run =  true ;*/
                      break ;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    else if (menu == 15) {
      bool bootestrelay = true;
      lcd.clear();

      while (bootestrelay) {
        lcd.setCursor(4, 1);
        lcd.print("TEST RELAY");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(7, 3);
        lcd.print("+");
        lcd.setCursor(12, 3);
        lcd.print("-");

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          delay(2000);
          lcd.clear();
          bootestrelay = false;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if ( buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          delay(2000);
          lcd.clear();
          bootestrelay = false;
          Setup_flag = false;
          central_menu = true;
          /* update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if ( buttonState2 == LOW) {
          test_relay++;
          if (test_relay > 6) {
            test_relay = 0;
          }
        }
        if ( buttonState3 == LOW) {
          test_relay--;
          if (test_relay < 0) {
            test_relay = 6;
          }
        }

        if (test_relay == 0) {
          lcd.setCursor(0, 2);
          lcd.print("____");
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          digitalWrite(cool, HIGH);
          digitalWrite(heat, HIGH);
        }
        // 1 taxytita
        else if (test_relay == 1 ) {
          lcd.setCursor(0, 2);
          lcd.print("1___");
          lcd.setCursor(4, 2);
          lcd.print("    ");
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          digitalWrite(cool, HIGH);
          digitalWrite(heat, HIGH);
          delay(2000);
          digitalWrite(tax_01, LOW);
        }
        // 2 taxytita
        else if (test_relay == 2 ) {
          lcd.setCursor(0, 2);
          lcd.print("_2__");
          lcd.setCursor(4, 2);
          lcd.print("    ");
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          digitalWrite(cool, HIGH);
          digitalWrite(heat, HIGH);
          delay(2000);
          digitalWrite(tax_02, LOW);
        }
        // 3 taxytita
        else if (test_relay == 3 ) {
          lcd.setCursor(0, 2);
          lcd.print("__3_");
          lcd.setCursor(4, 2);
          lcd.print("    ");
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_04, HIGH);
          digitalWrite(cool, HIGH);
          digitalWrite(heat, HIGH);
          delay(2000);
          digitalWrite(tax_03, LOW);
        }
        // 4 taxytita
        else if (test_relay == 4 ) {
          lcd.setCursor(0, 2);
          lcd.print("___4");
          lcd.setCursor(4, 2);
          lcd.print("    ");
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(cool, HIGH);
          digitalWrite(heat, HIGH);
          delay(2000);
          digitalWrite(tax_04, LOW);
        }
        //οταν ανεβαινη η θερμοκρασια ενεργοποιω τη ζεστη
        else if (test_relay == 5) {
          lcd.setCursor(0, 2);
          lcd.print("____");
          lcd.setCursor(0, 3);
          lcd.setCursor(4, 2);
          lcd.print("HT  ");
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          digitalWrite(cool, HIGH);
          delay(2000);
          digitalWrite(heat, LOW);
        }
        //οταν πεφτει η θερμοκρασια ενεργοποιω το κρυο
        else if (test_relay == 6) {
          lcd.setCursor(0, 2);
          lcd.print("____");
          lcd.setCursor(4, 2);
          lcd.print("  CL");
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          digitalWrite(heat, HIGH);
          delay(2000);
          digitalWrite(cool, LOW);
        }
      }
    }
    else if (menu == 16) {
      String S_Pin_data = "";
      String S_pin_code = "";
      String S_code = "";
      uint8_t thesi_pin = 10 ;
      uint8_t thesi_char_pin = thesi_pin - 10;
      int  numper_pin = 0 ;
      char c_numperPin;
      bool b_Pin_Code = true;
      lcd.clear();
      delay(1000);

      while (b_Pin_Code) {
        /*lcd.setCursor(5, 0);
          lcd.print("Old (");
          lcd.setCursor(10, 0);
          lcd.print(pin_code);
          lcd.setCursor(14, 0);
          lcd.print(")");*/
        lcd.setCursor(5, 1);
        lcd.print("PIN (");
        lcd.setCursor(thesi_pin, 1);
        lcd.print(c_numperPin);
        // if (thesi_pin > 13) {
        // lcd.setCursor(thesi_pin, 1);
        //  lcd.print(" ");
        // }
        lcd.setCursor(14, 1);
        lcd.print(")");
        lcd.setCursor(thesi_pin, 2);
        lcd.print("^");
        // if (thesi_pin > 13) {
        //  lcd.setCursor(thesi_pin, 2);
        //  lcd.print(" ");
        // }
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(6, 3);
        lcd.print("DEL");
        lcd.setCursor(12, 3);
        lcd.print("+");
        lcd.setCursor(18, 3);
        lcd.print("OK");

        //αναγνωση πληκτρων
        buttonVooidMenu();

        //EXIT menu με χρονομετρο
        if (  millis() - startMillis > period) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(">>>EXIT<<<");
          delay(2000);
          lcd.clear();
          b_Pin_Code = false ;
          Setup_flag = false;
          central_menu = false;
          update_Screen = true ;
          Moto_Run =  true ;
          break ;
        }

        if (numper_pin == 0) {
          c_numperPin = '0';
        }
        if (numper_pin == 1) {
          c_numperPin = '1';
        }
        if (numper_pin == 2) {
          c_numperPin = '2';
        }
        if (numper_pin == 3) {
          c_numperPin = '3';
        }
        if (numper_pin == 4) {
          c_numperPin = '4';
        }
        if (numper_pin == 5) {
          c_numperPin = '5';
        }
        if (numper_pin == 6) {
          c_numperPin = '6';
        }
        if (numper_pin == 7) {
          c_numperPin = '7';
        }
        if (numper_pin == 8) {
          c_numperPin = '8';
        }
        if (numper_pin == 9) {
          c_numperPin = '9';
        }

        if (buttonState1 == LOW) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print("--RETURN--");
          delay(2000);
          lcd.clear();
          b_Pin_Code = false ;
          Setup_flag = false;
          central_menu = true;
          /*  update_Screen = true ;
            Moto_Run =  true ;*/
          break ;
        }

        if (buttonState2 == LOW) {
          thesi_pin = thesi_pin - 1 ;
          if (thesi_pin < 10) {
            thesi_pin = 10;
          }
          numper_pin = 0;
          S_pin_code.remove(thesi_char_pin, 1);
          lcd.setCursor((thesi_pin + 1), 1);
          lcd.print(" ");
          lcd.setCursor((thesi_pin + 1), 2);
          lcd.print(" ");
          delay(150);
        }

        if (buttonState3 == LOW) {
          numper_pin = numper_pin + 1 ;
          if (numper_pin > 9) {
            numper_pin = 0 ;
          }
          delay(100);
        }

        if (buttonState4 == LOW) {
          S_pin_code = S_pin_code + c_numperPin ;
          thesi_pin = thesi_pin + 1 ;
          numper_pin = 0;
          lcd.setCursor((thesi_pin - 1), 2);
          lcd.print(" ");
          delay(150);

          if (thesi_pin > 13 ) {
            delay(1000);
            S_code = S_pin_code.substring(0, 4);
            bool b_run_code = true;
            lcd.clear();
            while (b_run_code) {
              lcd.setCursor(4, 1);
              lcd.print("Please Wait");
              Serial.println(S_code);
              Serial1.println("AT+CPIN?");

              if (Serial1.available()) {
                S_Pin_data = Serial1.readString();
                Serial.println(S_Pin_data);
                delay(delay_GSM);
                if (S_Pin_data.indexOf("+CPIN: READY") > -1) {
                  S_pin_code = "";
                  lcd.clear();
                  lcd.setCursor(4, 1);
                  lcd.print("There is no");
                  lcd.setCursor(8, 2);
                  lcd.print("PIN");
                  delay(5000);
                  b_run_code = false;
                  b_Pin_Code = false ;
                  Setup_flag = false;
                  central_menu = true;
                  /*  update_Screen = true ;
                    Moto_Run =  true ;*/
                  break ;
                }
                else if (S_Pin_data.indexOf("+CPIN: SIM PIN") > -1) {
                  delay(delay_GSM);
                  Serial1.println("AT+CPIN= " + S_code);
                  delay(delay_GSM);
                  String clck = "AT+CLCK= ";
                  clck += '"';
                  clck += "SC";
                  clck += '"';
                  clck += ',';
                  clck += "0";
                  clck += ',';
                  clck += '"';
                  clck += S_code;
                  clck += '"';
                  Serial1.println(clck);
                  delay(delay_GSM);
                  Serial1.println("AT+CPIN?");
                  delay(delay_GSM);
                  Serial1.println("AT+CMGF=1"); // Configuring TEXT mode
                  delay(delay_GSM);
                  Serial1.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
                  delay(delay_GSM);
                  Serial1.println("AT+CMGD=1,4");//DELETE all sms
                  delay(delay_GSM);
                  Serial1.println("AT+DDET=1");//DTMF
                  delay(delay_GSM);
                  Serial1.println("ATS0=3");//απαντά αυτόματα στην κλήση μετά από 3 κουδούνισμα
                  delay(delay_GSM);
                  Serial1.println("AT+CLIP=1");//αναγνωριση κλησεων
                  S_pin_code = "";
                  S_code = "";
                  clck = "";
                  lcd.clear();
                  lcd.setCursor(4, 1);
                  lcd.print("PIN removed");
                  lcd.setCursor(8, 2);
                  lcd.print("and");
                  lcd.setCursor(6, 3);
                  lcd.print("you ready");
                  delay(5000);
                  b_run_code = false;
                  b_Pin_Code = false ;
                  Setup_flag = false;
                  central_menu = true;
                  /*  update_Screen = true ;
                    Moto_Run =  true ;*/
                  break ;

                }
              }
            }
          }
        }
      }
    }
  }
}



///////////////////////////////////////////////////
void CASE_menu() {
  switch (menu) {

    case 1:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1.TEMP_T1");
      lcd.setCursor(9, 0);
      lcd.print("     ");
      if (EEPROM.get(e_therm_T1, therm_T1) >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(EEPROM.get(e_therm_T1, therm_T1));
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(EEPROM.get(e_therm_T1, therm_T1));
      }
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 2:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2.TEMP_T2");
      lcd.setCursor(9, 0);
      lcd.print("     ");
      if (therm_T2 >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(therm_T2);
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(therm_T2);
      }
      lcd.setCursor(4, 1);
      lcd.print("STEP-1: ");
      lcd.setCursor(12, 1);
      lcd.print(EEPROM.get(e_proti_D, proti_D));
      lcd.setCursor(17, 1);
      lcd.print("   ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 3:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("3.TEMP_T3"  );
      lcd.setCursor(9, 0);
      lcd.print("     ");
      if (therm_T3 >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(therm_T3);
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(therm_T3);
      }
      lcd.setCursor(4, 1);
      lcd.print("STEP-2: ");
      lcd.setCursor(12, 1);
      lcd.print(EEPROM.get(e_deuteri_D, deuteri_D));
      lcd.setCursor(17, 1);
      lcd.print("   ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 4:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("4.TEMP_T4");
      lcd.setCursor(9, 0);
      lcd.print("     ");
      if (therm_T4 >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(therm_T4);
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(therm_T4);
      }
      lcd.setCursor(4, 1);
      lcd.print("STEP-3: ");
      lcd.setCursor(12, 1);
      lcd.print(EEPROM.get(e_triti_D, triti_D));
      lcd.setCursor(17, 1);
      lcd.print("   ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 5:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("5.COOL        ");
      if (EEPROM.get(e_COOL, COOL) >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(EEPROM.get(e_COOL, COOL));
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(EEPROM.get(e_COOL, COOL));
      }
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 6:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("6.HEAT        ");
      if (EEPROM.get(e_HEAT, HEAT) >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(EEPROM.get(e_HEAT, HEAT));
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(EEPROM.get(e_HEAT, HEAT));
      }
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 7:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("7.ALARM LOW   ");
      if (EEPROM.get(e_alarm_low, alarm_low) >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print( EEPROM.get(e_alarm_low, alarm_low));
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print( EEPROM.get(e_alarm_low, alarm_low));
      }
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 8:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("8.ALARM HIGH  "  );
      if (EEPROM.get(e_alarm_high, alarm_high) >= 0) {
        lcd.setCursor(14, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print( EEPROM.get(e_alarm_high, alarm_high));
      }
      else  {
        lcd.setCursor(14, 0);
        lcd.print(EEPROM.get(e_alarm_high, alarm_high));
      }
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 9:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("9.MODE         ");
      lcd.setCursor(15, 0);
      lcd.print(EEPROM.get(e_mode, mode));
      lcd.setCursor(16, 0);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 10:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("10.TELEPHONE-1      ");
      lcd.setCursor(0, 1);
      lcd.print("  " );
      /* lcd.setCursor(3, 1);
        lcd.print(TEL_1);*/
      for (byte b_1 = 0 ; b_1 < 13 ; b_1++) { //13 is the maximum lenght of an IP adress with dots
        char p1 = EEPROM.read(e_TEL_1 + b_1);
        lcd.setCursor((3 + b_1), 1);
        lcd.print(p1);
      }
      lcd.setCursor(16, 1);
      lcd.print("    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 11:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("11.TELEPHONE-2      ");
      lcd.setCursor(0, 1);
      lcd.print("  ");
      /* lcd.setCursor(3, 1);
        lcd.print(TEL_2);*/
      for (byte b_2 = 0 ; b_2 < 13 ; b_2++) { //13 is the maximum lenght of an IP adress with dots
        char p2 = EEPROM.read(e_TEL_2 + b_2);
        lcd.setCursor((3 + b_2), 1);
        lcd.print(p2);
      }

      lcd.setCursor(16, 1);
      lcd.print("    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 12:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("12.TELEPHONE-3      ");
      lcd.setCursor(0, 1);
      lcd.print("  " );
      /* lcd.setCursor(3, 1);
        lcd.print(TEL_3);*/
      for (byte b_3 = 0 ; b_3 < 13 ; b_3++) { //13 is the maximum lenght of an IP adress with dots
        char p3 = EEPROM.read(e_TEL_3 + b_3);
        lcd.setCursor((3 + b_3), 1);
        lcd.print(p3);

      }

      lcd.setCursor(16, 1);
      lcd.print("    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 13:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("13.bell-number   ");
      if (EEPROM.get(e_bell, bell) <= 9) {
        lcd.setCursor(17, 0);
        lcd.print(" ");
        lcd.setCursor(18, 0);
        lcd.print(EEPROM.get(e_bell, bell));
      }
      else {
        lcd.setCursor(17, 0);
        lcd.print(EEPROM.get(e_bell, bell));
      }
      lcd.setCursor(19, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 14:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("14:RELAY with TIMER ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 15:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("15: TEST RELAY      ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 16:
      lcd.setCursor(0, 0);
      lcd.print("16:   REMOVE PIN    ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("      ");
      lcd.setCursor(18, 3);
      lcd.print("OK");
      break;

    case 17:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("0:       MENU       ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("EXIT" );
      lcd.setCursor(4, 3);
      lcd.print("   ");
      lcd.setCursor(7, 3);
      lcd.write(3);
      lcd.setCursor(8, 3);
      lcd.print("    ");
      lcd.setCursor(12, 3);
      lcd.write(4);
      lcd.setCursor(13, 3);
      lcd.print("       ");
      break;
  }
}

///////////////////////////////////////////////////

void updateScreen() {
  //εκκηνηση θερμοστατη
  sensors.requestTemperatures ();
  therm_1 = (sensors.getTempCByIndex(0));
  int smartPhone_Connect = RemoteXY_isConnected();

  lcd.setCursor(0, 0);
  if (smartPhone_Connect == 1) {
    lcd.print("@");
  }
  else {
    lcd.print(" ");
  }
  lcd.setCursor(1, 0);
  lcd.print("     ");
  lcd.setCursor(6, 0);
  lcd.print(therm_1);
  lcd.setCursor(11, 0);
  lcd.print(" ");
  lcd.setCursor(12, 0);
  lcd.print("'");
  lcd.setCursor(13, 0);
  lcd.print("C     ");
  if (b_Signal_Sim800l && b_Ber_Sim800l) {
    lcd.setCursor(19, 0);
    lcd.print("Y");
  }
  else  {
    lcd.setCursor(19, 0);
    lcd.print(" ");
  }
  lcd.setCursor(2, 1);
  lcd.print("   ");
  lcd.setCursor(15, 1);
  lcd.print("  ");
  if (b_gsm_sim) {
    lcd.setCursor(17, 1);
    lcd.print("Gsm");
  }
  else  {
    lcd.setCursor(17, 1);
    lcd.print("   ");
  }
  lcd.setCursor(0, 3);
  lcd.print("      ");
  lcd.setCursor(7, 3);
  lcd.print("1");
  lcd.setCursor(9, 3);
  lcd.print("  ");
  lcd.setCursor(12, 3);
  lcd.print("2");
  lcd.setCursor(14, 3);
  lcd.print("  MENU");

  //ενεργοποιηθηκε το TIMER
  if (timerONOFF == 1) {
    if (timerRelay == 1) {
      lcd.setCursor(0, 1);
      lcd.print("T1");
    }
    else if (timerRelay == 2) {
      lcd.setCursor(0, 1);
      lcd.print("T2");
    }
    else if (timerRelay == 3) {
      lcd.setCursor(0, 1);
      lcd.print("T3");
    }
    else if (timerRelay == 4) {
      lcd.setCursor(0, 1);
      lcd.print("T4");
    }
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("  ");
  }

  // ενεργοποιηθηκε η επαφη απο ρελε ισοσταθμησης ρευματος
  if ( power_state == LOW ) {
    lcd.setCursor(18, 2);
    lcd.write(6);
    lcd.setCursor(19, 2);
    lcd.write(5);
    RemoteXY.led_power_r = 255 ;
  }
  else {
    lcd.setCursor(18, 2);
    lcd.print("  ");
    RemoteXY.led_power_r = 0 ;
  }
  //δεν εχει ρευμα δικτυου η συσκευη
  if (onlyBattery == LOW) {
    lcd.setCursor(16, 2);
    lcd.write(0);
    lcd.setCursor(17, 2);
    lcd.print(" ");
    RemoteXY.onlyBattery_led_r = 255;
  }
  else {
    lcd.setCursor(16, 2);
    lcd.print("  ");
    RemoteXY.onlyBattery_led_r = 0;
  }
  // kindinos xamili thermokrasia
  if (tiktak_alarm_LOW == 1) {
    lcd.setCursor(10, 2);
    lcd.write(6);
    lcd.setCursor(11, 2);
    lcd.print("L");
    RemoteXY.led_1_r = 255;
  }
  else {
    lcd.setCursor(10, 2);
    lcd.print("  ");
    RemoteXY.led_1_r = 0;
  }
  // kindinos ypsili thermokrasia
  if (tiktak_alarm_HIGH == 1) {
    lcd.setCursor(12, 2);
    lcd.write(6);
    lcd.setCursor(13, 2);
    lcd.print("H");
    RemoteXY.led_2_r = 255;
  }
  else {
    lcd.setCursor(12, 2);
    lcd.print("  ");
    RemoteXY.led_2_r = 0;
  }

  //ενδειξη οταν εχουμε ενδειξη φωτιας
  if (fire_state == 0) {
    lcd.setCursor(5, 1);
    lcd.print("!! FIRE !!");
  }
  else if (fire_state == 1) {
    lcd.setCursor(5, 1);
    lcd.print("          ");
  }
}

//////////////////////////////////////////////////////

void motoboot() {

  /////////////////////////////////////////////////

  //////λειτουργια TIMER
  if (timerONOFF == 1 && tiktak == 0) {
    if (startsTimer) {
      digitalWrite(tax_01, HIGH);//κλεινω τα ρελε και τα led της εφαρμογης
      digitalWrite(tax_02, HIGH);//για να μην μεινη καποιο ανοιχτο πχ απο επαναφορα
      digitalWrite(tax_03, HIGH);//απο το προγραμμα θερμοκρασιων και να λειτουργειση
      digitalWrite(tax_04, HIGH);// κανονικα το προγραμμα ρελε με χρονομετρο
      RemoteXY.led_4_g = 0;
      RemoteXY.led_5_g = 0;
      RemoteXY.led_6_g = 0;
      RemoteXY.led_7_g = 0;
      previousTimerMillis = millis();//βαζω το millis() στο previousTimerMillis και με την διαφορα τους περνω το χρονο ON OFF
      startsTimer = false;
    }

    lcd.setCursor(0, 2);
    lcd.print("____");
    //ξεκιναμε με OFF και μετα με ON
    if (flashTimerRelay == 1) {
      if (millis() - previousTimerMillis >= longTimerTimeOFF) {
        flashTimerRelay = 0;
        previousTimerMillis = millis();
        TIMER();//λειτουργια ρελε με χρονομετρο
      }
    }
    else  {
      if (millis() - previousTimerMillis >= longTimerTimeON) {
        flashTimerRelay = 1;
        previousTimerMillis = millis();
        TIMER();//λειτουργια ρελε με χρονομετρο
      }
    }
  }
  ///////λειτουργια χωρις TIMER
  else if (timerONOFF == 0 && tiktak == 0) {
    startsTimer = true;
    flashTimerRelay = 1;
    //previousTimerMillis = 0;
    digitalWrite(tax_01, HIGH);
    digitalWrite(tax_02, HIGH);
    digitalWrite(tax_03, HIGH);
    digitalWrite(tax_04, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("____");
    RemoteXY.led_4_g = 0;
    RemoteXY.led_5_g = 0;
    RemoteXY.led_6_g = 0;
    RemoteXY.led_7_g = 0;
  }
  else if (timerONOFF == 0 || timerONOFF == 1 && tiktak > 0) {
    startsTimer = true;
    flashTimerRelay = 1;
    // previousTimerMillis = 0;
  }
  ////////////////////
  switch (EEPROM.get(e_mode, mode)) {
    //ταχυτητες
    case 1:
      switch (tiktak) {
        // 1 taxytita
        case 1:
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          delay(2000);
          digitalWrite(tax_01, LOW);
          lcd.setCursor(0, 2);
          lcd.print("1___");
          RemoteXY.led_4_g = 200;
          RemoteXY.led_5_g = 0;
          RemoteXY.led_6_g = 0;
          RemoteXY.led_7_g = 0;
          break;
        //2 taxytita
        case 2:
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          delay(2000);
          digitalWrite(tax_02, LOW);
          lcd.setCursor(0, 2);
          lcd.print("_2__");
          RemoteXY.led_4_g = 0;
          RemoteXY.led_5_g = 200;
          RemoteXY.led_6_g = 0;
          RemoteXY.led_7_g = 0;
          break;
        // 3 taxytita
        case 3:
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_04, HIGH);
          delay(2000);
          digitalWrite(tax_03, LOW);
          lcd.setCursor(0, 2);
          lcd.print("__3_");
          RemoteXY.led_4_g = 0;
          RemoteXY.led_5_g = 0;
          RemoteXY.led_6_g = 200;
          RemoteXY.led_7_g = 0;
          break;
        // 4 taxytita
        case 4:
          digitalWrite(tax_01, HIGH);
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          delay(2000);
          digitalWrite(tax_04, LOW);
          lcd.setCursor(0, 2);
          lcd.print("___4");
          RemoteXY.led_4_g = 0;
          RemoteXY.led_5_g = 0;
          RemoteXY.led_6_g = 0;
          RemoteXY.led_7_g = 200;
          break;
      }
      break;
    //ανεμηστηρες
    case 2:
      switch (tiktak) {
        // 1 ανεμηστηρες
        case 1:
          digitalWrite(tax_02, HIGH);
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          delay(2000);
          digitalWrite(tax_01, LOW);
          lcd.setCursor(0, 2);
          lcd.print("1___");
          RemoteXY.led_4_g = 200;
          RemoteXY.led_5_g = 0;
          RemoteXY.led_6_g = 0;
          RemoteXY.led_7_g = 0;
          break;
        //1&2 ανεμηστηρες
        case 2:
          digitalWrite(tax_03, HIGH);
          digitalWrite(tax_04, HIGH);
          delay(2000);
          digitalWrite(tax_01, LOW);
          digitalWrite(tax_02, LOW);
          lcd.setCursor(0, 2);
          lcd.print("12__");
          RemoteXY.led_4_g = 200;
          RemoteXY.led_5_g = 200;
          RemoteXY.led_6_g = 0;
          RemoteXY.led_7_g = 0;
          break;
        //1&2&3 ανεμηστηρες
        case 3:
          digitalWrite(tax_04, HIGH);
          delay(2000);
          digitalWrite(tax_01, LOW);
          digitalWrite(tax_02, LOW);
          digitalWrite(tax_03, LOW);
          lcd.setCursor(0, 2);
          lcd.print("123_");
          RemoteXY.led_4_g = 200;
          RemoteXY.led_5_g = 200;
          RemoteXY.led_6_g = 200;
          RemoteXY.led_7_g = 0;
          break;
        //1&2&3&4 ανεμηστηρες
        case 4:
          delay(2000);
          digitalWrite(tax_01, LOW);
          digitalWrite(tax_02, LOW);
          digitalWrite(tax_03, LOW);
          digitalWrite(tax_04, LOW);
          lcd.setCursor(0, 2);
          lcd.print("1234");
          RemoteXY.led_4_g = 200;
          RemoteXY.led_5_g = 200;
          RemoteXY.led_6_g = 200;
          RemoteXY.led_7_g = 200;
          break;
      }
      break;
  }
  //////////////////
  //οταν πεφτει η θερμοκρασια ενεργοποιω τη ζεστη
  if (tiktak_Heat == 1) {
    digitalWrite(heat, LOW);
    lcd.setCursor(5, 2);
    lcd.print("HT");
    RemoteXY.led_3_r = 200;
    RemoteXY.led_3_g = 200;
  }
  else if (tiktak_Heat == 0) {
    digitalWrite(heat, HIGH);
    lcd.setCursor(5, 2);
    lcd.print("  ");
    RemoteXY.led_3_r = 0;
    RemoteXY.led_3_g = 0;
  }
  //οταν ανεβαινη η θερμοκρασια ενεργοποιω το κρυο
  if (tiktak_Cool == 1) {
    digitalWrite(cool, LOW);
    lcd.setCursor(7, 2);
    lcd.print("CL");
    RemoteXY.led_8_r = 200;
    RemoteXY.led_8_g = 200;
  }
  else if (tiktak_Cool == 0) {
    digitalWrite(cool, HIGH);
    lcd.setCursor(7, 2);
    lcd.print("  ");
    RemoteXY.led_8_r = 0;
    RemoteXY.led_8_g = 0;
  }
}

////////////////////////////////////////////////////////////

void app_control() {

  if (RemoteXY.therm != 0) {
    EEPROM.put(e_therm_T1, RemoteXY.edit_1);
    EEPROM.get(e_therm_T1, therm_T1);
    dtostrf(therm_T1, 4, 2, RemoteXY.text_2);
  }

  if (RemoteXY.diff_1 != 0) {
    if (RemoteXY.edit_2 < temp_diff_min ) {
      RemoteXY.edit_2 = temp_diff_min;
    }
    if (RemoteXY.edit_2 > temp_diff_max ) {
      RemoteXY.edit_2 = temp_diff_max;
    }
    EEPROM.put(e_proti_D, RemoteXY.edit_2);
    EEPROM.get(e_proti_D, proti_D);
    dtostrf(therm_T2, 4, 2, RemoteXY.text_3);
  }

  if (RemoteXY.diff_2 != 0) {
    if (RemoteXY.edit_3 < temp_diff_min ) {
      RemoteXY.edit_3 = temp_diff_min;
    }
    if (RemoteXY.edit_3 > temp_diff_max ) {
      RemoteXY.edit_3 = temp_diff_max;
    }
    EEPROM.put(e_deuteri_D, RemoteXY.edit_3);
    EEPROM.get(e_deuteri_D, deuteri_D);
    dtostrf(therm_T3, 4, 2, RemoteXY.text_4);
  }

  if (RemoteXY.diff_3 != 0) {
    if (RemoteXY.edit_4 < temp_diff_min ) {
      RemoteXY.edit_4 = temp_diff_min;
    }
    if (RemoteXY.edit_4 > temp_diff_max ) {
      RemoteXY.edit_4 = temp_diff_max;
    }
    EEPROM.put(e_triti_D, RemoteXY.edit_4);
    EEPROM.get(e_triti_D, triti_D);
    dtostrf(therm_T4, 4, 2, RemoteXY.text_5);
  }

  if (RemoteXY.cool != 0) {
    EEPROM.put(e_COOL, RemoteXY.edit_5);
    EEPROM.get(e_COOL, COOL);
    dtostrf(COOL, 4, 2, RemoteXY.text_6);
  }

  if (RemoteXY.heat != 0) {
    EEPROM.put(e_HEAT, RemoteXY.edit_6);
    EEPROM.get(e_HEAT,  HEAT);
    dtostrf(HEAT, 4, 2, RemoteXY.text_7);
  }

  if (RemoteXY.a_L != 0) {
    EEPROM.put(e_alarm_low, RemoteXY.edit_8);
    EEPROM.get(e_alarm_low, alarm_low);
    dtostrf(alarm_low, 4, 2, RemoteXY.text_9);
  }

  if (RemoteXY.a_H != 0) {
    EEPROM.put(e_alarm_high, RemoteXY.edit_7);
    EEPROM.get(e_alarm_high, alarm_high);
    dtostrf(alarm_high, 4, 2, RemoteXY.text_8);
  }

  //μνημη αριθμου κλησεων
  if (RemoteXY.button_2 != 0) {

    if (RemoteXY.bell_edit < bell_min) {
      RemoteXY.bell_edit = bell_min;
    }
    if (RemoteXY.bell_edit > bell_max) {
      RemoteXY.bell_edit = bell_max;
    }
    EEPROM.put(e_bell, RemoteXY.bell_edit);
    EEPROM.get(e_bell, bell);
    itoa(bell, RemoteXY.bell_text, 10);
  }
  //μνημη τηλεφωνηκων νουμερων
  if (RemoteXY.button_3 != 0) {
    TEL_1 = "";
    String tel_1 = RemoteXY.tel_1_edit ;
    for (int i_1 = 0 ; i_1 < tel_1.length() ; i_1++)
    {
      EEPROM.write( e_TEL_1 + i_1, tel_1[i_1] );
    }
    tel_1 = "";
    for (byte b_1 = 0 ; b_1 < 13 ; b_1++) { //13 is the maximum lenght of an IP adress with dots
      char f_1 = EEPROM.read(e_TEL_1 + b_1);
      TEL_1 += (f_1);
    }
  }

  if (RemoteXY.button_4 != 0) {
    TEL_2 = "";
    String tel_2 = RemoteXY.tel_2_edit ;
    for (int i_2 = 0 ; i_2 < tel_2.length() ; i_2++)
    {
      EEPROM.write( e_TEL_2 + i_2, tel_2[i_2] );
    }
    tel_2 = "";
    for (byte b_2 = 0 ; b_2 < 13 ; b_2++) { //13 is the maximum lenght of an IP adress with dots
      char f_2 = EEPROM.read(e_TEL_2 + b_2);
      TEL_2 += (f_2);
    }
  }

  if (RemoteXY.button_5 != 0) {
    TEL_3 = "";
    String tel_3 = RemoteXY.tel_3_edit ;
    for (int i_3 = 0 ; i_3 < tel_3.length() ; i_3++)
    {
      EEPROM.write( e_TEL_3 + i_3, tel_3[i_3] );
    }
    tel_3 = "";
    for (byte b_3 = 0 ; b_3 < 13 ; b_3++) { //13 is the maximum lenght of an IP adress with dots
      char f_3 = EEPROM.read(e_TEL_3 + b_3);
      TEL_3 += (f_3);
    }
  }

  // μνημη timer relay
  if (RemoteXY.button_1 != 0) {

    if (RemoteXY.edit_9 < 1) {
      RemoteXY.edit_9 = 1;
    }
    if (RemoteXY.edit_9 > 4) {
      RemoteXY.edit_9 = 4;
    }
    EEPROM.put(e_timerRelay, RemoteXY.edit_9);
    EEPROM.get(e_timerRelay, timerRelay);
    itoa(timerRelay, RemoteXY.text_10, 10);
  }
  //μνημη timerON
  if (RemoteXY.button_6 != 0) {

    if (RemoteXY.edit_10 < 0) {
      RemoteXY.edit_10 = 0;
    }
    if (RemoteXY.edit_10 > timerTimeMax) {
      RemoteXY.edit_10 = timerTimeMax;
    }

    EEPROM.put(e_timerON, RemoteXY.edit_10);
    EEPROM.get(e_timerON, timerON);
    itoa(timerON, RemoteXY.text_11, 10);
  }
  //μνημη timerOFF
  if (RemoteXY.button_7 != 0) {

    if (RemoteXY.edit_11 < 0) {
      RemoteXY.edit_11 = 0;
    }
    if (RemoteXY.edit_11 > timerTimeMax) {
      RemoteXY.edit_11 = timerTimeMax;
    }

    EEPROM.put(e_timerOFF, RemoteXY.edit_11);
    EEPROM.get(e_timerOFF, timerOFF);
    itoa(timerOFF, RemoteXY.text_14, 10);
  }


  //διακοπτης ON OFF λειτουργια TIMER
  if (RemoteXY.timerONOFF != 0) {
    if (RemoteXY.button_mem_time != 0) {
      timerONOFF = 1;
      EEPROM.put(e_timerONOFF, timerONOFF);
      EEPROM.get(e_timerONOFF, timerONOFF);
    }
  }
  else  {
    if (RemoteXY.button_mem_time != 0) {
      timerONOFF = 0;
      EEPROM.put(e_timerONOFF, timerONOFF);
      EEPROM.get(e_timerONOFF, timerONOFF);
    }
  }
}
///////////////////////////////////////////////////////
void gsm_tel_1() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("ATD+ " + TEL_1 + ";");
  }
}
//////////////////////////////////////////////////////////
void  gsm_sms_1() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("TEMP.:" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
////////////////////////////////////////////////////////
void gsm_sms_power_1() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("POWER OFF  :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
////////////////////////////////////////////////////////
void gsm_sms_fire_1() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("FIRE  :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////
void gsm_tel_2() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("ATD+ " + TEL_2 + ";");
  }
}
//////////////////////////////////////////////////////////////
void  gsm_sms_2() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("TEMP.:" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
////////////////////////////////////////////
void gsm_sms_power_2() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("POWER OFF  :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////////
void gsm_sms_fire_2() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("FIRE  :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////////
void gsm_tel_3() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("ATD+ " + TEL_3 + ";");
  }
}
//////////////////////////////////////////////////////////
void  gsm_sms_3() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("TEMP.:" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
//////////////////////////////////////////////////////////
void gsm_sms_power_3() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("POWER OFF  :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////////
void gsm_sms_fire_3() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("FIRE  :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
/////////////////////////////////////////////////////////
void gsm_sms_ok_1_temp() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("TEMP.  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
/////////////////////////////////////////////////////////
void gsm_sms_ok_1_power() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("POWER  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
/////////////////////////////////////////////////////////
void gsm_sms_ok_1_fire() {
  if (TEL_1 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("FIRE  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
//////////////////////////////////////////////////////////
void gsm_sms_ok_2_temp() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("TEMP.  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
//////////////////////////////////////////////////////////
void gsm_sms_ok_2_power() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("POWER  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
//////////////////////////////////////////////////////////
void gsm_sms_ok_2_fire() {
  if (TEL_2 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("FIRE  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////////
void gsm_sms_ok_3_temp() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("TEMP.  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////////
void gsm_sms_ok_3_power() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("POWER  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
///////////////////////////////////////////////////////
void gsm_sms_ok_3_fire() {
  if (TEL_3 != TEL_adiaforo) {
    delay(delay_GSM);
    Serial1.println("AT+CMGS=\"" + TEL_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    delay(delay_GSM);
    Serial1.println("FIRE  OK :" + String(therm_1) + " *C");
    delay(delay_GSM);
    Serial1.write(26);
  }
}
/////////////////////////////////////////////////////////
void voidfire() {

  digitalWrite(tax_01, HIGH);
  digitalWrite(tax_02, HIGH);
  digitalWrite(tax_03, HIGH);
  digitalWrite(tax_04, HIGH);
  lcd.setCursor(0, 2);
  lcd.print("____");
  RemoteXY.led_4_g = 0;
  RemoteXY.led_5_g = 0;
  RemoteXY.led_6_g = 0;
  RemoteXY.led_7_g = 0;
  digitalWrite(cool, HIGH);
  lcd.setCursor(7, 2);
  lcd.print("  ");
  RemoteXY.led_8_r = 0;
  RemoteXY.led_8_g = 0;
  digitalWrite(heat, HIGH);
  lcd.setCursor(5, 2);
  lcd.print("  ");
  RemoteXY.led_3_r = 0;
  RemoteXY.led_3_g = 0;
}
///////////////////////////////
void TikTak() {
  //για ταχυτητες
  if (therm_1 <= (therm_T1 - tiktak_diafora)) {
    tiktak = 0;
  }
  else if ((therm_1 >= therm_T1) && (therm_1 <= therm_T2 - tiktak_diafora)) {
    tiktak = 1;
  }
  else if ((therm_1 >= therm_T2) && (therm_1 <= therm_T3 - tiktak_diafora)) {
    tiktak = 2;
  }
  else if ((therm_1 >= therm_T3) && (therm_1 <= therm_T4 - tiktak_diafora)) {
    tiktak = 3;
  }
  else if (therm_1 >= therm_T4 ) {
    tiktak = 4;
  }
  //για θερμανση
  if (therm_1 <= HEAT ) {
    tiktak_Heat = 1;
  }
  else if (therm_1 >= (HEAT + tiktak_diafora)) {
    tiktak_Heat = 0;
  }
  //για ψυξη
  if (therm_1 >= COOL) {
    tiktak_Cool = 1;
  }
  else if (therm_1 <= (COOL - tiktak_diafora)) {
    tiktak_Cool = 0;
  }
}
/////////////////////////////////////////
void TikTak_ALARM() {
  //συναγερμος χαμηλης θερμοκρασιας
  if (therm_1 <= alarm_low ) {
    tiktak_alarm_LOW = 1;
  }
  else if (therm_1 >= (alarm_low + tiktak_diafora_temp)) {
    tiktak_alarm_LOW = 0;
  }
  //συναγερμος υψηλης θερμοκρασιας
  if (therm_1 >= alarm_high) {
    tiktak_alarm_HIGH = 1;
  }
  else if (therm_1 <= (alarm_high - tiktak_diafora_temp)) {
    tiktak_alarm_HIGH = 0;
  }
}
////////////////////////////////////////
void TikTak_setup() {
  if (therm_1 < therm_T1) {
    tiktak = 0;
  }
  else if ((therm_1 >= therm_T1) && (therm_1 < therm_T2)) {
    tiktak = 1;
  }
  else if ((therm_1 >= therm_T2) && (therm_1 < therm_T3)) {
    tiktak = 2;
  }
  else if ((therm_1 >= therm_T3) && (therm_1 < therm_T4)) {
    tiktak = 3;
  }
  else if (therm_1 >= therm_T4 ) {
    tiktak = 4;
  }
  //για θερμανση
  if (therm_1 <= HEAT ) {
    tiktak_Heat = 1;
  }
  else if (therm_1 > (HEAT)) {
    tiktak_Heat = 0;
  }
  //για ψυξη
  if (therm_1 >= COOL) {
    tiktak_Cool = 1;
  }
  else if (therm_1 < (COOL)) {
    tiktak_Cool = 0;
  }
}
///////////////////////////////////////////
void TikTak_ALARM_setup() {
  //συναγερμος χαμηλης θερμοκρασιας
  if (therm_1 <= alarm_low ) {
    tiktak_alarm_LOW = 1;
  }
  else if (therm_1 > (alarm_low)) {
    tiktak_alarm_LOW = 0;
  }
  //συναγερμος υψηλης θερμοκρασιας
  if (therm_1 >= alarm_high) {
    tiktak_alarm_HIGH = 1;
  }
  else if (therm_1 < (alarm_high)) {
    tiktak_alarm_HIGH = 0;
  }
}

/////////////////////////////////////////
void buttonVooidMenu() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  delay(DelayMenu) ;

  if (buttonState1 == LOW || buttonState2 == LOW || buttonState3 == LOW || buttonState4 == LOW) {
    startMillis = millis();  //save the start time
  }
}
////////////////////////////////////
void relay_on1() {
  delay(delay_GSM);
  Serial1.println("AT+CMGS=\"" + number_TEL + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(delay_GSM);
  Serial1.print("EX.1 : ON");
  delay(delay_GSM);
  Serial1.write(26);
}
//////////////////////////////////
void relay_off1() {
  delay(delay_GSM);
  Serial1.println("AT+CMGS=\"" + number_TEL + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(delay_GSM);
  Serial1.print("EX.1 : OFF");
  delay(delay_GSM);
  Serial1.write(26);
}
///////////////////////////////
void relay_on2() {
  delay(delay_GSM);
  Serial1.println("AT+CMGS=\"" + number_TEL + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(delay_GSM);
  Serial1.print("EX.2 : ON");
  delay(delay_GSM);
  Serial1.write(26);
}
///////////////////////////////////
void relay_off2() {
  delay(delay_GSM);
  Serial1.println("AT+CMGS=\"" + number_TEL + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(delay_GSM);
  Serial1.print("EX.2 : OFF");
  delay(delay_GSM);
  Serial1.write(26);
}
////////////////////////////////////
void temperature_status() {
  delay(delay_GSM);
  Serial1.println("AT+CMGS=\"" + number_TEL + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(delay_GSM);
  Serial1.print("TEMP.:" + String(therm_1) + " *C");
  delay(delay_GSM);
  Serial1.write(26);
}
//////////////////////////////////
void ex_Void_button() {
  // εντολες για εξωτερικα relay EX1 EX2
  if (buttonState2 == LOW) {
    ++ex1;
    if (ex1 > 3) {
      ex1 = 0;
    }
    if ( ex1 <= 1 ) {
      booex1 = 1;
      RemoteXY.ex_1 = 1;
      RemoteXY_sendInputVariables();
      MEMORYex1();
      Serial.println(booex1);
    }
    else if (ex1 > 1 && ex1 <= 3) {
      booex1 = 0;
      RemoteXY.ex_1 = 0;
      RemoteXY_sendInputVariables();
      MEMORYex1();
      Serial.println(booex1);
    }
  }
  if (buttonState3 == LOW) {
    ++ex2;
    if (ex2 > 3) {
      ex2 = 0;
    }
    if ( ex2 <= 1 ) {
      booex2 = 1;
      RemoteXY.ex_2 = 1;
      RemoteXY_sendInputVariables();
      MEMORYex2();
      Serial.println(booex2);
    }
    else if (ex2 > 1 && ex2 <= 3) {
      booex2 = 0;
      RemoteXY.ex_2 = 0;
      RemoteXY_sendInputVariables();
      MEMORYex2();
      Serial.println(booex2);
    }
  }
}
//////////////////////////////////
void ex_Void_app() {

  //εξωτερηκα relay
  if (RemoteXY.ex_1 != 0) {
    booex1 = 1;
    MEMORYex1();
  }
  else {
    booex1 = 0;
    MEMORYex1();
  }
  if (RemoteXY.ex_2 != 0) {
    booex2 = 1;
    MEMORYex2();
  }
  else {
    booex2 = 0;
    MEMORYex2();
  }
}
//////////////////////////////////
void MEMORYex1() {

  if (booex1 == 1 && memEX1) {
    EEPROM.put(e_booex1, booex1);
    memEX1 = false;
  }
  else if (booex1 == 0 && !memEX1) {
    EEPROM.put(e_booex1, booex1);
    memEX1 = true;
  }
}
/////////////////////////////////
void MEMORYex2() {

  if (booex2 == 1 && memEX2) {
    EEPROM.put(e_booex2, booex2);
    memEX2 = false;
  }
  else if (booex2 == 0 && !memEX2) {
    EEPROM.put(e_booex2, booex2);
    memEX2 = true;
  }
}
//////////////////////////////////
void EX_screen_relay() {
  if (booex1 == 1) {

    if (update_Screen) {
      lcd.setCursor(6, 3);
      lcd.print(" ");
      lcd.setCursor(8, 3);
      lcd.write(5);
    }
    digitalWrite(ex_1 , LOW);
  }
  else if (booex1 == 0) {

    if (update_Screen) {
      lcd.setCursor(6, 3);
      lcd.print(" ");
      lcd.setCursor(8, 3);
      lcd.print(" ");
    }
    digitalWrite(ex_1 , HIGH);
  }
  if (booex2 == 1) {

    if (update_Screen) {
      lcd.setCursor(11, 3);
      lcd.print(" ");
      lcd.setCursor(13, 3);
      lcd.write(5);
    }
    digitalWrite(ex_2 , LOW);
  }
  else if (booex2 == 0) {

    if (update_Screen) {
      lcd.setCursor(11, 3);
      lcd.print(" ");
      lcd.setCursor(13, 3);
      lcd.print(" ");
    }
    digitalWrite(ex_2 , HIGH);
  }
}
/////////////////////////////////
void start_loop_EX() {

  if ( start_EX) {
    if (EEPROM.get(e_booex1, booex1) == 1) {
      RemoteXY.ex_1 = 1;
      RemoteXY_sendInputVariables();
    }
    else if (EEPROM.get(e_booex1, booex1) == 0) {
      RemoteXY.ex_1 = 0;
      RemoteXY_sendInputVariables();
    }
    if (EEPROM.get(e_booex2, booex2) == 1) {
      RemoteXY.ex_2 = 1;
      RemoteXY_sendInputVariables();
    }
    else if (EEPROM.get(e_booex2, booex2) == 0) {
      RemoteXY.ex_2 = 0;
      RemoteXY_sendInputVariables();
    }
    start_EX = false;
  }
}
////////////////////////////////
void incall_TEL_DTMF() {
  if (count_Ring >= 3) {
    if (symbol == "1") {
      startMillisTELincall = millis();
      if (booex1 == 1) {
        booex1 = 0;
        RemoteXY.ex_1 = 0;
        RemoteXY_sendInputVariables();
        relay_off1(); //αποστολη μηνηματος μετα απο ενεργοποιηση ρελε μεσω κλησης
        symbol = "";
      }
      else if ( booex1 == 0) {
        booex1 = 1;
        RemoteXY.ex_1 = 1;
        RemoteXY_sendInputVariables();
        relay_on1(); //αποστολη μηνηματος μετα απο ενεργοποιηση ρελε μεσω κλησης
        symbol = "";
      }
    }
    else if (symbol == "2") {
      startMillisTELincall = millis();
      if (booex2 == 1) {
        booex2 = 0;
        RemoteXY.ex_2 = 0;
        RemoteXY_sendInputVariables();
        relay_off2(); //αποστολη μηνηματος μετα απο ενεργοποιηση ρελε μεσω κλησης
        symbol = "";
      }
      else if ( booex2 == 0) {
        booex2 = 1;
        RemoteXY.ex_2 = 1;
        RemoteXY_sendInputVariables();
        relay_on2(); //αποστολη μηνηματος μετα απο ενεργοποιηση ρελε μεσω κλησης
        symbol = "";
      }
    }
    else if (symbol == "3") {
      startMillisTELincall = millis();
      temperature_status(); //αποστολη μηνηματος αποστολης θερμοκρασιας
      symbol = "";
    }
  }
}
///////////////////////////////////////////////////
void TIMER() {//λειτουργια ρελε με χρονομετρο
  if (timerRelay == 1) {
    digitalWrite(tax_01, flashTimerRelay);
    digitalWrite(tax_02, HIGH);
    digitalWrite(tax_03, HIGH);
    digitalWrite(tax_04, HIGH);
    RemoteXY.led_4_g = 0;
    RemoteXY.led_5_g = 0;
    RemoteXY.led_6_g = 0;
    RemoteXY.led_7_g = 0;
  }
  else if (timerRelay == 2) {
    digitalWrite(tax_02, flashTimerRelay);
    digitalWrite(tax_01, HIGH);
    digitalWrite(tax_03, HIGH);
    digitalWrite(tax_04, HIGH);
    RemoteXY.led_4_g = 0;
    RemoteXY.led_5_g = 0;
    RemoteXY.led_6_g = 0;
    RemoteXY.led_7_g = 0;
  }
  else if (timerRelay == 3) {
    digitalWrite(tax_03, flashTimerRelay);
    digitalWrite(tax_01, HIGH);
    digitalWrite(tax_02, HIGH);
    digitalWrite(tax_04, HIGH);
    RemoteXY.led_4_g = 0;
    RemoteXY.led_5_g = 0;
    RemoteXY.led_6_g = 0;
    RemoteXY.led_7_g = 0;
  }
  else if (timerRelay == 4) {
    digitalWrite(tax_04, flashTimerRelay);
    digitalWrite(tax_01, HIGH);
    digitalWrite(tax_02, HIGH);
    digitalWrite(tax_03, HIGH);
    RemoteXY.led_4_g = 0;
    RemoteXY.led_5_g = 0;
    RemoteXY.led_6_g = 0;
    RemoteXY.led_7_g = 0;
  }
}

///////////////////////////////////////////////////
void maxatos() {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("MAXATOS");
  lcd.setCursor(4, 2);
  lcd.print("electronics");
  lcd.setCursor(1, 3);
  lcd.print("MP-01     vers. 3.5");
}
