#include <Arduino.h>
#include <HardwareSerial.h>
#include "PAT_Task_MCU.h"
#include "PAT_JSON.h"
#include <PAT_IO_Devices.h>
#include "PAT_Prototype.h"



const uint8_t MCU_BOOT_PIN = 26;
const uint8_t MCU_BOOT_PIN_MODE = LOW;
const uint8_t MCU_RESET_PIN = 25;
const uint8_t MCU_RESET_PIN_MODE = HIGH;


class_Digital_Output MCU_Boot(MCU_BOOT_PIN, MCU_BOOT_PIN_MODE);
class_Digital_Output MCU_Reset(MCU_RESET_PIN, MCU_RESET_PIN_MODE);

class_MCU MCU; // Use the UART2
extern class_UserBuffer ubuf;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RX_DATA_BUFFER_SIZE 256 // Define the size of the buffer
 volatile char  rx_data[RX_DATA_BUFFER_SIZE]; // Declare a volatile character array
  int  rx_data_Flag=0;


// void uart2_Rx_handler() {
//     if (Serial2.available()) {
//         rx_data = Serial2.read('\n');
//         rx_data[rx_data_Flag] = '\0'; // Null-terminate the string
//         Serial.print("MCU: ");
//         Serial.println((char*)rx_data);
//     }
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_MCU::init(unsigned long baud,int8_t rxPin, int8_t txPin, uint8_t rxfifo_full_thrhd ) {
  MCU_Boot.init();
  MCU_Reset.init();
  MCU_Boot.turnOff();
  MCU_Reset.turnOff();
  begin(baud, SERIAL_8N1, rxPin, txPin, false, 20000UL, rxfifo_full_thrhd);
  Str.reserve(200);
  //attachInterrupt(digitalPinToInterrupt(_RX2_PIN), uart2_Rx_handler, FALLING);
  //flag = &(rx_data_Flag);
  //this->reset()
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String class_MCU::readStr(void) {
 this->Str= "";
  while (this->available())
    {
      char inChar = (char)this->read();
      this->Str += inChar;
      delay_OS(1);
  }
  return  this->Str;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_MCU:: extractData(String input, const char* identifier, int* inputDataArray) {
  String pattern = String(identifier) + "[]={";
  int start = input.indexOf(pattern);
  int end = input.indexOf("}", start);
  int dataArray[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  if (start != -1 && end != -1) {
    String dataString = input.substring(start + pattern.length(), end);
    int index = 0;

    while (index < 12) {
      int value;
      int result = sscanf(dataString.c_str(), "%d,", &value);

      if (result == 1) {
        dataArray[index] = value;
        index++;
      } else {
        break;
      }
      // Move to the next comma
      dataString = dataString.substring(dataString.indexOf(',') + 1);
    }
    if (index == 12)
    {
      for (int a = 0; a < 12; a++)
      {
        inputDataArray[a] = dataArray[a];
      }
      return  1; // Return 1 if successfully extracted 12 data elements, 0 otherwise
    }else return  0; 
  }
  return 0; // Return 0 if pattern not found
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_MCU::turnOn(void) {
  MCU_Reset.turnOn();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_MCU::turnOff(void) {
  MCU_Reset.turnOff();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_MCU::checkReceivedData(void) {
  String ReceivedStr = MCU.readStr();
  String relayStr = "";
  String pushButtonStr = "";
  int relayInt[12];
  this->flag.pushButtonReceived = 0;
  this->flag.relayReceived = 0;
  if (ReceivedStr != "")
  {
    //Serial.println("MCU Received:  " + ReceivedStr);
    //-----------------------------------------------------------
    if (this->extractData(ReceivedStr, "Received:relay", this->relay))
    {
      this->flag.relayReceived = 1;
      //Serial.println("relay data was Received by MCU");
    }
    //-----------------------------------------------------------
    if (this->extractData(ReceivedStr, "pushButton", this->pushButton))
    {
      this->flag.pushButtonReceived = 1;
      // Serial.println("PushButton data was Received by MCU");
      Serial.println("MCU Received:  " + ReceivedStr);
    }
    //-----------------------------------------------------------
    return(this->flag.pushButtonReceived || this->flag.relayReceived);
  }
  else return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_MCU::send(int *relay) {
    MCU.firstInterval = millis();
    char out[100];
    int result = snprintf(out, sizeof(out), "relay[]={%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}",
        relay[0], relay[1], relay[2], relay[3],
        relay[4], relay[5], relay[6], relay[7],
        relay[8], relay[9], relay[10], relay[11]);

    MCU.println(out);
    delay_OS(10);
    MCU.flush();
    //Serial.println(out);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool extractData(String input, const char *identifier, int *dataArray)
// {
//   String pattern = String(identifier) + "[]={%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}";
//   int result = sscanf(input.c_str(), pattern.c_str(),
//                       &dataArray[0], &dataArray[1], &dataArray[2], &dataArray[3],
//                       &dataArray[4], &dataArray[5], &dataArray[6], &dataArray[7],
//                       &dataArray[8], &dataArray[9], &dataArray[10], &dataArray[11]);
//   return (result == 12);
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void task_Received_MCU(void) {
  String ReceivedStr = MCU.readStr();
  if (ReceivedStr != "")
  {
    //-----------------------------------------------------------
    if (extractData(ReceivedStr, "Received: relay", relayData))
      {
        ubuf.relayMCU[i]=
        relayData =
              //   //MCU.reset();
              //   Serial.println("MCU.reset()");
          ubuf.relayUpdated[i] = 1;
          for (int i = 0; i < 12; i++)
            {
              if (ubuf.relayMCU[i] != ubuf.relayM[i])
              {
                ubuf.relayUpdated[i]=0
              }
            }
            Serial.println("got PushButton");
    }
    //-----------------------------------------------------------

    Serial.println(ReceivedStr);

        if (extractData(ReceivedStr, "pushButton", pushButtonData))
        {
          ubuf.relayUpdated[i] = 1;
          for (int i = 0; i < 12; i++)
            {
              if (ubuf.relayMCU[i] != ubuf.relayM[i])
              {
                ubuf.relayUpdated[i]=0
              }
            }

            Serial.println("got PushButton");
        }
  }
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // int   ubuf.relay[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
// void MCU.send(int * relay) {
//   MCU.firstInterval = millis();
//     char out[100];
//     int result = snprintf(out, sizeof(out), "relay[]={%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}",
//       ubuf.relay[0], ubuf.relay[1], ubuf.relay[2], ubuf.relay[3],
//       ubuf.relay[4], ubuf.relay[5], ubuf.relay[6], ubuf.relay[7],
//       ubuf.relay[8], ubuf.relay[9], ubuf.relay[10], ubuf.relay[11]);

//     MCU.println(out);
//     MCU.flush();
//     Serial.println(out);
// }





// $$$relay[]={1,0,1,0,1,1,0,0}@@@
// $$$relay[]={0,1,1,1,1,1,0,0}@@@
// $$$relay[]={1,0,0,1,1,1,1,0}@@@
// $$$relay[]={1,0,1,0,1,1,0,0}@@@
// $$$relay[]={1,0,1,1,0,1,0,0}@@@
// $$$relay[]={1,1,1,0,1,1,0,1}@@@
// $$$relay[]={1,0,1,1,1,0,0,0}@@@







