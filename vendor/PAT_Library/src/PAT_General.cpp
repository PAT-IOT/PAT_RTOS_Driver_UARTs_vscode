#include <PAT_General.h>
#include "WiFi.h"
#include <PAT_Configuration.h>
#include "PAT_Ethernet.h"
#include <SPI.h>
////////////////////////////////////////////////////Config///////////////////////////////////////////////////////////////////////////////////
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 88, 21);
char server[] = "www.google.com";
//EthernetClient ethClient;
EthernetClient googleClient;
//////////////////////////////////////////////////////Config///////////////////////////////////////////////////////////////////////////////////
int Eth_Init(void) {
  pinMode(4, OUTPUT);
  digitalWrite(4,HIGH);
  Ethernet.init(5);
  delay(1000);
  Ethernet.begin(mac, ip);
  delay(1000);

  Serial.println("connecting...");
  if (googleClient.connect(server, 80))
  {
    Serial.println("connected");
      Serial.println(Ethernet.localIP());
    // googleClient.println("GET /search?q=arduino HTTP/1.1");
    // googleClient.println("Host: www.google.com");
    // googleClient.println("Connection: close");
    // googleClient.println();
    return 1;
  }
  else
  {
    Serial.println("connection failed");
  }
  return 0;
}
/////////////////////////////////////////////////Class Definitions/////////////////////////////////////////////////////////////////////////////
int Eth_connected(void) {
  if (googleClient.connect(server, 80))
  {
    Serial.println("connected");
      Serial.println(Ethernet.localIP());
    // googleClient.println("GET /search?q=arduino HTTP/1.1");
    // googleClient.println("Host: www.google.com");
    // googleClient.println("Connection: close");
    // googleClient.println();
    return 1;
  }
  else
  {
    Serial.println("connection failed");
  }
  return 0;
}


/////////////////////////////////////////////////Class Definitions/////////////////////////////////////////////////////////////////////////////
void Eth_update(void) {
  if (googleClient.available())
  {
    char c = googleClient.read();
    Serial.print(c);
  }

  if (!googleClient.connected())
  {
    Serial.println();
    Serial.println("disconnecting.");
    googleClient.stop();
    delay_OS(2000);
  }
}



/////////////////////////////////////////////////Class Definitions/////////////////////////////////////////////////////////////////////////////
#include "esp_system.h"

const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 10000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void ARDUINO_ISR_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void wtd_init() {
  pinMode(button, INPUT_PULLUP);                    //init control pin
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // // Get ESP32 chip ID
  // uint64_t chipId = ESP.getEfuseMac();
  // // Set the WiFi hostname with the chip ID
  // String deviceName = "ESP32-" + String((uint16_t)(chipId >> 32));
  // WiFi.setHostname(deviceName.c_str());


int WiFi_Init(void) {
  WiFi.disconnect();
  Serial.println(F("WiFi is Connecting to .... "));
  for(int i = 0; i < _NUMBER_OF_SSID; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      Serial.print(" SSID[" + String(i) + "] ");
      //WiFi.setAutoReconnect();
      WiFi.setHostname(_WIFI_HOST_NAME);
      tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, _WIFI_STATION_HOST_NAME);
      //WiFi.reconnect();
      WiFi.begin(_WIFI_SSID[i], _WIFI_PASSWORD[i]);

      delay_OS(1000); //this is a delay to wait for the connection to be established dont remove this line

      if (WiFi.status() == WL_CONNECTED)
      {
        printStatusWiFi();
        return int(WiFi.status());
      }
    }
  }
  Serial.println("WiFi connection Failed");
  return int(WiFi.status());
}
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printStatusWiFi() {
   Serial.println("-------------------------------------------------");
  (WiFi.status() == WL_CONNECTED) ? Serial.println("WiFi was connected") : Serial.println("WiFi was Not connected");
  Serial.print(F("IP= "));
  Serial.println(WiFi.localIP());

  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  int32_t rssi = WiFi.RSSI();
  Serial.print(F("RSSI: "));
  Serial.println(String(rssi) + F(" dBm"));

  Serial.print("ESP32 HostName: ");
  Serial.println(WiFi.getHostname());

  Serial.print("ESP32 Station HostName: ");
  Serial.println(_WIFI_STATION_HOST_NAME);

  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  Serial.println("-------------------------------------------------");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int task_WiFi_Init(void) {
//   WiFi.disconnect();
//   Serial.println(F("WiFi is Connecting to .... "));
//   for (int i = 0; i < _NUMBER_OF_SSID; i++)
//   {
//       Serial.print(" SSID[" + String(i) + "] ");
//       WiFi.setAutoReconnect();
//       WiFi.setHostname(_HOST_NAME);
//       tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, _STATION_NAME);

//       WiFi.reconnect();
//       WiFi.begin(_WIFI_SSID[i], _WIFI_PASSWORD[i]);

//       delay_OS(1000); //this is a delay to wait for the connection to be established dont remove this line



//       if (WiFi.status() == WL_CONNECTED)
//       {
//         printStatusWiFi();
//         return int(WiFi.status());
//       }
//     }
//   }
//   Serial.println("WiFi connection Failed");
//   return int(WiFi.status());
// }
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





