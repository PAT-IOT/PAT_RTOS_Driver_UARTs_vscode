#ifndef __PAT_PCB_HAL_h__
#define __PAT_PCB_HAL_h__


#include <tuple>
#include <utility>
#include <iostream>

#define _RELAYS_FIRST_INDEX  0
#define _RELAYS_LAST_INDEX   3


void task_Relay(void);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <int Start, int End, typename classT>
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
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class class_Relay {
private:

public:
  uint8_t pin;
  bool mode;
  bool isOn;
  class_Relay(uint8_t pin , bool activeMode = HIGH);
  void operator()(bool activeMode);
  void turnOn();
  void turnOff();
  void toggle();
  void init();
  bool getState();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initialize_relays(void);































//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // __PAT_PCB_HAL_h__