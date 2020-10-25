class LED_Controls {
  public:

    void Begin(byte GPIO_pin) {
      pinMode(GPIO_pin, OUTPUT);
    }

    void ON(byte GPIO_pin){
      digitalWrite(GPIO_pin, HIGH);
    }

    void OFF(byte GPIO_pin){
      digitalWrite(GPIO_pin,LOW);
    }

    void flash(byte GPIO_pin, int flash_speed, int flashes){
      for (int f=0; f < flashes; f = f +1){
        ON(GPIO_pin);
        delay(flash_speed);
        OFF(GPIO_pin);
        delay(flash_speed);
      }
    }
};