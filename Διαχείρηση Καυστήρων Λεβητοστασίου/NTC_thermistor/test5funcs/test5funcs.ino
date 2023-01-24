
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float temperature;
 
void setup() {
  Serial.begin(115200);  /* Define baud rate for serial communication */
  u8g2.begin();
}

void loop() {


  u8g2.firstPage();
  do {
  
    //-------------------------------------
     u8g2.setFont(u8g2_font_cu12_t_greek);   
     u8g2.drawUTF8(30,20, "Θερμοκρασία"    );
     u8g2.setFont(u8g2_font_10x20_t_greek);

     NTC_therm(temperature);
     
     char temperature_array[10];
     dtostrf( temperature  , 0, 2, temperature_array);
     u8g2.drawStr(50,45,temperature_array  );
     u8g2.drawRFrame(2,0,126,62,7);
     
  } while ( u8g2.nextPage() );

delay(2000);
  
}

void NTC_therm( float &temp ){
  
    const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
    const double R2 = 10000;            // 10k ohm series resistor
    const double adc_resolution = 1023; // 10-bit adc
    
    const double A = 0.001129148;   // thermistor equation parameters
    const double B = 0.000234125;
    const double C = 0.0000000876741; 

    double Vout, Rth,  adc_value; 
    adc_value = analogRead(A0);
    Vout = (adc_value * VCC) / adc_resolution;
    Rth = (VCC * R2 / Vout) - R2;

/*  Steinhart-Hart Thermistor Equation:
 *  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)
 *  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temp = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));   // Temperature in kelvin

  temp = temp - 278.15;  // Temperature in degree celsius
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" degree celsius");
  
 
}
