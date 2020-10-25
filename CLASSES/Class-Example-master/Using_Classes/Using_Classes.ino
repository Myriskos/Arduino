
#include "ClassesLed.h"

// Class      Object
LED_Controls   LED;

void setup() {
  LED.Begin(LED_BUILTIN);
}



void loop() {
  LED.ON(LED_BUILTIN);
  delay(1000);
  LED.OFF(LED_BUILTIN);
  delay(1000);
  LED.flash(LED_BUILTIN,100,10);
}
