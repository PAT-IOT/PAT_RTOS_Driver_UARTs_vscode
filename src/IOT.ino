#include <Arduino.h>
#include "WiFi.h"
#include "lib/PAT_Debug.h"
#include "lib/PAT_Configuration.h"
/*#include "PAT_RTC.h"
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


//   //while (!PSRamFS.begin())
//  while (!psramInit())
//   {
//     Serial.println("Failed to mount PSRamFS");
//       delay(1000);
//   }  
//    Serial.println("PSRamFS mounted successfully");
 
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
*/
#include <Ethernet.h>
#include <WebSocketsClient.h>  // include before MQTTPubSubClient.h
#include <MQTTPubSubClient.h>

uint8_t mac[] = {0xA0, 0xB7, 0x65, 0x4E, 0xD1, 0xA4}; 
const IPAddress ip(_WEBSOCKET_SERVER_IP_ARRAY);

WebSocketsClient client;
MQTTPubSubClient mqtt;

void connect() {
connect_to_host:
    Serial.println("connecting to host...");
    client.disconnect();
    client.begin(_WEBSOCKET_SERVER_IP, _WEBSOCKET_PORT, _SEPARATOR_PATH, _URL_PATH);  // "mqtt" is required
    client.setReconnectInterval(2000);
    mqtt.begin(client);  
    Serial.print("connecting to mqtt broker...");
    while (!mqtt.connect(_CLIENT_NAME, _USERNAME_SERVER, _PASSWORD_SERVER))
    {
        Serial.print(".");
        delay(1000);
        if (!client.isConnected()) {
            Serial.println("WebSocketsClient disconnected");
            goto connect_to_host;
        }
    }
    Serial.println(" connected!");
}

void setup() {
    Serial.begin(115200);
    Ethernet.begin(mac, ip);

    
    // initialize mqtt client
    client.begin(_WEBSOCKET_SERVER_IP, _WEBSOCKET_PORT, _SEPARATOR_PATH, _URL_PATH);  // "mqtt" is required
      client.setReconnectInterval(2000);
    mqtt.begin(client);

    // subscribe callback which is called when every packet has come
    mqtt.subscribe([](const String& topic, const String& payload, const size_t size) {
        Serial.println("mqtt received: " + topic + " - " + payload);
    });

    // subscribe topic and callback which is called when /hello has come
    mqtt.subscribe(_TOPIC1, [](const String& payload, const size_t size) {
        Serial.print(_TOPIC1);
        Serial.println(payload);
    });

    connect();
}

void loop() {
    mqtt.update();  // should be called

    if (!mqtt.isConnected()) {
        connect();
    }

    // publish message
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 1000) {
        prev_ms = millis();
        mqtt.publish("/hello", "world");
    }
}


