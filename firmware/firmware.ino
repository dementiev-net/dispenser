// ----------------------------------------------------------------------------
// Дозатор паяльной пасты
// версия 2.0 (Atmega328)
// (c) 2020 Дмитрий Дементьев <dementiev@me.com>
// ----------------------------------------------------------------------------

#include <EEPROM.h>
#include "config.h"
#include "button.h"
#include "lcd.h"
#include <AccelStepper.h>

LCD lcd;
LCDData dataScreen;
BUTTON button1;
BUTTON button2;
BUTTON button3;
AccelStepper stepper1(4, 2, 4, 3, 5);
AccelStepper stepper2(4, 2, 4, 3, 5);

int Presets[] = {0, 0, 0, 0, 0};
boolean pull = false; // флаг возврата
int mode = 0; // флаг режима

void setup()
{
  firstRun();
  Presets[0] = EEPROM.read(0); // берем пресеты из EEPROM
  Presets[1] = EEPROM.read(1);
  Presets[2] = EEPROM.read(2);
  Presets[3] = EEPROM.read(3);
  Presets[4] = EEPROM.read(4);
  for (int i = 0; i < 5; i++)
  {
    if (Presets[i] < 0 || Presets[i] > 86400) Presets[i] = 0;
  }
  pinMode(6, INPUT); // входы
  digitalWrite(6, HIGH);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  lcd.init();
  lcd.splashScreen();
  delay(1000);
}

void loop()
{
  byte btn1 = button1.checkButton(6);
  byte btn2 = button2.checkButton(8);
  byte btn3 = button3.checkButton(7);

  /**
     режим работы
  */
  if (mode == 0)
  {
    if (btn1 == 3) mode = 1;
    if (pull == false) lcd.resultScreen("Ujnjd r hf,jnt");
    if (btn2 == 1)
    {
      lcd.resultWork();
      stepper1.setCurrentPosition(0);
      stepper1.setAcceleration(Presets[0] * 10);
      stepper1.setMaxSpeed(Presets[1] * 10);
      stepper1.moveTo(Presets[2] * 10);
      stepper1.runToPosition();
      stepper1.setMaxSpeed(Presets[3] * 10);
      stepper1.moveTo((Presets[2] * 10) -  (Presets[4] * 10));
      stepper1.runToPosition();
    }
    if (pull)
    {
      stepper2.setSpeed(-Presets[3] * 10);
      stepper2.runSpeed();
      lcd.resultScreen("DJPDHFN");
    }
    if (btn3 == 1)
    {
      if (pull == false) pull = true; else pull = false;
    }

    /**
       режим меню
    */
  } else if (mode == 1) {

    dataScreen.menuAccPush   = Presets[0];
    dataScreen.menuSpeedPush = Presets[1];
    dataScreen.menuStepPush  = Presets[2];
    dataScreen.menuSpeedPull = Presets[3];
    dataScreen.menuStepPull  = Presets[4];

    if (btn1 == 1 && dataScreen.cntMM <= 6) dataScreen.cntMM++;
    if (btn1 == 1 && dataScreen.cntMM >= 6) dataScreen.cntMM = 1;
    if (btn2 == 1 && Presets[dataScreen.cntMM - 1] < 100) Presets[dataScreen.cntMM - 1] = Presets[dataScreen.cntMM - 1] + SET_STEP;
    if (btn3 == 1 && Presets[dataScreen.cntMM - 1] > 1) Presets[dataScreen.cntMM - 1]   = Presets[dataScreen.cntMM - 1] - SET_STEP;
    lcd.staticMenu(&dataScreen);

    if (btn1 == 3)
    {
      for (int i = 0; i < 5; i++)
      {
        EEPROM.update(i, Presets[i]);
      }
      mode = 0;
      dataScreen.cntMM = 1;
      lcd.resultScreen("Cj[hfytyj");
      delay(3000);
    }
  }
}

//первый запуск
bool firstRun()
{
  for (uint16_t i; i < sizeof(Presets); i++)
  {
    if (EEPROM.read(i) != 255) return false;
  }
  Presets[0] = MOT_ACC_PUSH;
  Presets[1] = MOT_SPEED_PUSH;
  Presets[2] = MOT_STEP_PUSH;
  Presets[3] = MOT_SPEED_PULL;
  Presets[4] = MOT_STEP_PULL;
  for (int i = 0; i < 5; i++)
  {
    EEPROM.update(i, Presets[i]);
  }
}
