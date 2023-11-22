/*
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define  _WEBSERVER_PORT    80

AsyncWebServer server(_WEBSERVER_PORT);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_RestAPI::init() {

  server.on("/api/post", HTTP_POST, handlePost);
  server.begin();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handlePost(AsyncWebServerRequest *request) {
  // Handling POST request
  if (request->contentType() == "application/json") {
    String jsonPayload = request->getString();
    Serial.println("Received JSON: " + jsonPayload);

    // Process payload 

    request->send(200, "application/json", "Received JSON: " + jsonPayload);
  } else {
    request->send(400, "text/plain", "Invalid content type");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StaticJsonDocument<250> jsonDocument;
char buffer[250];
float temperature;
float humidity;
float pressure;
 

//   WiFi.status();
//   WiFi.localIP()

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>


const int frequency = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;





void getTemperature() {
  Serial.println("Get temperature");
  create_json("temperature", temperature, "°C");
  server.send(200, "application/json", buffer);
}


void setup_routing() {
    //server.on("/ReportRelay", getTemperature);     
    server.on("/temperature", getTemperature);
  server.on("/led", HTTP_POST, handlePost);    
          
  server.begin();    
}
 
void create_json(char *tag, float value, char *unit) {  
  jsonDocument.clear();  
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);
}
 
void add_json_object(char *tag, float value, char *unit) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["type"] = tag;
  obj["value"] = value;
  obj["unit"] = unit; 
}


 
 
void getData() {
  Serial.println("Get BME280 Sensor Data");
  jsonDocument.clear();
  add_json_object("temperature", temperature, "°C");
  add_json_object("humidity", humidity, "%");
  add_json_object("pressure", pressure, "hPa");
  serializeJson(jsonDocument, buffer);
  server.send(200, "application/json", buffer);
}


void handlePost() {
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  int red_value = jsonDocument["red"];
  int green_value = jsonDocument["green"];
  int blue_value = jsonDocument["blue"];

  ledcWrite(redChannel, red_value);
  ledcWrite(greenChannel,green_value);
  ledcWrite(blueChannel, blue_value);

  server.send(200, "application/json", "{}");
}


void setup_task() {
  xTaskCreate(     
  read_sensor_data,      
  "Read sensor data",      
  1000,      
  NULL,      
  1,     
  NULL     
  );     
}



void setup() {
    WiFi_init();
    Serial.print("Connected! IP Address: ");
    Serial.println(WiFi.localIP());
    setup_routing();
}


// tast1
void read_sensor_data(void * parameter) {
   for (;;) {
     temperature = bme.readTemperature();
     Serial.println("Read sensor data");
     vTaskDelay(600 / portTICK_PERIOD_MS);
   }
}


// tast2
void loop() {    
  server.handleClient();     
}

*/