//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "PAT_RTOS_Driver_UART2.h" // Include custom UART driver header file
#include "freertos/FreeRTOS.h"     // Include FreeRTOS headers
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h" // Include ESP32 UART driver
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QueueHandle_t driver_uart2_queue;                               // Queue handle for UART2 data
size_t class_RTOS_Driver_UART2::_queueSize = _UART2_QUEUE_SIZE; // or whatever appropriate value
// class_RTOS_Driver_UART2 driver_uart2(_UART2_TXD_PIN, _UART2_RXD_PIN, _UART2_BAUD_RATE, _UART2_QUEUE_LENGTH, _UART2_QUEUE_SIZE);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class_RTOS_Driver_UART2::class_RTOS_Driver_UART2(gpio_num_t txPin,
                                                 gpio_num_t rxPin,
                                                 int baudRate,
                                                 size_t queueLength,
                                                 size_t queueSize)
{
  _txPin = txPin;
  _rxPin = rxPin;
  _baudRate = baudRate;
  _queueLength = queueLength;
  _queueSize = queueSize;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_RTOS_Driver_UART2::init(void)
{
  Serial.begin(115200); // Initialize serial communication
  const uart_config_t uart2Config = {
      .baud_rate = _baudRate,                // Configure UART baud rate
      .data_bits = UART_DATA_8_BITS,         // Configure data bits
      .parity = UART_PARITY_DISABLE,         // Disable parity
      .stop_bits = UART_STOP_BITS_1,         // Configure stop bits
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // Disable hardware flow control
  };

  uart_param_config(UART_NUM_2, &uart2Config);                                      // Set UART parameters
  uart_set_pin(UART_NUM_2, _txPin, _rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); // Set UART pin configuration
  uart_driver_install(UART_NUM_2, _queueSize /*_RX0_BUF_SIZE*/, _queueSize /*_TX0_BUF_SIZE*/, 0, NULL, 0);
  // Install UART driver with buffers
  driver_uart2_queue = xQueueCreate(_queueLength, _queueSize);

  xTaskCreatePinnedToCore(class_RTOS_Driver_UART2::task, "UART2 Task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL, 0); // Create UART2 task
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Task to handle UART2 data reading
void class_RTOS_Driver_UART2::task(void *parameter)
{
  char data[_queueSize]; // Buffer to store received data
  while (1)
  {
    // Read data from UART
    const int rxBytes = uart_read_bytes(UART_NUM_2, data, _queueSize /*_RX0_BUF_SIZE*/, 1 / portTICK_RATE_MS); // 1ms for waiting
    if (rxBytes > 0)
    {
      data[rxBytes] = '\0'; // Null-terminate the received data
      // Serial.println(data);
      //  Send the data to the queue
      if (xQueueSend(driver_uart2_queue, &data, 1 / portTICK_RATE_MS) != pdTRUE)
      {
        Serial.println("Failed to send data to queue");
      }
    }

    vTaskDelay(500 / portTICK_PERIOD_MS); // Delay before reading next data
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_RTOS_Driver_UART2::read(char *data)
{
  if (xQueueReceive(driver_uart2_queue, data, 1 / portTICK_RATE_MS) == pdTRUE)
  { // Check if data is received from the UART queue
    // If data is received, print it
    // Serial.print("Received= ");
    // Serial.println(data);
    return 1;
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_RTOS_Driver_UART2::read(uint8_t *data)
{
  if (xQueueReceive(driver_uart2_queue, data, 1 / portTICK_RATE_MS) == pdTRUE)
  { // Check if data is received from the UART queue
    // If data is received, print it
    // Serial.print("Received= "+String(data));
    return 1;
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
