#include <Arduino.h>
#include "PAT_Configuration.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String _CHIP_SERIAL_NUMBER = "";

String chipSerialNumber(void) {
    if (_CHIP_SERIAL_NUMBER != "") {
        return (_CHIP_SERIAL_NUMBER);
    }
    else {
    uint32_t id = 0;
	for(int i=0; i<17; i=i+8) {
	  id |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    _CHIP_SERIAL_NUMBER = String(id);
    return (_CHIP_SERIAL_NUMBER);
    }
}



const char* _WIFI_SSID[_NUMBER_OF_SSID] =       { "PAT_IOT",    "PAT_IOT",      "PAT_IOT2" };
const char* _WIFI_PASSWORD[_NUMBER_OF_SSID] =   { "PAT_IOT123",  "PAT_IOT123",   "PAT_IOT123" };
//const char* _MQTT_START_MESSAGE = "{\ntype: Report,\nclient_Name: IOT_Controller,\nserial_number: ed4578798675as4465,\n}";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #define _NUMBER_OF_SSID 3
// #define _NUMBER_OF_CHANNELS env["numberOfChannels"]
// #define _WEBSOCKET_SERVER_IP "195.248.240.222"
// #define _WEBSOCKET_SERVER_IP_ARRAY {195, 248, 240, 222}
// #define _PASSWORD_SERVER "xxx"
// #define _USERNAME_SERVER "admin"
// #define _CLIENT_NAME "arduino"
// #define _WEBSOCKET_PORT 9001
// #define _SEPARATOR_PATH "/"
// #define _URL_PATH "mqtt"
// #define _TOPIC1 "IOT_Controller1"
// #define _TOPIC2 "IOT_Controller2"
// #define _TOPIC3 "IOT_Controller3"
// const char* _WIFI_SSID[_NUMBER_OF_SSID] = {"PAT_IOT", "PAT_IOT", "PAT_IOT2"};
// const char* _WIFI_PASSWORD[_NUMBER_OF_SSID] = {"PAT_IOT123", "PAT_IOT123", "PAT_IOT123"};
// const char* _MQTT_START_MESSAGE = "{\ntype: Report,\nclient_Name: IOT_Controller,\nserial_number: ed4578798675as4465,\n}";
struct Configuration {
    int NUMBER_OF_SSID;
    int NUMBER_OF_CHANNELS;
    const char* WEBSOCKET_SERVER_IP;
    int WEBSOCKET_SERVER_IP_ARRAY[4];
    const char* PASSWORD_SERVER;
    const char* USERNAME_SERVER;
    const char* CLIENT_NAME;
    int WEBSOCKET_PORT;
    const char* SEPARATOR_PATH;
    const char* URL_PATH;
    const char* TOPIC1;
    const char* TOPIC2;
    const char* TOPIC3;
    const char* WIFI_SSID[_NUMBER_OF_SSID];
    const char* WIFI_PASSWORD[_NUMBER_OF_SSID];
    const char* MQTT_START_MESSAGE;
};

/*
Configuration Configuration_Default= {
    _NUMBER_OF_SSID,
    _NUMBER_OF_CHANNELS,
    _WEBSOCKET_SERVER_IP,
    {_WEBSOCKET_SERVER_IP_ARRAY[0], _WEBSOCKET_SERVER_IP_ARRAY[1], _WEBSOCKET_SERVER_IP_ARRAY[2], _WEBSOCKET_SERVER_IP_ARRAY[3]},
    _PASSWORD_SERVER,
    _USERNAME_SERVER,
    _CLIENT_NAME,
    _WEBSOCKET_PORT,
    _SEPARATOR_PATH,
    _URL_PATH,
    _TOPIC1,
    _TOPIC2,
    _TOPIC3,
    {_WIFI_SSID[0], _WIFI_SSID[1], _WIFI_SSID[2]},
    {_WIFI_PASSWORD[0], _WIFI_PASSWORD[1], _WIFI_PASSWORD[2]},
    _MQTT_START_MESSAGE
};
*/









