#include "lcd.h"

LCD::LCD()
{
  isset = true;
  display = new OLED(A4, A5);
}

void LCD::init()
{
  if (!isset)
  {
    return;
  }
  display->begin(SSD1306_128X32);
  display->setFont(SmallFont);
  display->update();
}

void LCD::splashScreen()
{
  display->clrScr();
  display->drawBitmap(0, 0, LogoBmp, 128, 32);
  display->update();
}

void LCD::staticMenu(LCDData* refdataScreen)
{
  byte i;
  display->clrScr();
  if (refdataScreen->cntMM < 4)
  {
    display->setFont(RusFont);
    display->print("1 Ecrjhtybt", 45, 1);
    display->print("2 Crjhjcnm", 45, 13);
    display->print("3 Ifub", 45, 25);
    display->setFont(TinyFont);
    display->drawBitmap(1, 2, iconDWN, 30, 32);
    display->print(String(refdataScreen->menuAccPush), 115, 3);
    display->print(String(refdataScreen->menuSpeedPush), 115, 15);
    display->print(String(refdataScreen->menuStepPush), 115, 27);
  }
  else
  {
    display->setFont(RusFont);
    display->print("4 Crjhjcnm", 45, 1);
    display->print("5 Ifub", 45, 13);
    display->setFont(TinyFont);
    display->drawBitmap(1, 2, iconUP, 30, 32);
    display->print(String(refdataScreen->menuSpeedPull), 115, 3);
    display->print(String(refdataScreen->menuStepPull), 115, 15);
  }
  switch (refdataScreen->cntMM)
  {
    case 1: i = 1; break;
    case 2: i = 13; break;
    case 3: i = 25; break;
    case 4: i = 1; break;
    case 5: i = 13; break;
  }
  display->print(">", 38, i);
  display->update();
}

void LCD::resultScreen(char text[20])
{
  display->clrScr();
  display->setFont(RusFont);
  display->print(text, CENTER, 16);
  display->update();
}

void LCD::resultWork()
{
  display->clrScr();
  display->drawBitmap(49, 1, iconDWN, 30, 32);
  display->update();
}
