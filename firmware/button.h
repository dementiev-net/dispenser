#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class BUTTON {
  private:
    bool buttonVal = true;
    bool buttonLast = true;
    bool DCwaiting = true;
    bool DConUp = true;
    bool singleOK = false;
    long downTime = -1;
    long upTime = -1;
    bool ignoreUp = true;
    bool waitForUp = true;
    bool holdEventPast = true;
    bool longHoldEventPast = true;
  public:
    BUTTON();
    int checkButton(int pin);
};

#endif
