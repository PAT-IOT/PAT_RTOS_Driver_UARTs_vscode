//PAT Help


// {
//   "timestamp": 164521452,
//   "type": "weeklySchedule",
//   "weeklySchedule": {
//     "tuesday": [
//       {"time": "18:52:00", "relay": [0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1]},
//       {"time": "18:52:30", "relay": [0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0]},
//       {"time": "18:53:00", "relay": [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0]},
//       {"time": "18:53:30", "relay": [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0]}
//     ]
//   }
// }

// ubuf (class_UserBuffer)
// │
// ├── key_Relay : "relay"
// │
// ├── relay : [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
// │
// ├── relayA : [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
// │
// ├── relayS : [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
// │
// ├── relayM : [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
// │
// ├── relayMode : ['a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a']   //   'a'   or   'm'   or   's'
// │
// └── weeklySchedule (class_weeklySchedule)
//     │
//     ├── day (array of class_daySchedule*)
//     │   │
//     │   ├── sunday
//     │   │   ├── item (array of class_timeSchedule)
//     │   │   └── name : "sunday"
//     │   │
//     │   ├── monday
//     │   │   ├── item (array of class_timeSchedule)
//     │   │   └── name : "monday"
//     │   │
//     │   ├── tuesday
//     │   │   ├── item (array of class_timeSchedule)
//     │   │   └── name : "tuesday"
//     │   │
//     │   ├── wednesday
//     │   │   ├── item (array of class_timeSchedule)
//     │   │   └── name : "wednesday"
//     │   │
//     │   ├── thursday
//     │   │   ├── item (array of class_timeSchedule)
//     │   │   └── name : "thursday"
//     │   │
//     │   ├── friday
//     │   │   ├── item (array of class_timeSchedule)
//     │   │   └── name : "friday"
//     │   │
//     │   └── saturday
//     │       ├── item (array of class_timeSchedule)
//     │       └── name : "saturday"
//     │
//     └── Struct (function)


// class class_timeSchedule
// │
// ├── String time
// ├── int timeSec
// └── int relay[12]

// class class_daySchedule
// │
// ├── class_timeSchedule item[10]
// └── String name
//     └── dayName()

// class class_weeklySchedule
// │
// ├── void Struct()
// ├── class_daySchedule sunday
// │   └── class_timeSchedule item[10]
// │       └── String name
// │           └── dayName()
// ├── class_daySchedule monday
// │   └── class_timeSchedule item[10]
// │       └── String name
// │           └── dayName()
// ├── class_daySchedule tuesday
// │   └── class_timeSchedule item[10]
// │       └── String name
// │           └── dayName()
// ├── class_daySchedule wednesday
// │   └── class_timeSchedule item[10]
// │       └── String name
// │           └── dayName()
// ├── class_daySchedule thursday
// │   └── class_timeSchedule item[10]
// │       └── String name
// │           └── dayName()
// ├── class_daySchedule friday
// │   └── class_timeSchedule item[10]
// │       └── String name
// │           └── dayName()
// └── class_daySchedule saturday
//     └── class_timeSchedule item[10]
//         └── String name
//             └── dayName()

// class class_nonVolatileMemory

// class class_UserBuffer
// │
// ├── String key_Relay
// ├── int relay[12]
// ├── int relayA[12]
// ├── int relayS[12]
// ├── int relayM[12]
// ├── char relayMode[12]
// ├── class_weeklySchedule weeklySchedule
// │   └── void Struct()
// │       ├── class_daySchedule sunday
// │       │   └── class_timeSchedule item[10]
// │       │       └── String name
// │       │           └── dayName()
// │       ├── class_daySchedule monday
// │       │   └── class_timeSchedule item[10]
// │       │       └── String name
// │       │           └── dayName()
// │       ├── class_daySchedule tuesday
// │       │   └── class_timeSchedule item[10]
// │       │       └── String name
// │       │           └── dayName()
// │       ├── class_daySchedule wednesday
// │       │   └── class_timeSchedule item[10]
// │       │       └── String name
// │       │           └── dayName()
// │       ├── class_daySchedule thursday
// │       │   └── class_timeSchedule item[10]
// │       │       └── String name
// │       │           └── dayName()
// │       ├── class_daySchedule friday
// │       │   └── class_timeSchedule item[10]
// │       │       └── String name
// │       │           └── dayName()
// │       └── class_daySchedule saturday
// │           └── class_timeSchedule item[10]
// │               └── String name
// │                   └── dayName()
// ├── void save(String str)
// └── int load(String str)
























#ifndef PAT_JSON__H
#define PAT_JSON__H
//#include "PAT_Prototype.h"
#include <Arduino.h>
#include <PAT_Memory.h>
#include <ArduinoJson.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _JSON_DOCUMENT_SIZE 2048
#define MemoryJsonDocument StaticJsonDocument
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_JSON : public class_nonVolatileMemory {
private:
  

 StaticJsonDocument<_JSON_DOCUMENT_SIZE> vdoc;  //valid data Base
public:
  DeserializationError payloadError;
  StaticJsonDocument<_JSON_DOCUMENT_SIZE> dB;  //valid data Base
  typedef void (*Implement)(void);
  String topic = "";
  String key = "";

  int payloadFlag;
  int payloadTemporaryFlag;

  class_JSON(const char* mytopic= "", const char* mykey="");
  void save(StaticJsonDocument<_JSON_DOCUMENT_SIZE>& dB_nvs);
  int  load(StaticJsonDocument<_JSON_DOCUMENT_SIZE>& dB_nvs);
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
class class_timeSchedule {
public:
  String time;
  int    timeSec;
  int    relay[12];
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_daySchedule {
  public:
    class_timeSchedule item[10];
    String name;

    class_daySchedule(const String& dayStr) : name(dayStr) {}
    String dayName() {
      return this->name;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_weeklySchedule {
public:
  void Struct(void);
  class_daySchedule sunday{ "sunday" }, monday{ "monday" }, tuesday{ "tuesday" },
    wednesday{ "wednesday" }, thursday{ "thursday" }, friday{ "friday" }, saturday{ "saturday" };
    
    class_daySchedule* day[7] = { &sunday, &monday, &tuesday, &wednesday, &thursday, &friday, &saturday };
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class class_UserBuffer : public class_nonVolatileMemory{
private:
  String key_Relay = "relay";
public:
  int relay[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  int relayA[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; 
  int relayS[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  int relayM[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  char relayMode[12] = { 'a','a','a','a','a','a','a','a','a','a','a','a'};
  
  class_weeklySchedule    weeklySchedule;
  void save(String str);
  int load(String str);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif  //PAT_JSON__H
