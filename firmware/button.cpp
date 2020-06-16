#include "button.h"
#include "config.h"

BUTTON::BUTTON() { }

int BUTTON::checkButton(int pin)
{
  int event = 0;
  buttonVal = digitalRead(pin);
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > BTN_DEBOUNCE) // кнопка нажата
  {
    downTime = millis();
    ignoreUp = false;
    waitForUp = false;
    singleOK = true;
    holdEventPast = false;
    longHoldEventPast = false;
    if ((millis() - upTime) < BTN_DCGAP && DConUp == false && DCwaiting == true)  DConUp = true;
    else  DConUp = false;
    DCwaiting = false;
  }
  else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > BTN_DEBOUNCE) // кнопка отпущена
  {
    if (not ignoreUp)
    {
      upTime = millis();
      if (DConUp == false) DCwaiting = true;
      else
      {
        event = 2;
        DConUp = false;
        DCwaiting = false;
        singleOK = false;
      }
    }
  }
  if (buttonVal == HIGH && (millis() - upTime) >= BTN_DCGAP && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
  {
    event = 1;
    DCwaiting = false;
  }
  if (buttonVal == LOW && (millis() - downTime) >= BTN_HOLDTIME) // удержание кнопки
  {
    if (not holdEventPast) // тригер "нормального" удержания
    {
      event = 3;
      waitForUp = true;
      ignoreUp = true;
      DConUp = false;
      DCwaiting = false;
      //downTime = millis();
      holdEventPast = true;
    }
    if ((millis() - downTime) >= BTN_LONGHOLDTIME) // тригер "долгого" удержания
    {
      if (not longHoldEventPast)
      {
        event = 4;
        longHoldEventPast = true;
      }
    }
  }
  buttonLast = buttonVal;

  return event;
}
