#include <ArduinoJson.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <Wire.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// NTP settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0;

// Maximum number of channels (adjust as needed)
const int maxChannels = 48;

// Pin numbers for relay control
int relayPins[maxChannels] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

// Initialize NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  timeClient.begin();

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Update time from NTP server
  timeClient.update();

  // Current day and time
  String today = timeClient.getFormattedDate();
  String currentTime = timeClient.getFormattedTime();

  // Your JSON data
  const char* json = R"({
  "type": "weeklySchedule",
  "device": {
    "serialNumber": "ed4578798675as4465",
  },
  "schedule": {
    "monday": [
      {"time": "08:50:00", "value": "on", "channels": [18, 19, 36]},
      {"time": "10:30:00", "value": "off", "channels": [18]},
      {"time": "11:15:00", "value": "on", "channels": [18]}
    ],
    "tuesday": [
      {"time": "08:15:00", "value": "on", "channels": [18, 19, 36, 42]},
      {"time": "10:45:00", "value": "off", "channels": [18, 36]},
      {"time": "11:30:00", "value": "on", "channels": [19, 44]}
    ],
    "wednesday": [
      {"time": "09:00:00", "value": "on", "channels": [18, 19]},
      {"time": "10:45:00", "value": "off", "channels": [19, 36]},
      {"time": "12:00:00", "value": "on", "channels": [36, 42]}
    ],
    "thursday": [
      {"time": "08:50:00", "value": "on", "channels": [18, 36, 44]},
      {"time": "11:45:00", "value": "off", "channels": [18, 36, 44]},
      {"time": "13:30:00", "value": "on", "channels": [18, 19, 36]}
    ],
    "friday": [
      {"time": "09:30:00", "value": "on", "channels": [18, 19, 44]},
      {"time": "11:15:00", "value": "off", "channels": [18]},
      {"time": "12:45:00", "value": "on", "channels": [18, 19, 36]}
    ],
    "saturday": [
      {"time": "08:30:00", "value": "on", "channels": [19, 36]},
      {"time": "10:15:00", "value": "off", "channels": [18, 19, 36, 42]},
      {"time": "11:30:00", "value": "off", "channels": [18, 36, 42]},
      {"time": "14:00:00", "value": "on", "channels": [18, 19, 36]}
    ],
    "sunday": [
      {"time": "08:45:00", "value": "on", "channels": [18, 19, 36, 42]},
      {"time": "10:45:00", "value": "off", "channels": [18, 42]},
      {"time": "11:45:00", "value": "on", "channels": [18, 36, 44]}
    ]
  }
})";

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract and apply schedules
  JsonObject schedules = doc["value"][today];
  if (!schedules.isNull()) {
    for (JsonVariant value : schedules) {
      String scheduleTime = value["time"];
      String scheduleValue = value["value"];

      if (currentTime == scheduleTime) {
        JsonArray channelArray = value["channels"];
        for (int i = 0; i < channelArray.size(); i++) {
          int channel = channelArray[i];
          if (channel >= 0 && channel < maxChannels) {
            if (scheduleValue == "on") {
              // Turn on relay for the specified channel
              digitalWrite(relayPins[channel], HIGH);
            } else if (scheduleValue == "off") {
              // Turn off relay for the specified channel
              digitalWrite(relayPins[channel], LOW);
            }
          }
        }
      }
    }
  }
}

void initializeRelayPins() {
  for (int i = 0; i < maxChannels; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);  // Initially, turn off all relays
  }
}
