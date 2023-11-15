#include <Arduino.h>
#include <Preferences.h>
//#include "lib/PAT_Debug.h"
#include "lib/PAT_Configuration.h"
#include <WebSocketsClient.h>
#include <MQTTPubSubClient.h>
#include "PAT_JSON.h"
#include <ArduinoJson.h>
#include "PAT_Task_MQTT.h"
#include <WiFiClient.h>
//#include <ESP32Ping.h>
//#include "PAT_PCB_HAL.h"
//#include "PAT_Memory.h"
//#include "PAT_Tasks_OS.h"
// #include "PAT_Task_MCU.h"
// #include "PAT_Task_WebServer.h"
// #include "PAT_Task_PushButton.h"
#define delay_ms(xxx)       vTaskDelay( xxx / portTICK_PERIOD_MS);

const uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const int espNowChannel = 1;
bool espNowInitSuccess = false;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void loop()
{
  unsigned long currentMillis = millis();

  if (wifiConnected && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (!Ping.ping(remote_ip)) {
      Serial.println("Ping failed, reconnecting to WiFi...");
      WiFi.disconnect();
      delay(1000);
      WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Reconnecting to WiFi...");
      }
      Serial.println("Reconnected to WiFi");
    }
  }
}*/



//const IPAddress remote_ip(_WEBSOCKET_SERVER_IP_ARRAY); //_WEBSOCKET_PORT

const char* serverIP = _WEBSOCKET_SERVER_IP;
const int serverPort = _WEBSOCKET_PORT;
const long timeout = 10; // Timeout in seconds






extern class_JSON JSONx;
extern class_JSON JSON1_action_relay;
extern class_JSON JSON1_report_relay;
extern class_JSON JSON1_weeklySchedule;
extern class_JSON JSON1_setDateTime;

extern const char*	_WIFI_SSID[];
extern const char* _WIFI_PASSWORD[];



WebSocketsClient webSocket;
MQTTPubSubClient mqttClient;    //MQTTPubSub::PubSubClient<256> mqttClient;
class_MQTT MQTT;

//___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task___task
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define MQTT broker connection parameters
/*
const char* brokerAddress = "192.168.1.10";
const char* topic = "esp32/status";

// Define server IP and port for pinging
const char* serverIP = "195.248.240.222";
const int serverPort = 9001;
const long timeout = 1; // Timeout in seconds

WiFiClient webSocket;
PubSubClient mqttClient(webSocket);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected");

  // Connect to MQTT broker
  mqttClient.setServer(brokerAddress, 1883);
  while (!mqttClient.connected()) {
    Serial.print(".");
    delay(1000);
    if (!mqttClient.connect("ESP32Client")) {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      delay(5000);
    }
  }
  Serial.println("Connected to MQTT broker");

  // Subscribe to the specified topic
  mqttClient.subscribe(topic);
}

void loop() {
  // Handle incoming MQTT messages
  if (mqttClient.available()) {
    while (mqttClient.available()) {
      char buffer[256];
      int bytesRead = mqttClient.readBytesUntil('\n', buffer, sizeof(buffer));
      buffer[bytesRead - 1] = '\0';
      Serial.print("Received message: ");
      Serial.println(buffer);
    }
  }

  // Ping the server to check if it's responding
  if (pingServer()) {
    Serial.println("Server is responding to pings.");
    // Publish a message to the MQTT topic indicating server responsiveness
    mqttClient.publish(topic, "Server is responding to pings.");
  } else {
    Serial.println("Server is not responding to pings.");
    // Publish a message to the MQTT topic indicating server unresponsiveness
    mqttClient.publish(topic, "Server is not responding to pings.");
  }

  // Yield to allow other tasks to run
  mqttClient.loop();
  delay(10000); // Wait for 10 seconds before pinging again
}*/

bool pingServer() {
  WiFiClient webSocket;
  // Try to connect to the server
  if (webSocket.connect(serverIP, serverPort)) {
    // Send a ping message to the server
    webSocket.write("ping");

    // Wait for the response
    long start = millis();
    while (!webSocket.available() && millis() - start < timeout * 1000) {
      delay_ms(100);
    }

    // Check if the response is the expected "pong" message
    if (webSocket.available()) {
      char buffer[1024];
      int bytesRead = webSocket.readBytesUntil('\n', buffer, sizeof(buffer));
      if (bytesRead > 0 && strcmp(buffer, "pong\n") == 0) {
        // Server responded to ping
        webSocket.stop();
        return true;
      } else {
        // Invalid response from server
        webSocket.stop();
        return false;
      }
    } else {
      // Timeout occurred
      webSocket.stop();
      return false;
    }
  } else {
    // Failed to connect to server
    return false;
  }
}









/*
bool pingServer() {

   WiFiClient client;
  // Try to connect to the server
  if (client.connect(serverIP, serverPort)) {
    // Send a ping message to the server
    client.write("ping");

    // Wait for the response
    long start = millis();
    while (!client.available() && millis() - start < timeout * 1000) {
      delay_ms(100);
    }

    // Check if the response is the expected "pong" message
    if (client.available()) {
      char buffer[1024];
      int bytesRead = client.readBytesUntil('\n', buffer, sizeof(buffer));
      if (bytesRead > 0 && strcmp(buffer, "pong\n") == 0) {
        // Server responded to ping
        client.stop();
        return true;
      } else {
        // Invalid response from server
        client.stop();
        return false;
      }
    } else {
      // Timeout occurred
      client.stop();
      return false;
    }
  } else {
    // Failed to connect to server
    return false;
  }
}
*/


void task_ping(void) {
  while (WiFi.status() == WL_CONNECTED)
  {
    if (pingServer())
    {
          Serial.println("IOT Controller is connected to the server ok ok ok ok ok ok  ok ok ok ok ok ok  ok ok ok ok ok ok ");
    }
    else
    {
      Serial.println("Failed to connect to server-----------------------------------------------------------------------------");
    }
  }
}


void task_MQTT(void) {
  mqttClient.update();  // should be called
  if (!mqttClient.isConnected() || (WiFi.status() != WL_CONNECTED) /*|| (!Ping.ping(remote_ip))*/) MQTT.init();
  WiFi_PrintStatus();
  //----------------------------------------------------
  if (JSON1_action_relay.payloadFlag){
      implement_action_relay(); 
      JSON1_action_relay.payloadFlag=0;
  }
  if (JSON1_report_relay.payloadFlag){
      implement_report_relay();
      JSON1_report_relay.payloadFlag=0;
  }
  if (JSON1_weeklySchedule.payloadFlag){
      weeklySchedulePutToStruct();
      JSON1_weeklySchedule.payloadFlag=0;
  }
  if (JSON1_setDateTime.payloadFlag){
      implement_setDateTime();
      JSON1_setDateTime.payloadFlag=0;
  }
    //----------------------------------------------------
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void onMqttMessage(const String &topic, const String &payload, const size_t size) {
   
    if (JSONx.putTemporary(payload)) {
    //----------------------------------------------------
    if (JSON1_action_relay.topic.equals(topic)&&
        JSON1_action_relay.key.equals(JSONx.dB["type"].as<String>())) 
                {
                  JSON1_action_relay.submit(payload);

                }
    //----------------------------------------------------
    else if ( JSON1_report_relay.topic.equals(topic)&&
              JSON1_report_relay.key.equals(JSONx.dB["type"].as<String>())) 
                {
                  JSON1_report_relay.submit(payload);
                }
    //----------------------------------------------------
    else if ( JSON1_weeklySchedule.topic.equals(topic)&&
              JSON1_weeklySchedule.key.equals(JSONx.dB["type"].as<String>())) 
                {
                  JSON1_weeklySchedule.submit(payload);
                }
    //----------------------------------------------------
    else if ( JSON1_setDateTime.topic.equals(topic)&&
              JSON1_setDateTime.key.equals(JSONx.dB["type"].as<String>())) 
                {
                  JSON1_setDateTime.submit(payload);
                }

  }
      //----------------------------------------------------
  };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void espNowHandler(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
// Handle data received via ESP-NOW and forward it to MQTT
  if (client.connected()) {
    String topic = "espnow_data";
    client.publish(topic, data, data_len);
  }
}
int ESPNOW_init(void) {

  if (esp_now_init() == ESP_OK) {
    esp_now_register_recv_cb(espNowHandler);
    esp_now_set_pmk((uint8_t *)password, 32);
    esp_now_add_peer(gatewayAddress, ESP_NOW_ROLE_COMBO, 0, NULL, 0);
    return 1;
  }
  Serial.println("Failed to initialize ESP-NOW");
   return 0;
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_MQTT::init(void) {
    if(WiFi_Init()==WL_CONNECTED) {
      Serial.print("MQTT ...");
      webSocket.begin(_WEBSOCKET_SERVER_IP, _WEBSOCKET_PORT, _SEPARATOR_PATH, _URL_PATH); //webSocket.isConnected()
      webSocket.setReconnectInterval(2000);
      mqttClient.begin(webSocket);  
      fori(5){
              if (mqttClient.connect(_CLIENT_NAME, _USERNAME_SERVER, _PASSWORD_SERVER)) { 
                            mqttClient.subscribe  (_TOPIC1, [](const String &payload, const size_t size){}); 
                            mqttClient.subscribe  (_TOPIC2, [](const String &payload, const size_t size){}); 
                            mqttClient.subscribe  (_TOPIC3, [](const String &payload, const size_t size){}); 
                            mqttClient.subscribe([](const String &topic, const String &payload, const size_t size){  
                                                 onMqttMessage(topic, payload, size); 
                                                 });
                            Serial.println(" connected");
                            return 1;
                            }
          Serial.print(". ");
           delay_ms(1000);
      }
    }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WiFi_Init(void) {
  Serial.print(F("Connecting to .... "));
 fori(_NUMBER_OF_SSID){
   forj(5){
          Serial.print(" SSID["+String(i)+"] ");
          WiFi.begin(_WIFI_SSID[i], _WIFI_PASSWORD[i]);
           delay_ms(1000); //this is a delay to wait for the connection to be established dont remove this line
          if (WiFi.status() == WL_CONNECTED) {
                                                                            Serial.println("connected"); 
                                                                            return WiFi.status();
                                                                           }
          }
 }
  Serial.println(" Failed to connect"); 
  WiFi_PrintStatus();
  return WiFi.status() ;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WiFi_PrintStatus() {
  Serial.print(F("IP= "));
  Serial.println(WiFi.localIP());
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());
  int32_t rssi = WiFi.RSSI();
  Serial.print(F("RSSI: "));
  Serial.println(String(rssi) + F(" dBm"));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*int class_MQTT::init(void) {
    if(WiFi_Init()==WL_CONNECTED) {
      Serial.println("MQTT ... ");
      webSocket.begin(_WEBSOCKET_SERVER_IP, _WEBSOCKET_PORT, _SEPARATOR_PATH, _URL_PATH); //webSocket.isConnected()
      webSocket.setReconnectInterval(2000);
      mqttClient.begin(webSocket);  
      fori(5){
              if (mqttClient.connect(_CLIENT_NAME, _USERNAME_SERVER, _PASSWORD_SERVER)) { 
                            mqttClient.subscribe  (_TOPIC1, [](const String &payload, const size_t size){}); 
                            mqttClient.subscribe  (_TOPIC2, [](const String &payload, const size_t size){}); 
                            mqttClient.subscribe  (_TOPIC3, [](const String &payload, const size_t size){}); 
                            mqttClient.subscribe([](const String &topic, const String &payload, const size_t size){  
                                                 onMqttMessage(topic, payload, size); 
                                                 });
                            Serial.print(" connected");
                            return 1;
                            }
          Serial.print(". ");
          delay(1000);
      }
    }
  return 0;
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*int WiFi_Init(void) {
  Serial.print(F("Connecting to .... "));
 fori(_NUMBER_OF_SSID){
   forj(5){
          Serial.print(" SSID["+String(i)+"] ");
          WiFi.begin(_WIFI_SSID[i], _WIFI_PASSWORD[i]);
          delay(1000); //this is a delay to wait for the connection to be established dont remove this line
          if (WiFi.status() == WL_CONNECTED) {
                                                                            Serial.println("connected"); 
                                                                            return WiFi.status();
                                                                           }
          }
 }
  Serial.println(" Failed to connect"); 
  WiFi_PrintStatus();
  return WiFi.status() ;
}*/                                              
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

