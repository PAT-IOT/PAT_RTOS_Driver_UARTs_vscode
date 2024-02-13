#ifndef __PAT_IO_Devices_h__
#define __PAT_IO_Devices_h__


#include <tuple>
#include <utility>
#include <iostream>

#define _RELAYS_FIRST_INDEX  0
#define _RELAYS_LAST_INDEX   3
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void init_IO_Devices(void) __attribute__((weak));

//static const uint8_t
// void construct1() __attribute__((constructor(101)));
// void destruc1() __attribute__((destructor(101)));
// void construct1 () {
//     printf ("\n      construct1() constructor -- (.section .ctors) priority 101\n");
// }
// void destruct1 () {
//     printf ("\n      destruct1() destructor -- (.section .dtors) priority 101\n\n");
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*template <int Start, int End, typename classT>
class class_Array {
private:
    classT data[End - Start + 1];

public:
    class_Array() {}

    class_Array(classT objects[]) {
        for (int i = Start; i <= End; ++i) {
            data[i - Start] = objects[i - 1];
        }
    }

    classT& operator[](int index) {
        if (index >= Start && index <= End) {
            return data[index - Start];
        } else {
            //Serial.println("Error: Index out of range");
            static classT errorObject = 0;
            return errorObject;       
             }
    }
        int getFirstIndex() {
        return Start;
    }

    int getLastIndex() {
        return End;
    }
};*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    IO_TURNED_OFF = 0,
    IO_TURNED_ON = 1,
    IO_FLOATING = 2,
    IO_NOTSET = 3
} IO_status_t;


class class_Digital_Output {
private:

public:
  uint8_t pin;
  uint8_t mode;
  uint8_t isOn;
  IO_status_t  status_t;
  void init();
  class_Digital_Output(uint8_t pin, bool activeMode = HIGH);
  void operator()(bool activeMode);
  void turnOn();
  void turnOff();
  void toggle();
  void floating();
  void toggleOnFloating();
  void toggleOffFloating();
  IO_status_t status();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _PUSHBUTTON_NUMBER 12 
#define _PUSHBUTTON_DEBOUNCE_DELAY 500 

void task_PushButton(void);
static void pushButton_WebServer_handel(void);
static void pushButton_ResetPassword_handel(void);

class class_Input
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
  class_Input(uint8_t pin,void (*routine)(void) = NULL, uint8_t state = INPUT_PULLUP, uint8_t mode = FALLING);
  void init();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // __PAT_IO_Devices_h__