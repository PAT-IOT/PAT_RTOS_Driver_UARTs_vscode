#ifndef PAT_JSON__H
#define PAT_JSON__H

#include <Arduino.h>
//#include <PSRamFS.h>
#include "PAT_Memory.h"
#include <ArduinoJson.h>
#include <vector>  // Include for std::vector
#include <map>  
//#include "esp_heap.h"




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define JsonDocumentSize 2048
#define MemoryJsonDocument StaticJsonDocument

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_JSON : public class_nonVolatileMemory {
private:
  
  //EXT_RAM_ATTR uint8_t myVariable[2024];
  //SpiRamJsonDocument vdoc;
 StaticJsonDocument<JsonDocumentSize> vdoc;  //valid data Base
public:
  DeserializationError payloadError;
  typedef void (*Implement)(void);
  
  String topic = "";
  String key = "";
  StaticJsonDocument<JsonDocumentSize> dB;  //valid data Base

  int payloadFlag;
  int payloadTemporaryFlag;
  // class_JSON(const char* mytopic = "", const char* mykey = "", ptrImplementFuntion ptrfun = implementNull)
//     : topic(mytopic), key(mykey), ptrImplementFuntion(ptrfun) {
//         this->payloadFlag = 0;
//         this->payloadTemporaryFlag = 0;
//     }
  class_JSON(const char* mytopic= "", const char* mykey="");
  void save(StaticJsonDocument<JsonDocumentSize>& dB_nvs);
  int  load(StaticJsonDocument<JsonDocumentSize>& dB_nvs);
  int  submit(const String &payload);
  int  putTemporary(const String &payload);
  const String& getTopic() const
  {
    return topic;
  }
  const String& getkey() const
    {
      return key;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_Parser {
private:

public:
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_Composer : public class_nonVolatileMemory {
private:
  String key_Relay = "relayData";

public:
  int relayData[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  //char causeRelayData[12] = { '','0','0','0','0','0','0','0','0','0','0','0' };

  void save(String str);
  int load(String str);
  String action_relay(int relaydata[], int offset = 0);
  String action_relay( int relaydata1, int relaydata2, int relaydata3, int relaydata4, 
                      int relaydata5, int relaydata6, int relaydata7, int relaydata8);
  String report_relay(int relaydata[]);

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WeeklyScheduleItem {
public:
    String time;
    String value;
    std::vector<int> channels;
};

class WeeklySchedule {
public:
    std::map<String, std::vector<WeeklyScheduleItem>> days;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------
class class_timeSchedule {
public:
  String time;
  int    timeSec;
  int    relay[12];
};
//--------------------------------
class class_daySchedule {
  public:
  class_timeSchedule item[10];
  String name;

  
  String dayName() {
    return this->name;
  }

  
  class_daySchedule(const String& dayStr) : name(dayStr) {
    // Constructor implementation
  }
};


//--------------------------------
class class_weeklySchedule {
public:
  class_daySchedule sunday{"sunday"}, monday{"monday"}, tuesday{"tuesday"}, wednesday{"wednesday"}, thursday{"thursday"}, friday{"friday"}, saturday{"saturday"};
  class_daySchedule* day[7] = {&sunday, &monday, &tuesday, &wednesday, &thursday, &friday, &saturday};

    // Constructor implementation
  /*class_daySchedule& getDay(int dayIndex) {
    if (dayIndex < 0 || dayIndex >= 7) {
      throw std::out_of_range("Invalid day index");
    }
    return *day[dayIndex];
  }*/
};

//--------------------------------



void task_implement_weeklySchedule(void);
//void implement_weeklySchedule2(void);
void weeklySchedulePutToStruct(void);

void implement_action_relay(void);

void implement_report_relay(void);

void implement_weeklySchedule(void);

void implement_setDateTime(void);


#endif  //PAT_JSON__H
