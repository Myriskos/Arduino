
//βιβλιοθηκη για αποθηκευση στην EEPROM
#include <EEPROM.h>

//βιβλιοθηκη για OLED
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L (Rx,Tx  > Tx,Rx)is connected to Arduino #3 & #2

// δηλωση οθονης
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// δηλωση επαφων ρελε
const int   Relay_1 = 6 ;
const int   Relay_2 = 7 ;

// δηλωση επαφων ρελε led
const int   led_1 = 8 ;
const int   led_2 = 9 ;

// δηλωση επαφης βλαβης
const int damage_pin = 4;
// δηλωση επαφης  γεματη δεξαμενη
const int full_pin = 5;
// δηλωση επαφης  onlyBattery
const int onlyBattery_pin = A0;
// δηλωση επαφης  noPower
const int noPower_pin = A1;

// κατασταση των ρελε ON η OFF
byte   conditionA ;
byte   conditionB ;
//ποιο τηλεφωνο επικινωνησε τελευταια φορα
byte who_tel_A = 0;
byte who_tel_B = 0;

int damage;
int full;
int onlyBattery;
int noPower;
//delay αναβοσβημα led σε βλαβη
int damageflash = 0;
unsigned long currentMillis;
unsigned long previousMillis = 0;
const long interval = 500;

String mySerial_data = "" ;
String Relay_1_State = "" ;
String Relay_2_State = "" ;
String TEL_1 = "" ;
String TEL_2 = "" ;
String TEL_3 = "" ;
String telA = "" ; //τηλεφωνικος αριθμος
String telB = "" ; //τηλεφωνικος αριθμος
String tel_1 = "" ;
String tel_2 = "" ;
String tel_3 = "" ;
String CellNumtemp = "" ;
uint8_t damage_count = 0;
byte power_count = 0;
byte power_count_sms_ok = 0;
byte count = 0;
byte count_damage = 0;
byte count_power = 0;
//μεταβλητες για καθηστερηση συναγερμου διακοπης
unsigned long startMillisPOWER;   //χρονος εκκηνησης
const unsigned long periodPOWER = 10000;  //
bool diakopi = false;
int delay_GSM = 500; //χρονοκαθηστερηση αναμεσα στης εντολες sim800l
int nump_flagTEL = 6;//αριθμος κλησεων σε προβλημα
int flagTEL = nump_flagTEL;//αριθμος κλησεων σε προβλημα διακοπης
int flagTEL_Damage = nump_flagTEL; //αριθμος κλησεων σε προβλημα βλαβης
unsigned long startMillisTEL;   //χρονος εκκηνησης
const unsigned long periodTEL = 30000;  //χρονος αναπαντητης
bool booATD_Damage = true; //οταν κανη κληση τηλεφωνου σε βλαβη
bool booATD = true;//οταν κανη κληση τηλεφωνου σε διακοπη
String symbol_data = "";
String symbol = "";
String error_data = "";//εαν βγει ERROR στη σειριακη
String NoCarrier_data = ""; //εαν βγει NO CARRIER στη σειριακη

int count_Ring = 0;
bool b_incall = false;//να περνω το millis για το χρονο κλησης καλουντος
//bool  bool_DTMF = false;//ποτε ισχυουν οι εντολες DTMF
String number_data = "";
String number = "";//το τηλ.νουμερο του καλουντος απο αναγνωριση κλησης χωρις το προθεμα της χωρας (π.χ.+30)
//String number_30 = "";//το τηλ.νουμερο του καλουντος απο αναγνωριση κλησης με το προθεμα της χωρας
String number_TEL = "";//τοποθετουμαι το αποθηκευμενο τηλ.νουμερο για αποστολη μηνηματος ενεργοποιησης η απενεργοποιησης EX1 EX2
String number_TEL_1 = "";//το αποθηκευμενο τηλ.νουμερο χωρις
String number_TEL_2 = "";//το προθεμα της χωρας (π.χ.+30)
String number_TEL_3 = "";//
unsigned long startMillisTELincall;//αυτοματο κλεισημο κλεισης καλουντος
const unsigned long periodTELincall = 40000;
unsigned long startMillisTELincall_RING;//μηδενισμος RING εαν ειναι μικροτερο του 3
const unsigned long periodTELincall_RING = 15000;

int length_TEL_1;//αριθμος ψηφιων τηλεφωνικων νουμερων για παρουμε καινα
int length_TEL_2;//βαλουμε στην μνημη
int length_TEL_3;

int e_TEL_1 = 0;//διευθηνση μνημης τηλεφωνων
int e_TEL_2 = 20;
int e_TEL_3 = 40;
int e_conditionA = 60;//διευθηνση μνημης καταστασης ρελε
int e_conditionB = 61;
int e_who_tel_A = 62;//διευθηνση μνημης ποιο τηλεφωνο επικινωνησε τελευταια φορα
int e_who_tel_B = 63;
int e_length_TEL_1 = 64;//διευθηνση μνημης τηλεφωνων των length_TEL_1
int e_length_TEL_2 = 65; //length_TEL_2,length_TEL_3
int e_length_TEL_3 = 66;

int a = -100;//για ρολαρισμα στη οθονη
int b = 100;
int c = a;



void setup() {
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  u8g2.begin();
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  // χρονοκαθυστέρηση για να βρει δικτυο το sim800l
  delay(15000);


  //οροσμος pin εισοδων βλαβης και γεματη δεξαμενη
  pinMode(damage_pin, INPUT_PULLUP);
  pinMode(full_pin, INPUT_PULLUP);
  //οροσμος pin εισοδων onlyBattery και noPower
  pinMode(onlyBattery_pin, INPUT);
  pinMode(noPower_pin, INPUT_PULLUP);
  //ορισμος pin  εξοδων για ρελε
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);

  //ορισμος pin  εξοδων για  led
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  /* οριζουμε οι εξοδοι να ειναι σε κατασταση HIGH για να ειναι
       απενεργοποιοιμενα τα ρελε κατα την εκκινηση του κωδικα και
       σε καθε επανεκκινηση του arduino,ετσι δουλευουν τα πλακετακια
       των ρελε*/
  digitalWrite(Relay_1, HIGH);
  digitalWrite(Relay_2, HIGH);

  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);

  EEPROM.get(e_length_TEL_1, length_TEL_1);
  EEPROM.get(e_length_TEL_2, length_TEL_2);
  EEPROM.get(e_length_TEL_3, length_TEL_3);

  for (byte b_1 = 0 ; b_1 < length_TEL_1 ; b_1++) { //13 is the maximum lenght of an IP adress with dots
    char f_1 = EEPROM.read(e_TEL_1 + b_1);
    TEL_1 += (f_1);
  }
  for (byte b_2 = 0 ; b_2 < length_TEL_2 ; b_2++) { //13 is the maximum lenght of an IP adress with dots
    char f_2 = EEPROM.read(e_TEL_2 + b_2);
    TEL_2 += (f_2);
  }
  for (byte b_3 = 0 ; b_3 < length_TEL_3 ; b_3++) { //13 is the maximum lenght of an IP adress with dots
    char f_3 = EEPROM.read(e_TEL_3 + b_3);
    TEL_3 += (f_3);
  }

  EEPROM.get(e_conditionA, conditionA);
  EEPROM.get(e_conditionB, conditionB);
  EEPROM.get(e_who_tel_A, who_tel_A);
  EEPROM.get(e_who_tel_B, who_tel_B);

  who_cond_A();
  who_cond_B();
  who_telA();
  who_telB();

  delay(delay_GSM);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  delay(delay_GSM);
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(delay_GSM);
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  delay(delay_GSM);
  mySerial.println("AT+CMGD=1,4");//DELETE all sms
  delay(delay_GSM);
  mySerial.println("AT+DDET=1");//DTMF
  delay(delay_GSM);
  mySerial.println("ATS0=3");//απαντά αυτόματα στην κλήση μετά από 3 κουδούνισμα
  delay(delay_GSM);
  mySerial.println("AT+CLIP=1");//αναγνωριση κλησεων
  delay(delay_GSM);
  Serial.println (conditionA);
  delay(50);
  Serial.println (conditionB);
  delay(50);
  Serial.println (who_tel_A);
  delay(50);
  Serial.println (who_tel_B);
  delay(50);
  Serial.println (TEL_1);
  delay(50);
  Serial.println (TEL_2);
  delay(50);
  Serial.println (TEL_3);
  delay(50);
  Serial.println (telA);
  delay(50);
  Serial.println (telB);
}

void loop() {

  // Serial.println(TEL_1);
  damage = digitalRead(damage_pin);
  full = digitalRead(full_pin);
  onlyBattery = digitalRead(onlyBattery_pin);
  noPower = digitalRead(noPower_pin);
  //τα αποθηκευμενα νουμερα χωρις +30
  number_TEL_1 = TEL_1.substring(3, 13);
  number_TEL_2 = TEL_2.substring(3, 13);
  number_TEL_3 = TEL_3.substring(3, 13);
  delay(10);
  statusCount();
  delay(10);

  //να μηδενηση το count_Ring κ number_TEL εαν κλειση το τηλ πριντις τρεις
  //κλησης καιαπαντηση ,για να ειναι ετοιμο για την επομενη κλεισει
  if (count_Ring > 0 && count_Ring < 3 && !b_incall) {
    if ( millis() - startMillisTELincall_RING > periodTELincall_RING) {
      number_TEL = "";
      count_Ring = 0;
    }
  }

  //να κλειση το τηλ μετα απο 60" εαν δεν σταλει DTMF
  if (( millis() - startMillisTELincall > periodTELincall) && b_incall) {
    delay(delay_GSM);
    mySerial.println("ATH"); //hang up
    b_incall = false;
    number_TEL = "";
    count_Ring = 0;
  }
  a = a + 1;
  b = b - 1;
  c = c + 1;
  if (a > 100) {
    a = -100;
  }
  if (b < -100) {
    b = 100;
  }
    screen();

    if (mySerial.available()) {
      delay(100);

      mySerial_data = mySerial.readString();
      number_data = mySerial_data.substring(mySerial_data.indexOf("+CLIP:"));
      symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
      error_data = mySerial_data.substring(mySerial_data.indexOf("ERROR"));
      NoCarrier_data = mySerial_data.substring(mySerial_data.indexOf("NO CARRIER"));

      Serial.print(mySerial_data);
      delay(10);

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
            mySerial.println("ATH"); //hang up
            b_incall = false;
            number_TEL = "";
            count_Ring = 0;
          }
        }
      }

      if (mySerial_data.indexOf("XCWQ1") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("XCWQ1"), mySerial_data.indexOf("#"));
        tel_1 = CellNumtemp.substring(5);
        length_TEL_1 = tel_1.length() ;
        EEPROM.put(e_length_TEL_1, length_TEL_1);
        for (int i_1 = 0 ; i_1 < length_TEL_1 ; i_1++)
        {
          EEPROM.write( e_TEL_1 + i_1, tel_1[i_1] );
        }
        delay(delay_GSM);
        mySerial.println("AT+CMGS=\"" + tel_1 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
        delay(delay_GSM);
        mySerial.print("OK");
        delay(delay_GSM);
        mySerial.write(26);
        CellNumtemp = "";
        tel_1 = "";
        mySerial_data = "";
      }
      else if  (mySerial_data.indexOf("XCWQ2") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("XCWQ2"), mySerial_data.indexOf("#"));
        tel_2 = CellNumtemp.substring(5);
        length_TEL_2 = tel_2.length() ;
        EEPROM.put(e_length_TEL_2, length_TEL_2);
        for (int i_2 = 0 ; i_2 < length_TEL_2 ; i_2++)
        {
          EEPROM.write( e_TEL_2 + i_2, tel_2[i_2] );
        }
        delay(delay_GSM);
        mySerial.println("AT+CMGS=\"" + tel_2 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
        delay(delay_GSM);
        mySerial.print("OK");
        delay(delay_GSM);
        mySerial.write(26);
        CellNumtemp = "";
        tel_2 = "";
        mySerial_data = "";
      }
      else if  (mySerial_data.indexOf("XCWQ3") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("XCWQ3"), mySerial_data.indexOf("#"));
        tel_3 = CellNumtemp.substring(5);
        length_TEL_3 = tel_3.length() ;
        EEPROM.put(e_length_TEL_3, length_TEL_3);
        for (int i_3 = 0 ; i_3 < length_TEL_3 ; i_3++)
        {
          EEPROM.write( e_TEL_3 + i_3, tel_3[i_3] );
        }
        delay(delay_GSM);
        mySerial.println("AT+CMGS=\"" + tel_3 + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
        delay(delay_GSM);
        mySerial.print("OK");
        delay(delay_GSM);
        mySerial.write(26);
        CellNumtemp = "";
        tel_3 = "";
        mySerial_data = "";
      }

      else if (mySerial_data.indexOf("ON1") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("+3"));
        telA = CellNumtemp.substring(0, 13);
        write_who_tel_A();
        if ( telA == TEL_1 || telA == TEL_2 || telA == TEL_3 ) {
          if (damage == 0 && (noPower == 0 || onlyBattery == 0)) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print(Relay_1_State + "_BLABH ANTLIAS_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else if (damage == 0 ) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print(Relay_1_State + "_BLABH ANTLIAS");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else if (noPower == 0 || onlyBattery == 0) {
            digitalWrite(Relay_1, LOW);
            Relay_1_State = "ON.";
            conditionA = 1 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else  {
            digitalWrite(Relay_1, LOW);
            Relay_1_State = "ON.";
            conditionA = 1 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State);
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
        }
      }

      else if (mySerial_data.indexOf("OFF1") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("+3"));
        telA = CellNumtemp.substring(0, 13);
        write_who_tel_A();
        if ( telA == TEL_1 || telA == TEL_2 || telA == TEL_3) {
          if (damage == 0 && (noPower == 0 || onlyBattery == 0)) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print(Relay_1_State + "_BLABH ANTLIAS_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else if (damage == 0 ) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print(Relay_1_State + "_BLABH ANTLIAS");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else if (noPower == 0 || onlyBattery == 0) {
            digitalWrite(Relay_1, HIGH);
            Relay_1_State = "OFF.";
            conditionA = 0 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else {
            digitalWrite(Relay_1, HIGH);
            Relay_1_State = "OFF.";
            conditionA = 0 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State);
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
        }
      }
      else if (mySerial_data.indexOf("STATUS1") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("+3"));
        telA = CellNumtemp.substring(0, 13);
        write_who_tel_A();
        if ( telA == TEL_1 || telA == TEL_2 || telA == TEL_3) {
          if (damage == 0 && (noPower == 0 || onlyBattery == 0)) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print(Relay_1_State + "_BLABH ANTLIAS_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else if (damage == 0 ) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print(Relay_1_State + "_BLABH ANTLIAS");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else if (noPower == 0 || onlyBattery == 0) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State);
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
        }
      }
      else if (mySerial_data.indexOf("ON2") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("+3"));
        telB = CellNumtemp.substring(0, 13);
        write_who_tel_B();
        if ( telB == TEL_1 || telB == TEL_2 || telB == TEL_3 ) {
          if (noPower == 0 || onlyBattery == 0) {
            digitalWrite(Relay_2, LOW);
            Relay_2_State = "ON-2";
            conditionB = 1 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else {
            digitalWrite(Relay_2, LOW);
            Relay_2_State = "ON-2";
            conditionB = 1 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State);
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
        }
      }

      else if (mySerial_data.indexOf("OFF2") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("+3"));
        telB = CellNumtemp.substring(0, 13);
        write_who_tel_B();
        if ( telB == TEL_1 || telB == TEL_2 || telB == TEL_3) {
          if (noPower == 0 || onlyBattery == 0) {
            digitalWrite(Relay_2, HIGH);
            Relay_2_State = "OFF-2";
            conditionB = 0 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else {
            digitalWrite(Relay_2, HIGH);
            Relay_2_State = "OFF-2";
            conditionB = 0 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State);
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
        }
      }

      else if (mySerial_data.indexOf("STATUS2") > -1) {
        CellNumtemp = mySerial_data.substring(mySerial_data.indexOf("+3"));
        telB = CellNumtemp.substring(0, 13);
        write_who_tel_B();
        if ( telB == TEL_1 || telB == TEL_2 || telB == TEL_3) {
          if (noPower == 0 || onlyBattery == 0) {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
          else {
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State);
            delay(delay_GSM);
            mySerial.write(26);
            CellNumtemp = "";
            mySerial_data = "";
          }
        }
      }
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
        mySerial.println("ATH"); //hang up
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
        //incall_TEL_DTMF();
      }

      incall_TEL_DTMF();
    }

    //εντολες για βλαβη απο ρελλε
    while (damage == 0 && damage_count == 0) {
      damage = digitalRead(damage_pin);//να διαβαζει το pin βλαβης
      digitalWrite(Relay_1, HIGH);
      Relay_1_State = "OFF.";
      conditionA = 0;
      EEPROM.update(e_conditionA, conditionA);
      if (flagTEL_Damage > 0) {
        if (booATD_Damage) {
          startMillisTEL = millis();
          delay(delay_GSM);
          mySerial.println("ATD+ " + telA + ";");
          booATD_Damage = false;
          break;
        }
        else if (!booATD_Damage) {
          if (mySerial.available()) {
            mySerial_data = mySerial.readString(); // to hold incomming communication from GSM module
            Serial.println(mySerial_data);
            symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
            symbol = symbol_data.substring(7, 8);

            Serial.println(symbol);
            // delay(100);

            if (symbol == "*" ) {
              delay(delay_GSM);
              mySerial.println("ATH"); //hang up
              flagTEL_Damage = 0;
              mySerial_data = "";
              symbol_data = "";
              booATD_Damage = true;
              symbol = "";
              break;
            }
          }
          if (  millis() - startMillisTEL > periodTEL && !booATD_Damage) {
            delay(delay_GSM);
            mySerial.println("ATH"); //hang up
            flagTEL_Damage--;
            booATD_Damage = true;
            break;
          }
        }
      }
      else if ( flagTEL_Damage == 0 ) {
        delay(delay_GSM);
        mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
        delay(delay_GSM);
        mySerial.print("BLABH ANTLIAS");
        delay(delay_GSM);
        mySerial.write(26);
        damage_count = 1;
        break;
      }
    }
    if (damage == 1) {
      while (!booATD_Damage) {
        delay(delay_GSM);
        mySerial.println("ATH"); //hang up
        booATD_Damage = true;
        break;
      }
      flagTEL_Damage = nump_flagTEL;
      damage_count = 0;
    }

    //εντολες για διακοπη ρευματος
    if (onlyBattery == 1 && noPower == 1) {
      while (!booATD) {
        delay(delay_GSM);
        mySerial.println("ATH"); //hang up
        booATD = true;
        break;
      }
      power_count = 0;
      diakopi = false;
    }

    while ((noPower == 0 || onlyBattery == 0) && !diakopi) {
      startMillisPOWER = millis();
      flagTEL = nump_flagTEL;
      diakopi = true;
      break;
    }

    while ((  millis() - startMillisPOWER > periodPOWER) &&
           (noPower == 0 || onlyBattery == 0) && power_count == 0 ) {

      onlyBattery = digitalRead(onlyBattery_pin);
      noPower = digitalRead(noPower_pin);

      if (flagTEL > 0) {
        if (booATD) {
          startMillisTEL = millis();
          delay(delay_GSM);
          mySerial.println("ATD+ " + telA + ";");
          booATD = false;
          break;
        }
        else if (!booATD) {
          if (mySerial.available()) {
            mySerial_data = mySerial.readString(); // to hold incomming communication from GSM module
            Serial.println(mySerial_data);
            symbol_data = mySerial_data.substring(mySerial_data.indexOf("+DTMF:"));
            symbol = symbol_data.substring(7, 8);

            Serial.println(symbol);
            // delay(100);

            if (symbol == "*" ) {
              delay(delay_GSM);
              mySerial.println("ATH"); //hang up
              flagTEL = 0;
              mySerial_data = "";
              symbol_data = "";
              booATD = true;
              symbol = "";
              break;
            }
          }
          if (  millis() - startMillisTEL > periodTEL) {
            delay(delay_GSM);
            mySerial.println("ATH"); //hang up
            flagTEL--;
            booATD = true;
            break;
          }
        }
      }
      else if ( flagTEL == 0 ) {
        delay(delay_GSM);
        mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
        delay(delay_GSM);
        mySerial.print("DIAKOPI REYMA");
        delay(delay_GSM);
        mySerial.write(26);
        power_count = 1;
        power_count_sms_ok = 1;
        break;
      }
    }

    if (onlyBattery == 1 && noPower == 1 && power_count_sms_ok == 1) {
      delay(delay_GSM);
      mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
      delay(delay_GSM);
      mySerial.print("REYMA OK");
      delay(delay_GSM);
      mySerial.write(26);
      power_count_sms_ok = 0;
    }

    //εντολες απο αισθητηρα δεξαμενης
    if ( full == 0 && conditionA == 1 ) {
      digitalWrite(Relay_1, HIGH);
    }
    else if (full == 1 && conditionA == 1) {
      digitalWrite(Relay_1, LOW);
    }

  }

  //----------------------------------------
  void who_telA() {
    if (who_tel_A == 1) {
      telA = TEL_1;
    }
    else if (who_tel_A == 2) {
      telA = TEL_2;
    }
    else if (who_tel_A == 3) {
      telA = TEL_3;
    }
    else {
      telA = TEL_1;
    }
  }
  //------------------------------------------
  void who_telB() {
    if (who_tel_B == 1) {
      telB = TEL_1;
    }
    else if (who_tel_B == 2) {
      telB = TEL_2;
    }
    else if (who_tel_B == 3) {
      telB = TEL_3;
    }
    else {
      telA = TEL_1;
    }
  }
  //-------------------------------------------
  void write_who_tel_A() {
    if ( telA == TEL_1) {
      who_tel_A = 1;
      EEPROM.update(e_who_tel_A, who_tel_A);
    }
    else if ( telA == TEL_2) {
      who_tel_A = 2;
      EEPROM.update(e_who_tel_A, who_tel_A);
    }
    else if ( telA == TEL_3) {
      who_tel_A = 3;
      EEPROM.update(e_who_tel_A, who_tel_A);
    }
  }
  //-------------------------------------------
  void write_who_tel_B() {
    if ( telB == TEL_1) {
      who_tel_B = 1;
      EEPROM.update(e_who_tel_B, who_tel_B);
    }
    else if ( telB == TEL_2) {
      who_tel_B = 2;
      EEPROM.update(e_who_tel_B, who_tel_B);
    }
    else if ( telB == TEL_3) {
      who_tel_B = 3;
      EEPROM.update(e_who_tel_B, who_tel_B);
    }
  }
  //--------------------------------------------
  void who_cond_A() {
    if (conditionA == 1) {
      digitalWrite(Relay_1, LOW);
      Relay_1_State = "ON.";
    }
    else if (conditionA == 0) {
      digitalWrite(Relay_1, HIGH);
      Relay_1_State = "OFF.";
    }
  }
  //------------------------------------------------
  void who_cond_B() {
    if (conditionB == 1) {
      digitalWrite(Relay_2, LOW);
      Relay_2_State = "ON-2";
    }
    else if (conditionB == 0) {
      digitalWrite(Relay_2, HIGH);
      Relay_2_State = "OFF-2";
    }
  }
  /////////////////////////////////////////////////////////
  void statusCount() {
    if ( damage == 0 ) {
      count_damage = 1;
    }
    else {
      count_damage = 0;
    }
    if (onlyBattery == 0 || noPower == 0) {
      count_power = 1;
    }
    else {
      count_power = 0;
    }
    if (count_damage == 1 && count_power == 1) {
      count = 1;
    }
    else {
      count = 0;
    }
  }
  ///////////////////////
  void  incall_TEL_DTMF() {
    if (count_Ring >= 3) {
      if (symbol == "1") {
        startMillisTELincall = millis();
        telA = number_TEL;
        write_who_tel_A();
        if (damage == 0 && (noPower == 0 || onlyBattery == 0)) {
          delay(delay_GSM);
          mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
          delay(delay_GSM);
          mySerial.print(Relay_1_State + "_BLABH ANTLIAS_&_DIAKOPI REYMA");
          delay(delay_GSM);
          mySerial.write(26);
          symbol = "";
        }
        else if (damage == 0 ) {
          delay(delay_GSM);
          mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
          delay(delay_GSM);
          mySerial.print(Relay_1_State + "_BLABH ANTLIAS");
          delay(delay_GSM);
          mySerial.write(26);
          symbol = "";
        }
        else if (noPower == 0 || onlyBattery == 0) {
          if (conditionA == 0) {
            digitalWrite(Relay_1, LOW);
            Relay_1_State = "ON.";
            conditionA = 1 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
          else if (conditionA == 1) {
            digitalWrite(Relay_1, HIGH);
            Relay_1_State = "OFF.";
            conditionA = 0 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
        }
        else {
          if (conditionA == 0) {
            digitalWrite(Relay_1, LOW);
            Relay_1_State = "ON.";
            conditionA = 1 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State);
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
          else if (conditionA == 1) {
            digitalWrite(Relay_1, HIGH);
            Relay_1_State = "OFF.";
            conditionA = 0 ;
            EEPROM.update(e_conditionA, conditionA);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telA + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("ANTLIA :" + Relay_1_State);
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
        }
      }
      else if (symbol == "2") {
        startMillisTELincall = millis();
        telB = number_TEL;
        write_who_tel_B();
        if (noPower == 0 || onlyBattery == 0) {
          if (conditionB == 0) {
            digitalWrite(Relay_2, LOW);
            Relay_2_State = "ON-2";
            conditionB = 1 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
          else if (conditionB == 1) {
            digitalWrite(Relay_2, HIGH);
            Relay_2_State = "OFF-2";
            conditionB = 0 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State + "_&_DIAKOPI REYMA");
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
        }
        else {
          if (conditionB == 0) {
            digitalWrite(Relay_2, LOW);
            Relay_2_State = "ON-2";
            conditionB = 1 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State);
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
          else if (conditionB == 1) {
            digitalWrite(Relay_2, HIGH);
            Relay_2_State = "OFF-2";
            conditionB = 0 ;
            EEPROM.update(e_conditionB, conditionB);
            delay(delay_GSM);
            mySerial.println("AT+CMGS=\"" + telB + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
            delay(delay_GSM);
            mySerial.print("RELAY_2 is :" + Relay_2_State);
            delay(delay_GSM);
            mySerial.write(26);
            symbol = "";
          }
        }
      }
    }
  }
  //--------------------------

  void screen() {

//    if (damage == 1 && onlyBattery == 1 && noPower == 1
//        && conditionA == 0 && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Μαχάτος   Μιχάλης"  );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση OFF" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 OFF" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 1 && onlyBattery == 1 && noPower == 1
//             && conditionA == 1 && conditionB == 1) {
//
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Μαχάτος   Μιχάλης"  );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση ON" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 ON" );
//      } while ( u8g2.nextPage() );
//    }
//
//    else if (damage == 1 && onlyBattery == 1 && noPower == 1
//             && conditionA == 1 && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Μαχάτος   Μιχάλης"  );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση ON" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 OFF" );
//      } while ( u8g2.nextPage() );
//    }
//
//    else if (damage == 1 && onlyBattery == 1 && noPower == 1
//             && conditionA == 0 && conditionB == 1) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Μαχάτος   Μιχάλης"  );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση OFF" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 ON" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 0 && onlyBattery == 1 && noPower == 1
//             && (conditionA == 1 || conditionA == 0) && conditionB == 1) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Μαχάτος   Μιχάλης"  );
//        u8g2.drawUTF8( b, 32, "Βλαβη Αντλιας" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 ON" );
//      } while ( u8g2.nextPage() );
//    }
//
//    else if (damage == 0 && onlyBattery == 1 && noPower == 1
//             && (conditionA == 1 || conditionA == 0) && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Μαχάτος   Μιχάλης"  );
//        u8g2.drawUTF8( b, 32, "Βλαβη Αντλιας" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 OFF" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 0 && (onlyBattery == 0 || noPower == 0)
//             && (conditionA == 1 || conditionA == 0) && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Διακοπη Ρευμα" );
//        u8g2.drawUTF8( b, 32, "Βλαβη Αντλιας" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 OFF" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 0 && (onlyBattery == 0 || noPower == 0)
//             && (conditionA == 1 || conditionA == 0) && conditionB == 1) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Διακοπη Ρευμα" );
//        u8g2.drawUTF8( b, 32, "Βλαβη Αντλιας" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 ON" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 1 && (onlyBattery == 0 || noPower == 0)
//             && conditionA == 0 && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Διακοπη Ρευμα" );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση OFF" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 OFF" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 1 && (onlyBattery == 0 || noPower == 0)
//             && conditionA == 0 && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Διακοπη Ρευμα" );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση ON" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 ON" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 1 && (onlyBattery == 0 || noPower == 0)
//             && conditionA == 1 && conditionB == 0) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Διακοπη Ρευμα" );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση ON" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 OFF" );
//      } while ( u8g2.nextPage() );
//    }
//    else if (damage == 1 && (onlyBattery == 0 || noPower == 0)
//             && conditionA == 0 && conditionB == 1) {
//      u8g2.firstPage();
//      do {
//        u8g2.setFont(u8g2_font_cu12_t_greek);
//        u8g2.drawUTF8( a, 12, "Διακοπη Ρευμα" );
//        u8g2.drawUTF8( b, 32, "Γεωτρηση OFF" );
//        u8g2.drawUTF8( c, 52, "Ρελε_2 ON" );
//      } while ( u8g2.nextPage() );
//    }
  }
