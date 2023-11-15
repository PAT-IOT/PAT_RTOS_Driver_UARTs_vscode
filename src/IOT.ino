#include <Arduino.h>
//#include <PSRamFS.h>
#include "WiFi.h"
#include "lib/PAT_Debug.h"
//#include "PAT_Configuration.h"
#include "PAT_RTC.h"
// #include <WebSocketsClient.h>
// #include <MQTTPubSubClient.h>
//#include "PAT_PCB_HAL.h"
// #include "PAT_Memory.h"
// #include <Preferences.h>
#include "PAT_Tasks_OS.h"
#include "PAT_Task_MCU.h"
//#include "PAT_Task_WebServer.h"
//#include "PAT_Task_PushButton.h"
#include "PAT_Task_MQTT.h"
#include "PAT_JSON.h"
#include "PAT_Task_PushButton.h"
#include "PAT_Relay.h"
#include "PAT_Task_MCU.h"
#include "esp_system.h"


extern class_pushButton pushButton[];
extern class_Relay relay[];
extern class_MQTT MQTT;
//extern class_Array< 1, 4, class_Relay > relay;
extern class_RTC RTC;
extern class_MCU MCU;
extern String _CHIP_SERIAL_NUMBER;
extern class_Composer compose;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
    delay(1000);

  Serial.println();
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");

  //while (!PSRamFS.begin())
  /* while (!psramInit())
  {
    Serial.println("Failed to mount PSRamFS");
      delay(1000);
  }  
   Serial.println("PSRamFS mounted successfully");
 */
  for (int i = 0; i < 4; i++)
  {
    relay[i].init();
  }

  
  RTC.init();
  MCU.init();
  compose.load("relayData");
  delay(1000);


  tasks_OS_Init();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      // Get the current millis() value




