Note1: You should make sure you are using OPEN-SMART 2.8 INCH TFT LCD shield or TFT breakout board whose driver IC is ILI9320.
Note2: Because the resolution of the shield is 240*320, the code in the MCUFRIEND_kbv.cpp should also be like that:
MCUFRIEND_kbv::MCUFRIEND_kbv(int CS, int RS, int WR, int RD, int RST):Adafruit_GFX(240, 320)
{
    // we can not access GPIO pins until AHB has been enabled.
}