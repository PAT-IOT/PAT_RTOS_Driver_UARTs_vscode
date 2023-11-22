#ifndef PAT_PROTOTYPE_H
#define PAT_PROTOTYPE_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <PAT_Debug.h>
#include <PAT_Configuration.h>
#include <PAT_Relay.h>
#include "WiFi.h"
#include <PAT_RTC.h>
#include "PAT_Tasks_OS.h"
#include "PAT_Task_MCU.h"
#include "PAT_Task_MQTT.h"
#include "PAT_JSON.h"
#include "PAT_Task_MCU.h"
#include "esp_system.h"
//-------------------------------------------------------------
//extern class_Array< 1, 4, class_Relay > relay;
extern class_Relay relay[];
extern class_MQTT MQTT;
extern class_RTC RTC;
extern class_MCU MCU;
extern String _CHIP_SERIAL_NUMBER;
extern class_UserBuffer ubuf;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ArduinoJson.h>
//#include <PSRamFS.h>
#include "PAT_JSON.h"
#include <PAT_Relay.h>
#include "PAT_Task_MCU.h"
#include <PAT_Configuration.h>
#include <PAT_RTC.h>
#include <vector>  // Include for std::vector
#include <map>  
//-------------------------------------------------------------
//extern class_Array< 1, 4, class_Relay > relay;
extern class_Relay relay[];
extern class_MCU MCU;
extern String _CHIP_SERIAL_NUMBER;
extern class_RTC RTC;
//StaticJsonDocument<4096> class_JSON::vdoc;
//-------------------------------------------------------------
#include <Arduino.h>
//#include <PSRamFS.h>
#include <PAT_Memory.h>
#include <ArduinoJson.h>
#include <vector>  // Include for std::vector
#include <map>  
//#include "esp_heap.h"
//-------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern class_MCU MCU; // Use the UART2
extern class_UserBuffer ubuf;
extern class_RTC RTC;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "PAT_Tasks_OS.h"
#include "PAT_Task_MCU.h"
#include "PAT_Task_MQTT.h"
#include "PAT_Task_WebServer.h"
#include <PAT_RTC.h>
#include <PAT_Relay.h>
#include <PAT_Debug.h>
#include "PAT_Application.h"



#include <Arduino.h>
#include <Preferences.h>
//#include <PAT_Debug.h>
#include <PAT_Configuration.h>
#include <WebSocketsClient.h>
#include <MQTTPubSubClient.h>
#include "PAT_JSON.h"
#include <ArduinoJson.h>
#include "PAT_Task_MQTT.h"
#include <WiFiClient.h>
#include "PAT_Prototype.h"


#define delay_OS(xxx) vTaskDelay(xxx / portTICK_PERIOD_MS);

extern class_weeklySchedule weeklySchedule;


extern class_JSON JSONx;
extern class_JSON JSON1_action_relay;
extern class_JSON JSON1_report_relay;
extern class_JSON JSON1_weeklySchedule;
extern class_JSON JSON1_setDateTime;

extern const char*	_WIFI_SSID[];
extern const char* _WIFI_PASSWORD[];

extern WebSocketsClient webSocket;
extern MQTTPubSubClient mqttClient;    //MQTTPubSub::PubSubClient<256> mqttClient;
extern class_MQTT MQTT;


#define _RELAY_NUMBER 12




#endif  // PAT_PROTOTYPE_H
