#ifndef __PAT_Task_PushButton_h__
#define __PAT_Task_PushButton_h__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void task_PushButton(void);
static void pushButton0_handel(void);
static void pushButton1_handel(void);
static void pushButton2_handel(void);
static void pushButton3_handel(void);

class class_pushButton
{
private:
  unsigned int pin;
  unsigned int state;
  unsigned int mode;
  void (*handel)(void);

public:
   volatile int cunter;  
  //Status = INPUT_PULLUP or INPUT_PULLDOWN
  //Mode = RISING or FALLING or CHANGE or ONLOW or ONHIGH or ONLOW_WE or ONHIGH_WE
  class_pushButton(uint8_t pin,void (*routine)(void) = NULL, uint8_t state = INPUT_PULLUP, uint8_t mode = FALLING);
  void init();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // __PAT_Task_PushButton_h__








/*
void RoutinSwitch0(void);
void RoutinSwitch1(void);
void RoutinSwitch2(void);
void RoutinSwitch3(void);
void RoutinSwitch4(void);

class class_Interrupt
{
private:
  unsigned int interruptPin;
  unsigned int interruptState;
  unsigned int interruptMode;
  void (*interruptRoutine)(void);

public:
  int cunter;
//------------------------------  
  //Status = INPUT_PULLUP or INPUT_PULLDOWN
  //Mode = RISING or FALLING or CHANGE or ONLOW or ONHIGH or ONLOW_WE or ONHIGH_WE
  class_Interrupt(uint8_t pin, uint8_t state = INPUT_PULLDOWN, uint8_t mode = RISING, void (*routine)(void) = NULL);
  void handleInterrupt();
  void begin();

};*/











// void task_PushButton(void);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
class PushButtonClass {
private:
  int pin;
  volatile bool isPressed;
  unsigned long lastDebounceTime;
  unsigned long debounceDelay;

public:
  PushButtonClass(int _pin = 2, unsigned long _debounceDelay = 50);
  void begin();
  bool isButtonPressed();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PushButtonClass::PushButtonClass(int _pin, unsigned long _debounceDelay) {
  pin = _pin;
  isPressed = false;
  lastDebounceTime = 0;
  debounceDelay = _debounceDelay;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PushButtonClass::begin() {
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(pin), [this]() {
      if ((millis() - lastDebounceTime) >= debounceDelay) {
        isPressed = !isPressed;
        lastDebounceTime = millis();
      }
    },
    FALLING);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PushButtonClass::isButtonPressed() {
  return isPressed;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PushButtonClass pushButton(BUTTON_PIN);
//-------------------------------------
*/

/*
class PushButtonClass {
private:
  int pin;
  volatile bool isPressed;
  unsigned long lastDebounceTime;
  unsigned long debounceDelay;

public:
  PushButtonClass(int _pin = 2, unsigned long _debounceDelay = 50);
  void begin();
  bool isButtonPressed();
};

PushButtonClass::PushButtonClass(int _pin, unsigned long _debounceDelay) {
  pin = _pin;
  isPressed = false;
  lastDebounceTime = 0;
  debounceDelay = _debounceDelay;
}

void PushButtonClass::begin() {
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(pin), [this]() {
      if ((millis() - lastDebounceTime) >= debounceDelay) {
        isPressed = !isPressed;
        lastDebounceTime = millis();
      }
    },
    FALLING);
}

bool PushButtonClass::isButtonPressed() {
  return isPressed;
}

const int BUTTON_PIN = 2; // Define BUTTON_PIN with the desired pin number
PushButtonClass pushButton(BUTTON_PIN);
*/


