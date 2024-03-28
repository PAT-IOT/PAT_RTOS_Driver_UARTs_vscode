
#include <Arduino.h>
#include "PAT_RTOS_Driver.h"
//#include "RTOS_Driver_UARTs.env"

extern class_RTOS_Driver driver;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_application(void *arg)
{

  while (1)
  {
    //-----------------------------------------------
    char data[driver.uart0.size()]; // Buffer to store received data
    if (driver.uart0.read(data))
    {                                              // Check if data is received from the UART queue
      Serial.println("Received= " + String(data)); // If data is received, print it
    }
    //-----------------------------------------------
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay before reading next data
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup function
void setup()
{
  Serial.begin(115200);                                                                                             // Initialize serial communication
  driver.init();                                                                                                    // Initialize the UART driver
  xTaskCreatePinnedToCore(task_application, "task application", 1024 * 4, NULL, configMAX_PRIORITIES - 2, NULL, 0); // Create the application task
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Loop function (not used)
void loop()
{
  delay(1000);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
