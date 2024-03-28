#ifndef PAT_RTOS_DERIVER_H
#define PAT_RTOS_DERIVER_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//____________________________________________________________________  USER  CONFIG  ________________________________________________________________________
// default configuration
#define RTOS_INSTALL_UART0
//#define RTOS_INSTALL_UART1
#define RTOS_INSTALL_UART2

// #define RTOS_INSTALL_SPI0
// #define RTOS_INSTALL_SPI1
// #define RTOS_INSTALL_SPI2
// #define RTOS_INSTALL_SPI3

// #define RTOS_INSTALL_I2C0
// #define RTOS_INSTALL_I2C1
// #define RTOS_INSTALL_I2C2
// #define RTOS_INSTALL_I2C3

//____________________________________________________________________  USER  CONFIG  ________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef RTOS_INSTALL_UART0
#include "PAT_RTOS_Driver_UART0.h" // Include custom UART driver header file
#endif
#ifdef RTOS_INSTALL_UART1
#include "PAT_RTOS_Driver_UART1.h" // Include custom UART driver header file
#endif
#ifdef RTOS_INSTALL_UART2
#include "PAT_RTOS_Driver_UART2.h" // Include custom UART driver header file
#endif
//-----------------------------------------------------------------------------
class class_RTOS_Driver
{
private:
public:
  class_RTOS_Driver();

#ifdef RTOS_INSTALL_UART0
  class_RTOS_Driver_UART0 uart0;
#endif
#ifdef RTOS_INSTALL_UART1
  class_RTOS_Driver_UART1 uart1;
#endif
#ifdef RTOS_INSTALL_UART2
  class_RTOS_Driver_UART2 uart2;
#endif
  void init(void);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // PAT_RTOS_UART0_H
