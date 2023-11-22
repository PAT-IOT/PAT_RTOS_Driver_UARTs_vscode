#include <Arduino.h>
#include <HardwareSerial.h>
#include "PAT_Task_MCU.h"
#include "PAT_JSON.h"
//class_MCU MCU;

//volatile String class_MCU::data;

  //MCU.println("$relay[]={0,0,0,0,0,0,0,0}@");
  //MCU.flush();
  //delay(2000);





class_MCU MCU; // Use the UART2
extern class_UserBuffer ubuf;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RX_DATA_BUFFER_SIZE 256 // Define the size of the buffer
 volatile char  rx_data[RX_DATA_BUFFER_SIZE]; // Declare a volatile character array
  int  rx_data_Flag=0;


static void uart2_rx_handler() {
if (Serial2.available()) {
    rx_data_Flag = Serial2.readBytesUntil('\n', (char *)rx_data, sizeof(rx_data) - 1);
    rx_data[rx_data_Flag] = '\0'; // Null-terminate the string
    Serial.println((char *)rx_data);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_MCU::init(unsigned  long   baud,                 \
                                int8_t rxPin,               \
                                int8_t txPin,               \
                                uint8_t rxfifo_full_thrhd   \
                                ){                          \
                    begin(baud, SERIAL_8N1, rxPin, txPin, false, 20000UL, rxfifo_full_thrhd);
                    //attachInterrupt(digitalPinToInterrupt(_RX2_PIN), uart2_rx_handler, RISING);
                    //flag = &(rx_data_Flag);
                    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String class_MCU::readData(void) {
            if(rx_data_Flag) {
              rx_data_Flag=0;
              return String((char *)rx_data);
            }
            return "";
          }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


























// $$$relay[]={1,0,1,0,1,1,0,0}@@@
// $$$relay[]={0,1,1,1,1,1,0,0}@@@
// $$$relay[]={1,0,0,1,1,1,1,0}@@@
// $$$relay[]={1,0,1,0,1,1,0,0}@@@
// $$$relay[]={1,0,1,1,0,1,0,0}@@@
// $$$relay[]={1,1,1,0,1,1,0,1}@@@
// $$$relay[]={1,0,1,1,1,0,0,0}@@@







