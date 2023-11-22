
/*

http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json
https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json



File> Preferences{
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json

}

///////////////////////////////////////////////////////////////////////////
----------------------------MQTT------------------------
link{
	install 

}
--------------
nesesory Library for installing{
downlod this link https:github.com/hideakitai/MQTTPubSubClient and install it.
note: dont install WebSocketsClient in arduino labrary 
 
 
ArxContainer
ArxTypeTraits



ArduinoJson by bemoit blabchon 
https://arduinojson.org/?utm_source=meta&utm_medium=library.properties

WebSockets

}
--------------
Related Library {

}
--------------
///////////////////////////////////////////////////////////////////////////
----------------------------JSON------------------------
link{
// https://arduinojson.org/v6/example/generator/
// https://arduinojson.org/v6/assistant
// https://arduinojson.org/book/
}
--------------
nesesory Library for installing{

}
--------------
Related Library {

}
--------------
///////////////////////////////////////////////////////////////////////////
----------------------------WebSerwer------------------------
link{

}
--------------
nesesory Library for installing{

}
--------------
Related Library {

}
--------------
///////////////////////////////////////////////////////////////////////////





*/



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



/*
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
}*/


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

/*
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
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
byte mac[] = {0xA0, 0xB7, 0x65, 0x4E, 0xD1, 0xA4}; 
int Ethernet_Init(void) {

  Serial.print(F("Ethernet Connecting to .... "));
  // Set ENC28J60 pins as OUTPUT
  pinMode(ENC28J60_SCK, OUTPUT);
  pinMode(ENC28J60_MOSI, OUTPUT);
  pinMode(ENC28J60_MISO, INPUT);
  pinMode(ENC28J60_CS, OUTPUT);
  // Set initial states
  digitalWrite(ENC28J60_CS, HIGH);
  // Initialize the Ethernet library
  if (UIPEthernet.begin(mac))
  {
  Serial.println(F("connected"));  
  IPAddress ip = UIPEthernet.localIP();  // Obtain and print IP address
  Serial.print("IP Address: ");
  Serial.println(ip);
  return 1;
  }
Serial.println(" Failed to connect");
return 0;
}*/

// const uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// const int espNowChannel = 1;
// bool espNowInitSuccess = false;
//const IPAddress remote_ip(_WEBSOCKET_SERVER_IP_ARRAY); //_WEBSOCKET_PORT
// const char* serverIP = _WEBSOCKET_SERVER_IP;
// const int serverPort = _WEBSOCKET_PORT;
// const long timeout = 10; // Timeout in seconds

//--------------------------------
    // Constructor implementation
  /*class_daySchedule& getDay(int dayIndex) {
    if (dayIndex < 0 || dayIndex >= 7) {
      throw std::out_of_range("Invalid day index");
    }
    return *day[dayIndex];
  }*/
/*
class WeeklyScheduleItem {
public:
    String time;
    String value;
    std::vector<int> channels;
};

class WeeklySchedule {
public:
    std::map<String, std::vector<WeeklyScheduleItem>> days;
};*/
  // class_JSON(const char* mytopic = "", const char* mykey = "", ptrImplementFuntion ptrfun = implementNull)
//     : topic(mytopic), key(mykey), ptrImplementFuntion(ptrfun) {
//         this->payloadFlag = 0;
//         this->payloadTemporaryFlag = 0;
//     }
/*
struct SpiRamAllocator {
    void* allocate(size_t size) {
      return ps_malloc(size);
      //return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
    }

    void deallocate(void* pointer) {
      free(pointer);
      //heap_caps_free(pointer);
    }
};
//SpiRamAllocator object_psram
using SpiRamJsonDocument = BasicJsonDocument<SpiRamAllocator>;
*/
  //EXT_RAM_ATTR uint8_t myVariable[2024];
  //SpiRamJsonDocument vdoc;
// class_JSON::class_JSON(const char* mytopic, const char* mykey)
//   : topic(mytopic),key(mykey) {
//   this->payloadFlag = 0;
// }
//  ubuf.relayA[relay_Index] = JSON1_action_relay.dB["mode"].as<JsonArray>()[relay_Index].as<int>();  ledcSetup(redChannel, frequency, resolution);
// ledcSetup(greenChannel, frequency, resolution);
// ledcAttachPin(green_pin, greenChannel);