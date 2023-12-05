#ifndef __PAT_Configuration_h__
#define __PAT_Configuration_h__
//#include "dotenv.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





String chipSerialNumber(void);
// [
//     {ssid:x, password:y},
//     {ssid:x, password:y},
//     {ssid:x, password:y},
//     {ssid:x, password:y},
//     {ssid:x, password:y},
//     {ssid:x, password:y},
//     {ssid:x, password:y},
// ]

//env.load_dotenv();


#define     _NUMBER_OF_SSID     3	
#define     _NUMBER_OF_CHANNELS     env["numberOfChannels"]
#define     _WEBSOCKET_SERVER_IP    "195.248.240.222"          //    ws://195.248.240.222
#define     _WEBSOCKET_SERVER_IP_ARRAY    195, 248, 240, 222 
#define     _PASSWORD_SERVER        "rLjRfTsPkUfOaQtZ"
#define     _USERNAME_SERVER 	      "admin"
#define     _CLIENT_NAME            "arduino"
#define     _WEBSOCKET_PORT           9001
#define     _SEPARATOR_PATH         "/"  // url
#define     _URL_PATH               "mqtt"
#define     _TOPIC1                 "IOT_Controller1" 
#define     _TOPIC2                 "IOT_Controller2"
#define     _TOPIC3                 "IOT_Controller3"



#define     fori(x) 	             for(int i = 0; i < x; i++)
#define     forj(x) 	             for(int j = 0; j < x; j++)
#define     fora(x) 	             for(int a = 0; a < x; a++)
#define     forb(x) 	             for(int b = 0; b < x; b++)
#define     forc(x) 	             for(int c = 0; c < x; c++)
#define     ford(x) 	             for(int d = 0; d < x; d++)




extern const char*	_WIFI_SSID[];
extern const char* _WIFI_PASSWORD[];
#define delay_OS(xxx) vTaskDelay(xxx / portTICK_PERIOD_MS);




/*
  const char* json = R"(
  {
    /"timestamp/":%d,
    /"type":/"report_relay/",
    /"topic/":/"IOT_Controller/0512654/",
    /"relay[]/":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]
  }
  )";
*/










// {
//   "type": "action",
//   "value": 0,
//   "serial_number": "ed4578798675as4465",
//   "channel": 15,
//   "timestamp": 164521452
// }

// WebSocketsClient webSocket;
// //MQTTPubSub::PubSubClient<256> mqttClient;
// MQTTPubSubClient mqttClient;

#endif  //__PAT_WebServer_h__















