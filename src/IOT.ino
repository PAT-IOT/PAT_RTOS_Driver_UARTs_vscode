#include "PAT_Prototype.h"




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
    delay(1000);
  Serial.println();
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
  ubuf.load("relay");
  delay(1000);

  tasks_OS_Init();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
/*
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

*/





