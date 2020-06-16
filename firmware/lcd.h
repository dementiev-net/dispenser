#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "config.h"
#include "fonts.h"
#include <OLED_I2C.h>

struct LCDData {
  byte cntMM = 1;
  uint16_t menuAccPush;
  uint16_t menuAccPull;
  uint16_t menuSpeedPush;
  uint16_t menuSpeedPull;
  uint16_t menuStepPush;
  uint16_t menuStepPull;
};

class LCD {
  private:
    OLED *display;
  public:
    bool isset;
    LCD();
    void init();
    void splashScreen();
    void staticMenu(LCDData* refdataScreen);
    void resultScreen(char text[20]);
    void resultWork();
};

#endif
