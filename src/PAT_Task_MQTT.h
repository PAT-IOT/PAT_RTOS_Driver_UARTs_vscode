#ifndef __PAT_Task_MQTT_h__
#define __PAT_Task_MQTT_h__
#include "PAT_JSON.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WiFi_Init(void);
void WiFi_PrintStatus(void);

bool pingServer();
void task_ping(void);
void onMqttMessage(const String& topic, const String& payload, const size_t size);
void task_MQTT(void);  
int Ethernet_Init(void);

class class_MQTT : public class_JSON
{
public:

  int init(void);
  //static void callback_topics(const char *topic, const char *payload, size_t length);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






#endif  // __PAT_Task_WebServer_h__