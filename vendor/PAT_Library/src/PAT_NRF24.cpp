#include <Arduino.h>
#include "SPI.h"
#include "NRFLite.h"
#include <PAT_NRF24.h>
#include <PAT_Debug.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const static uint8_t PIN_RADIO_CE = 2;
const static uint8_t PIN_RADIO_CSN = 0;
// const static uint8_t PIN_RADIO_IRQ  =   36;
const static uint8_t PIN_RADIO_MOSI = 23;
const static uint8_t PIN_RADIO_MISO = 19;
const static uint8_t PIN_RADIO_SCK = 18;


const static uint8_t RADIO_ID = 0;
const static uint8_t DESTINATION_RADIO_ID = 0;

NRFLite _radio;
struct_NRF24 _radioData;

Class_NRF24 NRF;  // Nordic Radio Frequency

volatile uint8_t _NRF24_dataWasReceived; 
static void radioInterrupt(void){
  _NRF24_dataWasReceived = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Class_NRF24::init(void) {
  SPI.begin(PIN_RADIO_SCK, PIN_RADIO_MISO, PIN_RADIO_MOSI, PIN_RADIO_CSN);

  // Indicate to NRFLite that it should not call SPI.begin() during initialization since it has already been done.
  uint8_t callSpiBegin = 0;
  //attachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ), radioInterrupt, FALLING);

  if (_radio.init(DESTINATION_RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 100, callSpiBegin))
  {
    Serial.println("NRF24 was initialized ");
    Serial.flush();

    return 1;
  }
  else
  {
    Serial.println("NRF24 couldn't initialized");
    Serial.flush();

    return 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Class_NRF24::println(char *str) {

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Class_NRF24::print(char *str) {
    // _radioData.OnTimeMillis = millis();

    // Serial.print("Sending ");
    // Serial.print(this->data.channel);
    // Serial.print(" ms");
    
    // if (_radio.send(DESTINATION_RADIO_ID, &, sizeof(_radioData)))
    // {
    //     Serial.println("...Success");
    // }
    // else
    // {
    //     Serial.println("...Failed");
    //     _radioData.FailedTxCount++;
    // }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #define DB_println(xxx) Debug_println(xxx) 
// #define DB_print(xxx) Debug_print(xxx) 
#define DB_println(xxx) 
#define DB_print(xxx) 

int Class_NRF24::scan(void) {
  uint8_t  received = 0;
  //--------------------------------------------------------
  while (_radio.hasDataISR())
  {
    _radio.readData(&this->vdata);
    received = 1;
  }
  //--------------------------------------------------------
  if (received)
  {
    DB_print("\nNRF24 Received: ");
    //--------------------------------------------------------
    if ((this->vdata.starter == '{') && (this->vdata.ender == '}') && (this->vdata.timestamp != this->data.timestamp))
    {
      memcpy(&this->data, &this->vdata, sizeof(this->vdata));
      this->flag = 1;
      DB_print("\nstarter= ");
      DB_println(this->data.starter);
      DB_print("timestamp= ");
      DB_println(this->data.timestamp);
      DB_print("relayR= ");
      for (size_t i = 0; i < sizeof(data.relayR); i++)
      {
        DB_print(this->data.relayR[i]);
        DB_print("  ");
      }
      DB_print("\nender= ");
      DB_println(this->data.ender);
    }
    else  if ((this->vdata.starter == '{') && (this->vdata.ender == '}') && (this->vdata.timestamp == this->data.timestamp))
    {
      DB_println("vdata was repeated");
      
    }
    else
    {
      memset(&this->vdata, 0, sizeof(this->vdata));
      DB_println("vdata was not Valided");
    }
    //--------------------------------------------------------
  }
  //--------------------------------------------------------
  return this->flag;
}

#undef DB_println
#undef DB_print
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Class_NRF24::scanInt(void) {
  if (_NRF24_dataWasReceived)
  {
    return this->scan();
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




