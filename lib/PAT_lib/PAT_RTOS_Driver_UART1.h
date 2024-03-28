#ifndef PAT_RTOS_DERIVER_UART1_H
#define PAT_RTOS_DERIVER_UART1_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//____________________________________________________________________  USER  CONFIG  ________________________________________________________________________
// default configuration
#define default_UART1_BAUD_RATE 115200   // UART baud rate
#define default_UART1_QUEUE_LENGTH 10    // Length of UART1 queue
#define default_UART1_QUEUE_SIZE 128     // Size of UART1 queue
#define default_UART1_TXD_PIN GPIO_NUM_9 // Define TX pin for UART1
#define default_UART1_RXD_PIN GPIO_NUM_10 // Define RX pin for UART1
//____________________________________________________________________  USER  CONFIG  ________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>

const int _UART1_BAUD_RATE = default_UART1_BAUD_RATE;
const size_t _UART1_QUEUE_LENGTH = default_UART1_QUEUE_LENGTH;
const size_t _UART1_QUEUE_SIZE = default_UART1_QUEUE_SIZE;
const gpio_num_t _UART1_TXD_PIN = default_UART1_TXD_PIN;
const gpio_num_t _UART1_RXD_PIN = default_UART1_RXD_PIN;

//----------------------------------------------------------------------------------------
// // Static inline function to get environment variable value and convert it to integer
// static inline int getEnvInt(const char *varName, int defaultValue)
// {
//   const char *envValue = getenv(varName);
//   if (envValue != NULL)
//   {
//     return atoi(envValue);
//   }
//   return defaultValue; // Return default value if environment variable is not set
// }
// //----------------------------------------------------------------------------------------
// // Static inline function to get environment variable value and convert it to gpio_num_t
// static inline gpio_num_t getEnvGpio(const char *varName, gpio_num_t defaultValue)
// {
//   const char *envValue = getenv(varName);
//   if (envValue != NULL)
//   {
//     return static_cast<gpio_num_t>(atoi(envValue));
//   }
//   return defaultValue; // Return default value if environment variable is not set
// }
//----------------------------------------------------------------------------------------
// const int _UART1_BAUD_RATE =       getEnvInt("UART1_BAUD_RATE"   , default_UART1_BAUD_RATE);
// const size_t _UART1_QUEUE_LENGTH = getEnvInt("UART1_QUEUE_LENGTH", default_UART1_QUEUE_LENGTH);
// const size_t _UART1_QUEUE_SIZE =   getEnvInt("UART1_QUEUE_SIZE"  , default_UART1_QUEUE_SIZE);
// const gpio_num_t _UART1_TXD_PIN = getEnvGpio("UART1_TXD_PIN"   , default_UART1_TXD_PIN);
// const gpio_num_t _UART1_RXD_PIN = getEnvGpio("UART1_RXD_PIN"   , default_UART1_RXD_PIN);
//----------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_RTOS_Driver_UART1
{
private:
  gpio_num_t _txPin;
  gpio_num_t _rxPin;
  int _baudRate;
  size_t _queueLength;
  static size_t _queueSize;

public:
  // class_RTOS_Driver_UART1(gpio_num_t txPin, gpio_num_t rxPin, int baudRate, size_t queueLength, size_t queueSize);
  class_RTOS_Driver_UART1(gpio_num_t txPin = _UART1_TXD_PIN,
                          gpio_num_t rxPin = _UART1_RXD_PIN,
                          int baudRate = _UART1_BAUD_RATE,
                          size_t queueLength = _UART1_QUEUE_LENGTH,
                          size_t queueSize = _UART1_QUEUE_SIZE);

  void init(void);
  static void task(void *parameter);

  int read(char *data);
  int read(uint8_t *data);

  __inline size_t size(void)
  {
    return (size_t)_queueSize;
  }
  __inline size_t length(void)
  {
    return _queueLength;
  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // PAT_RTOS_UART1_H
