
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "PAT_Tasks_OS.h"
#include "PAT_Application.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct struct_queueData {
  int relayM[_RELAY_NUMBER];
  int relayR[_RELAY_NUMBER];
};
struct_queueData queueDataCore0;
struct_queueData queueDataCore1;


struct struct_queueHandle {
  QueueHandle_t relayM;
  QueueHandle_t relayR;
};
struct_queueHandle queueHandle;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////------------------------------------------
void tasks_OS_Init() {
 //-------------------------------------------------------
  // Create queues for each relay type
  queueHandle.relayM = xQueueCreate(1, sizeof(uint8_t) * _RELAY_NUMBER);
  queueHandle.relayR = xQueueCreate(1, sizeof(uint8_t) * _RELAY_NUMBER);

  if (queueHandle.relayM == NULL || queueHandle.relayR == NULL)
  {
    Serial.println("Failed to create the queue");
    Serial.flush();
    esp_restart();
  }
  //-------------------------------------------------------
  // Set up Core0 tasks
  xTaskCreatePinnedToCore(taskCore0_1, "TaskCore0_1", 4000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskCore0_2, "TaskCore0_2", 4000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskCore0_3, "TaskCore0_3", 4000, NULL, 3, NULL, 0);
  xTaskCreatePinnedToCore(taskCore0_4, "TaskCore0_4", 4000, NULL, 4, NULL, 0);
  // Set up Core1 tasks
  xTaskCreatePinnedToCore(taskCore1_1, "TaskCore1_1", 5000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskCore1_2, "TaskCore1_2", 5000, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(taskCore1_3, "TaskCore1_3", 10000, NULL, 3, NULL, 1);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////------------------------------------------
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_1(void* parameter) {
  for (;;)
  {
    if (task_NRF24_Received(queueDataCore0.relayR))
    {
      if (xQueueSend(queueHandle.relayR, &queueDataCore0.relayR, portMAX_DELAY) != pdPASS)
      {
        Serial.println("Failed to send data to the relayS queue");
      }
    }

    //DEBUG_MEASURE_TIME(
   //task_MCU_Received();
    
    //)
      delay_OS(5);
  }
}
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_2(void* parameter) {

  for (;;)
  {

    //DEBUG_MEASURE_TIME(
      
    //)
      delay_OS(500);
  }
}
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_3(void* parameter) {
  for (;;)
  {

    //DEBUG_MEASURE_TIME(
      tast_leds();
    //)
      delay_OS(200);
  }
}
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void taskCore0_4(void* parameter) {
  static int dataToSend = 0;  // Sample data to send
  for (;;)
  {
    tast_leds2();

    delay_OS(200);
  }
}
//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
void taskCore1_1(void* parameter) {
  for (;;)
  {
    task_MCU_Received();
    if (xQueueReceive(queueHandle.relayR, &queueDataCore1.relayR, portMAX_DELAY) != pdPASS)
      {
        Serial.println("Received data from Core 0:");

          for (int index = 0; index < _RELAY_NUMBER; index++)
          {
            if (queueDataCore1.relayR[index] == 1)
            {
              //queueDataCore1.relayR[index] = 0;
              (ubuf.relay[index]) ? ubuf.relayR[index] = 0 : ubuf.relayR[index] = 1;
              ubuf.relayMode[index] = 'r';
            }
          }
      }
     
      delay_OS(50);
  }
}
//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
void taskCore1_2(void* parameter) {
  task_MCU_Send();
  int receivedData;
  for (;;)
  {
    //Serial.println("\t\t\t" + String(millis()/1000.0) + "-> TaskCore1_2");
    //DEBUG_MEASURE_TIME(
    task_MQTT();
    //)
    delay_OS(500);
  }
}
//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
void taskCore1_3(void* parameter) {
  for (;;)
  {
    //Serial.println("\t\t\t" + String(millis()/1000.0) + "-> TaskCore1_1");
    //esp.wdg_reset();
    task_RTC();
    task_run_weeklySchedule();
    delay_OS(1000);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


