#ifndef _PAT_Application_H
#define _PAT_Application_H
#include "PAT_Prototype.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tast_leds(void);
void tast_leds2(void);
void task_MQTT(void);
void task_RTC(void);
void task_WebServer(void);
int  task_run_weeklySchedule(void);
void task_MCU_Received(void);
void task_MCU_Send(void);
void task_NRF24_Received(void);


void buf_to_JSON_reportRelay(void);
void JSON_to_buf_weeklySchedule(void);
void JSON_to_buf_setDateTime(void);
void JSON_to_buf_actionRelay(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // _PAT_Application_H
