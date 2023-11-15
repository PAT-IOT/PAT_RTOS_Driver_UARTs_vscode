
#include <Arduino.h>
#include "PAT_Tasks_OS.h"
#include "PAT_Task_MCU.h"
#include "PAT_Task_MQTT.h"
#include "PAT_Task_WebServer.h"
#include "PAT_Task_PushButton.h"
#include "PAT_RTC.h"
#include "PAT_Relay.h"
#include "lib/PAT_Debug.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TaskHandle_t core0_Task;
// void core0_Loop_init(void) {
//   xTaskCreatePinnedToCore(
//     core0_Loop,    // Task function.
//     "core0_Task",  // name of task.
//     10000,         // Stack size of task
//     NULL,          // parameter of the task
//     1,             // If you want to increase the priority of a task, you should assign it a lower numerical priority value. For example, a task with priority 1 has a higher priority than a task with priority 2, and so on.
//     &core0_Task,   // Task handle to keep track of created task
//     0);            // pin task to core 0
// }
// dataQueue = xQueueCreate(5, sizeof(int));  // Create a queue for data transfer// Queue size of 5, assuming you're sending integers
QueueHandle_t dataQueue;
void tasks_OS_Init() {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////------------------------------------------
  //dataQueue = xQueueCreate(5, sizeof(int)); 
  // Set up Core 0 tasks
  xTaskCreatePinnedToCore(taskCore0_1, "TaskCore0_1", 10000, NULL, 1, NULL, 0);
  //xTaskCreatePinnedToCore(taskCore0_2, "TaskCore0_2", 5000, NULL, 2, NULL, 0);
  //xTaskCreatePinnedToCore(taskCore0_3, "TaskCore0_3", 1000, NULL, 3, NULL, 0);
  // Set up Core 1 tasks
  xTaskCreatePinnedToCore(taskCore1_1, "TaskCore1_1", 10000, NULL, 1, NULL, 1);
  //xTaskCreatePinnedToCore(taskCore1_2, "TaskCore1_2", 5000, NULL, 2, NULL, 1);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////------------------------------------------
}
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_1(void* parameter) 
                            {
  int receivedData;
  for (;;) {
    //if (xQueueReceive(dataQueue, &receivedData, portMAX_DELAY) == pdPASS) {
     // Serial.println(String(millis()/1000.0) +"-> TaskCore0_1: receive "+ String(receivedData));

     //task_MCU();
    task_Relay();
    task_RTC();
    //}
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_2(void* parameter) {
      static int dataToSend = 0;  // Sample data to send
  for (;;) {
  // task_PushButton();
    //task_MCU();
    dataToSend++;
   // if (xQueueSend(dataQueue, &dataToSend, portMAX_DELAY) == pdPASS) {
      //Serial.println(String(millis()/1000.0) + "-> TaskCore0_2 Send : " + String(dataToSend));
//}

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_3(void* parameter) {
  for (;;) {
   //task_WebServer();
    Serial.println(String(millis()/1000.0) + "-> taskCore0_3");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
void taskCore1_1(void* parameter) {
  for (;;) {
    DEBUG_MEASURE_TIME(
      
      task_MQTT();
    task_implement_weeklySchedule();
 )
    //Serial.println("\t\t\t" + String(millis()/1000.0) + "-> TaskCore1_1");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
void taskCore1_2(void* parameter) {
  for (;;) {

   DEBUG_MEASURE_TIME(
    //task_ping();
    )
    //Serial.println("\t\t\t" + String(millis()/1000.0) + "-> TaskCore1_2");
    vTaskDelay(11000 / portTICK_PERIOD_MS);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

