 
#include "PAT_Prototype.h"
#include <Arduino.h>
#include "WiFi.h"
#include "SPIFFS.h"
#include <PAT_Memory.h>
#include "PAT_Task_WebServer.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  
  Serial.begin(250000);
  while (!Serial);
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.flush();
  //esp.resetReason();
  //esp.wdg_init(15000);
  NRF.init();
  RTC.init();
  MCU.init();
  
  pushButton_WebServer.init();
  pushButton_ResetPassword.init();
  led_wifi.init();
  led_nrf.init();
  

  if (!file_class_UserBuffer.load(ubuf))
  {
    if (!file_class_UserBuffer.load(ubuf))
    {
      file_class_UserBuffer.save(ubuf);
    }
  }
  
  task_run_weeklySchedule();
  task_MCU_Send();
  webServerInit();
  //enableLoopWDT();
  tasks_OS_Init();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {    
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    










/* //is working
#include <SPI.h>
#include "PAT_Ethernet.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 88, 21);
char server[] = "www.google.com";

EthernetClient client;

void setup() {
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  digitalWrite(4,HIGH);
  Ethernet.init(5);
  delay(1000);
  Ethernet.begin(mac, ip);
  delay(1000);

  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for (;;)
      ;
  }
}
*/


/*
#include "PAT_Ethernet.h"
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




/* // this code is ok
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");

  RTC.init();
  MCU.init();
  ubuf.load("relay");
  delay(100);

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  File file = SPIFFS.open("/text.txt");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
  tasks_OS_Init();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
*/



/* // this code is ok
#include "PAT_Prototype.h"

#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "PAT_IOT";
const char* password = "PAT_IOT123";

// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
*/