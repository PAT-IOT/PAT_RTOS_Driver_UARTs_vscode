#include <ArduinoJson.h>
//#include <PSRamFS.h>
//#include "PAT_Configuration.h"
#include "PAT_JSON.h"
#include "PAT_Relay.h"
#include "PAT_Task_MCU.h"
#include "lib/PAT_Configuration.h"
#include "PAT_RTC.h"
#include <vector>  // Include for std::vector
#include <map>  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define _TOPIC3 "IOT_Controller3"


// class_JSON JSON1("IOT_Controller1","IOT_Controller1",implementNull);
// class_JSON JSON2("IOT_Controller2","IOT_Controller1",implementNull);
// class_JSON JSON3("IOT_Controller3","IOT_Controller1",implementNull);
// class_JSON JSONx  ("JSONx","JSONx",implementNull);
// class_JSON JSON1_action_relay   ("IOT_Controller1", "action_relay",implementNull  );
// class_JSON JSON1_report_relay   ("IOT_Controller1", "report_relay",implementNull  );
// class_JSON JSON1_weeklySchedule ("IOT_Controller1", "weeklySchedule",implementNull);
// class_JSON JSON1_setDateTime    ("IOT_Controller1", "setDateTime",implementNull   );


// class_JSON JSON1("IOT_Controller1","IOT_Controller1");
// class_JSON JSON2("IOT_Controller2","IOT_Controller1");
// class_JSON JSON3("IOT_Controller3","IOT_Controller1");



class_JSON JSONx  ("JSONx","JSONx");
class_JSON JSON1_action_relay   ("IOT_Controller1", "action_relay"  );
class_JSON JSON1_report_relay   ("IOT_Controller1", "report_relay"  );
class_JSON JSON1_weeklySchedule ("IOT_Controller1", "weeklySchedule");
class_JSON JSON1_setDateTime    ("IOT_Controller1", "setDateTime"   );

class_Composer compose;
//extern class_Array< 1, 4, class_Relay > relay;
extern class_Relay relay[];
extern class_MCU MCU;
extern String _CHIP_SERIAL_NUMBER;
extern class_RTC RTC;
//StaticJsonDocument<4096> class_JSON::vdoc;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class_JSON::class_JSON(const char* mytopic, const char* mykey)
//   : topic(mytopic),key(mykey) {
//   this->payloadFlag = 0;
// }

class_JSON::class_JSON(const char* mytopic, const char* mykey) /*: vdoc( 2048 , SpiRamAllocator())*/ {
    topic = mytopic;
    key = mykey;
    payloadFlag = 0;
    payloadTemporaryFlag = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_JSON::save(MemoryJsonDocument<JsonDocumentSize>& dB_nvs) {
  String jsonString = "";
  serializeJson(dB_nvs, jsonString);
  class_nonVolatileMemory::write(this->key.c_str(), jsonString);  // Inherited from nonVolatileMemory
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_JSON::load(MemoryJsonDocument<JsonDocumentSize>& dB_nvs) {
    String jsonString = "";
    class_nonVolatileMemory::read(this->key.c_str(), jsonString);  // Inherited from nonVolatileMemory
    if (!jsonString.isEmpty()) {
        DeserializationError error = deserializeJson(dB_nvs, jsonString);
        if (error) {
            return -1; // or another suitable error code
        }
    }
    
    return 0; // or another suitable default value
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_Composer::save(String str) {
  if (str == "relayData")
  {
    char out[100];
    int result = snprintf(out, 100, "{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}", \

      this->relayData[0], this->relayData[1], this->relayData[2], this->relayData[3], \
      this->relayData[4], this->relayData[5], this->relayData[6], this->relayData[7], \
      this->relayData[8], this->relayData[9], this->relayData[10], this->relayData[11]);
    
    class_nonVolatileMemory::write(str.c_str(), String(out));
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_Composer::load(String str) {
  if (str == "relayData"){
    int val[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    char out[100];
    String strloaded;
    class_nonVolatileMemory::read(str.c_str(), strloaded);
    if (sscanf(strloaded.c_str(), "{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}", \
      val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8], val[9], val[10], val[11]) == 12)
    {
      for (int i = 0; i < 12; i++)
      {
        this->relayData[i] = val[i];
      }
      
      return 1;
    }
    else
    {
      return 0;
      }
  }
  else {
      return 0;
      }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_JSON::submit(const String &payload) {
  this->payloadError = deserializeJson(this->vdoc, payload);
  if (payloadError) {
    return 0;
  } else {
    this->dB = this->vdoc;
    this->save(this->dB);
    this->payloadFlag = 1;
    }
    return 1;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_JSON::putTemporary(const String &payload) {
  this->payloadError = deserializeJson(this->vdoc, payload);
  if (payloadError) {
    Serial.println("Json isNot Valid : ");
    Serial.println(payloadError.c_str());
    return 0;
  } else {
    this->dB = this->vdoc;
    Serial.println("Json is Valid : ");
      serializeJson(this->dB, Serial);
      Serial.println();
    }
  return 1;
}
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


String class_Composer::action_relay(int relaydata[], int offset) {
  char out[100];
  
  int result = snprintf(out, 100, "$relay[]={%d,%d,%d,%d,%d,%d,%d,%d}@", \
  relaydata[0 + offset], relaydata[1 + offset], relaydata[2 + offset], relaydata[3 + offset], \
  relaydata[4 + offset], relaydata[5 + offset], relaydata[6 + offset], relaydata[7 + offset]);
  return String(out);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String class_Composer::action_relay(int relaydata1, int relaydata2, int relaydata3, int relaydata4,  \
                                  int relaydata5, int relaydata6, int relaydata7, int relaydata8) {
  char out[100];
  int result = snprintf(out, 100, "$relay[]={%d,%d,%d,%d,%d,%d,%d,%d}@",  \
                        relaydata1, relaydata2, relaydata3, relaydata4,   \
                        relaydata5, relaydata6, relaydata7, relaydata8);
  return String(out);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String class_Composer::report_relay(int relaydata[]) {
  DynamicJsonDocument doc(2048);
  String str= _TOPIC1 + String('/') + chipSerialNumber();;
  doc["topic"] = str;
  doc["timestamp"] = "2134654764651464";
  doc["type"] = "report_relay";

  JsonArray relayArray = doc.createNestedArray("relay");
  for (int i = 0; i < 12; i++) {
    relayArray.add(relaydata[i]);
  }

  String jsonStr;
  serializeJson(doc, jsonStr);

  return jsonStr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void implement_action_relay(void) {
  
  Serial.println("implement_action_relay");
  
  int relay_Index = -1;
  for (JsonVariant item_relay : JSON1_action_relay.dB["relay"].as<JsonArray>())
  {
    relay_Index++;
    if ((relay_Index >= 0) && (relay_Index <= 11))
    {
    compose.relayData[relay_Index] = item_relay.as<int>();
    Serial.println("compose.relayData[" + String(relay_Index) + "] = " + String(item_relay.as<int>()));
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void implement_report_relay(void) {
  
  Serial.println("implement_report_relay");
  Serial.println(compose.report_relay(compose.relayData));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class_weeklySchedule weeklySchedule;
void weeklySchedulePutToStruct(void) {
  static const String dayName[] = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };
  Serial.println("___________________________weeklySchedulePutToStruct_____________________________________");
  //------------------------------------------------------------------------------------------------------------
  for (JsonPair day : JSON1_weeklySchedule.dB["weeklySchedule"].as<JsonObject>())
  {   // for(sunday, monday, tuesday, wednesday, thursday, friday, saturday){ }

    String dayOfWeek = String(day.key().c_str());   //  dayOfWeek = sunday  or  dayOfWeek = monday   or ....
    Serial.println("dayOfWeek = " + dayOfWeek);
    //--------------------------------------------------------------------------------------
    for (int dayIndex = 0; dayIndex < 7; dayIndex++)
    {
       Serial.println("________________________________________________");
      Serial.println("dayIndex = " + String(dayIndex));
      if (dayOfWeek == dayName[dayIndex])
      {
        int item_Index = -1;
        int relay_Index = -1;
        for (JsonVariant items : day.value().as<JsonArray>())
        {  // item objects are  time and relay
          item_Index++;

          weeklySchedule.day[dayIndex]->item[item_Index].time = items["time"].as<String>();
          Serial.println("items[" + String(item_Index) + "]. = " + String(items["time"].as<String>()));

          weeklySchedule.day[dayIndex]->item[item_Index].timeSec = RTC.toSecond(weeklySchedule.day[dayIndex]->item[item_Index].time);
          Serial.println("weeklySchedule.day[" + String(dayIndex) + "]->item[" + String(item_Index) + "].timeSec = " + String(weeklySchedule.day[dayIndex]->item[item_Index].timeSec));

          relay_Index = -1;
          for (JsonVariant item_relay : items["relay"].as<JsonArray>())
          {
            relay_Index++;
            weeklySchedule.day[dayIndex]->item[item_Index].relay[relay_Index] = item_relay.as<int>();
            Serial.println("weeklySchedule.day[" + String(dayIndex) + "]->item[" + String(item_Index) + "].relay[" + String(relay_Index) + "] = " + String(item_relay.as<int>()));

          }
           Serial.println("-------------------------------------------");
        }
         Serial.println("********************************************");
        while (item_Index < 9)
        {
          item_Index++;
          weeklySchedule.day[dayIndex]->item[item_Index].time = "";
          Serial.println("weeklySchedule.day[" + String(dayIndex) + "]->item[" + String(item_Index) + "].timeSec = -1");
          weeklySchedule.day[dayIndex]->item[item_Index].timeSec = -1;
        }
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_implement_weeklySchedule(void) {
  //Serial.println("____________________________________implement_weeklySchedule___________________________________");
  //---------------------------------
  DateTime now = RTC.now();
  String nameOfDay = RTC.nameOfDay(now);
  int nowSec = RTC.toSecond(now);
  //Serial.println("today is " + nameOfDay);
   //--------------------------------------------------------------------------------------------------------------------------------------------------------
    for (int dayIndex = 0; dayIndex < 7; dayIndex++)
    {
      if (weeklySchedule.day[dayIndex]->name == nameOfDay)
      {
        int wrote = 0;
        for (int item_Index = 9; item_Index >= 0; item_Index--)
        {
          //Serial.println("weeklySchedule.day["+ String(dayIndex) +"]->item[" + String(item_Index) + "].timeSec=" + String(weeklySchedule.day[dayIndex]->item[item_Index].timeSec));
          if ((wrote) || (weeklySchedule.day[dayIndex]->item[item_Index].timeSec == -1))
          {
          }
          else if ((nowSec) >= (weeklySchedule.day[dayIndex]->item[item_Index].timeSec))
          {
            wrote = 1;
            //Serial.println("relayData is being written from item=" + String(item_Index));
            for (int relay_Index = 0; relay_Index < 12; relay_Index++)
            {
              compose.relayData[relay_Index] = weeklySchedule.day[dayIndex]->item[item_Index].relay[relay_Index];
              //Serial.println("weeklySchedule.day["+ String(dayIndex) +"]->item[" + String(item_Index) + "] , compose.relayData[" + String(relay_Index) + "] = " + String(compose.relayData[relay_Index]));
            }
            compose.save("relayData");
          }
        }
      }
    }
   //--------------------------------------------------------------------------------------------------------------------------------------------------------
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void implement_setDateTime(void) {
  Serial.println("implement_setDateTime");
  // Extract the value from JSON as a String
  String datetimeStr = JSON1_setDateTime.dB["value"].as<String>();
  // Parse the date and time
  int year, month, day, hour, minute, second;
  if (sscanf(datetimeStr.c_str(), "%d-%d-%d %d:%d:%d",
             &year, &month, &day, &hour, &minute, &second) == 6) {
    // Create a DateTime object
    DateTime newTime(year, month, day, hour, minute, second);
    // Set the RTC to the new datetime
    RTC.adjust(newTime);
    Serial.println("RTC set to the new datetime.");
  } else {
    Serial.println("Failed to set the RTC.");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



