#ifndef __PAT_Task_MCU_h__
#define __PAT_Task_MCU_h__

#include <Arduino.h>


#define _TX2_PIN 16
#define _RX2_PIN 17
#define _UART_MCU 2  //uart2
#define   _MCU_VALID_INTERVAL  3500


static void uart2_Rx_handler();


struct struct_flag{
  public:
    int pushButtonReceived = 0;
    int relayReceived = 0;
};

class class_MCU : public HardwareSerial {
public:
char* data;
String Str = "";
int relay[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
int pushButton[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
struct_flag flag;

long lastInterval = 0;
long firstInterval = 0;

class_MCU() : HardwareSerial(2) {

}

void init(unsigned long baud = 115200,
            int8_t rxPin = 16,
            int8_t txPin = 17,
            uint8_t rxfifo_full_thrhd = 112);


  String readStr(void);
  void send(int* relay);
  void turnOn(void);
  void turnOff(void);
  int extractData(String input, const char* identifier, int* dataArray);
  int checkReceivedData(void);
};

//class_MCU MCU(_UART_MCU); // Use the UART2


// $$$relay[]={1,0,1,0,1,1,0,0}@@@
// $$$relay[]={0,1,1,1,1,1,0,0}@@@
// $$$relay[]={1,0,0,1,1,1,1,0}@@@
// $$$relay[]={1,0,1,0,1,1,0,0}@@@
// $$$relay[]={1,0,1,1,0,1,0,0}@@@
// $$$relay[]={1,1,1,0,1,1,0,1}@@@
// $$$relay[]={1,0,1,1,1,0,0,0}@@@



#endif //__PAT_Task_MCU_h__