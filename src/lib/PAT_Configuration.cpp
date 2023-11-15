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
const char* _MQTT_START_MESSAGE = "{\ntype: Report,\nclient_Name: IOT_Controller,\nserial_number: ed4578798675as4465,\n}"  ;