#ifndef __PAT_Task_MCU_h__
#define __PAT_Task_MCU_h__

#include <Arduino.h>


#define _TX2_PIN 16
#define _RX2_PIN 17
#define _UART_MCU 2  //uart2



static void uart2_rx_handler();

class class_MCU : public HardwareSerial {
public:
int *flag;
char *data;
//String relay = "relay[]={0,0,0,0,0,0,0,0,0,0,0,0}";

 class_MCU() : HardwareSerial(2) {}
  void init(unsigned long baud = 9600,
            int8_t rxPin = 16,
            int8_t txPin = 17,
            uint8_t rxfifo_full_thrhd = 112);

  String readData(void);
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