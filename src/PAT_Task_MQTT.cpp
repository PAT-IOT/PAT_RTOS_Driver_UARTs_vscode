#include "PAT_Prototype.h"
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WebSocketsClient  webSocket;
MQTTPubSubClient  mqttClient;    //MQTTPubSub::PubSubClient<256> mqttClient;
//PubSubClient       mqttClient;    //MQTTPubSub::PubSubClient<256> mqttClient;
class_MQTT        MQTT;


// EthernetClient EthClient;
// WebSocketsClient EthwebSocket;
// MQTTPubSubClient EthmqttClient;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void onMqttMessage(const String &topic, const String &payload, const size_t size) {
  static boolean firstBoot= true;
  if (firstBoot)
  {
    firstBoot = false;
  }
  else if (JSONx.putTemporary(payload))
    {
      //----------------------------------------------------
      if (JSON1_actionRelay.topic.equals(topic) &&
        JSON1_actionRelay.key.equals(JSONx.dB["type"].as<String>()))
      {
        JSON1_actionRelay.submit(payload);

      }
      //----------------------------------------------------
      else if (JSON1_reportRelay.topic.equals(topic) &&
        JSON1_reportRelay.key.equals(JSONx.dB["type"].as<String>()))
      {
        JSON1_reportRelay.submit(payload);
      }
      //----------------------------------------------------
      else if (JSON1_weeklySchedule.topic.equals(topic) &&
        JSON1_weeklySchedule.key.equals(JSONx.dB["type"].as<String>()))
      {
        JSON1_weeklySchedule.submit(payload);
      }
      //----------------------------------------------------
      else if (JSON1_setDateTime.topic.equals(topic) &&
        JSON1_setDateTime.key.equals(JSONx.dB["type"].as<String>()))
      {
        JSON1_setDateTime.submit(payload);
      }
      else
      {
        JSONx.dB.clear();
      }
    }
      //----------------------------------------------------
  };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_MQTT::init(void) {
  //  if (Eth_connected())
  // {
  // //if(Eth_Init()) {
  // Serial.print("MQTT ...");
  //     EthwebSocket.begin(_WEBSOCKET_SERVER_IP, _WEBSOCKET_PORT, _SEPARATOR_PATH, _URL_PATH); //webSocket.isConnected()
  //     EthwebSocket.setReconnectInterval(2000);
      
  //     EthmqttClient.begin(EthwebSocket);
  //     fori(5){
  //             if (EthmqttClient.connect(_CLIENT_NAME, _USERNAME_SERVER, _PASSWORD_SERVER)) { 
  //                             EthmqttClient.subscribe(_TOPIC1, [](const String& payload, const size_t size) {onMqttMessage(_TOPIC1, payload, size); });
  //                           // EthmqttClient.subscribe  (_TOPIC2, [](const String &payload, const size_t size){          }); 
  //                           // EthmqttClient.subscribe  (_TOPIC3, [](const String &payload, const size_t size){          }); 
  //                           // EthmqttClient.subscribe([](const String &topic, const String &payload, const size_t size){ onMqttMessage(topic, payload, size); });
  //                           Serial.println(" MQTT was connected");
  //                           return 1;
  //                           }
  //         Serial.print(". ");
  //          delay_OS(1000);
  //     }
  //  }
  //  else
  //  {
  //   EthmqttClient.disconnect();
  //   Eth_Init();
  //  }
  if (WiFi.status() == WL_CONNECTED)
  {
  //if(Eth_Init()) {
  Serial.print("MQTT ...");
      webSocket.begin(_WEBSOCKET_SERVER_IP, _WEBSOCKET_PORT, _SEPARATOR_PATH, _URL_PATH); //webSocket.isConnected()
      webSocket.setReconnectInterval(2000);
      mqttClient.begin(webSocket);  
      fori(5){
        if (mqttClient.connect(_CLIENT_NAME, _USERNAME_SERVER, _PASSWORD_SERVER))
        {
          // const String& payload
                              mqttClient.subscribe(_TOPIC1, [](const String& payload, const size_t size) {onMqttMessage(_TOPIC1, payload, size); });
                            // mqttClient.subscribe  (_TOPIC2, [](const String &payload, const size_t size){          }); 
                            // mqttClient.subscribe  (_TOPIC3, [](const String &payload, const size_t size){          }); 
                            // mqttClient.subscribe([](const String &topic, const String &payload, const size_t size){ onMqttMessage(topic, payload, size); });
                            Serial.println(" MQTT was connected"); 
                            return 1;
                            }
          Serial.print(". ");
           delay_OS(1000);
      }
   }
   else
   {
    mqttClient.disconnect();
    mqttClient.clearWill();
    WiFi_Init();
   }
   return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_MQTT::erase(void) {
  mqttClient.clearWill();
  memset(&webSocket, 0, sizeof(WebSocketsClient));
  memset(&mqttClient, 0, sizeof(MQTTPubSubClient));
  memset(&WiFi, 0, sizeof(WiFi));
  Serial.println("Classes were Erased");
  // WebSocketsClient* pwebSocket;
  // MQTTPubSubClient* pmqttClient;
  // pwebSocket = &webSocket;
  // pmqttClient = &mqttClient;
  // memset(*pwebSocket, 0, sizeof(webSocket));
  // memset(*pmqttClient, 0, sizeof(mqttClient));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




