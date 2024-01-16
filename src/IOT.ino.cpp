# 1 "C:\\Users\\MAEE8~1.SOH\\AppData\\Local\\Temp\\tmp0t0ajdpu"
#include <Arduino.h>
# 1 "D:/01-PAT_Project/02-Wireless IoT Controller/02-Code/ver2.0/IOT_Controller/src/IOT.ino"
# 52 "D:/01-PAT_Project/02-Wireless IoT Controller/02-Code/ver2.0/IOT_Controller/src/IOT.ino"
#include <SPI.h>
#include <Ethernet2.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 88, 177);
char server[] = "www.google.com";

EthernetClient client;
void setup();
void loop();
#line 61 "D:/01-PAT_Project/02-Wireless IoT Controller/02-Code/ver2.0/IOT_Controller/src/IOT.ino"
void setup() {
  Serial.begin(115200);
  Ethernet.init(5);
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