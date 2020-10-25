#include <EEPROM.h>

#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12

#define ARRAY_SIZE 4
#define LAST_SELECTED_LED_EEPROM_ADDR 10

int ledPinArray[4] = { LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN };

int i;

void setLedPinModes() 
{
  for (i = 0 ; i < ARRAY_SIZE ; i++) {
    pinMode(ledPinArray[i], OUTPUT);
  }
}

void setInitialLedStates()
{
  for (i = 0 ; i < ARRAY_SIZE ; i++) {
    digitalWrite(ledPinArray[i], LOW);
  }
}

void powerOnLed(int ledIndex)
{
  for (i = 0; i < ARRAY_SIZE; i++) {
    if (i == ledIndex) {
      digitalWrite(ledPinArray[i], HIGH);
    }
    else {
      digitalWrite(ledPinArray[i], LOW);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setLedPinModes();
  int lastSelectedLedIndex = EEPROM.read(LAST_SELECTED_LED_EEPROM_ADDR);
  powerOnLed(lastSelectedLedIndex);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    int ledIndex = Serial.parseInt();
    if (ledIndex >= 0 && ledIndex < ARRAY_SIZE) {
      powerOnLed(ledIndex);
      // write on the eeprom
      EEPROM.write(LAST_SELECTED_LED_EEPROM_ADDR, ledIndex);
    }
  }
}