#include "PAT_Application.h"
#include "PAT_Prototype.h"
#include "PAT_Tasks_OS.h"
#include "PAT_Task_MCU.h"
#include "PAT_Task_MQTT.h"
#include "PAT_Task_WebServer.h"
#include <PAT_RTC.h>
#include <PAT_Relay.h>
#include <PAT_Debug.h>
#include "PAT_Application.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_RTC(void){
  if(RTC.initialized){
  static int w=0;
    DateTime now = RTC.now();
    static DateTime future;
  Serial.println("\nCurrent Time: " + String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
    if(w==0){
                future = RTC.now() + TimeSpan(0, 0, 1, 0); // after  1 min
                w=1;
            }
  // Serial.println("\t\t\t\t\t\tFuture  Time: " + String(future.year()) + "-" + String(future.month()) + "-" + String(future.day()) + " " + String(future.hour()) + ":" + String(future.minute()) + ":" + String(future.second()));
  //   if(future < now)  Serial.println("Alarm ON ");
  //   else  Serial.println("\t\t\t\t\t\tAlarm OFF ");
  }else {
  RTC.init();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_WebServer(void){
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_MQTT(void) {
  mqttClient.update();  // should be called
  if (!mqttClient.isConnected() || (WiFi.status() != WL_CONNECTED) ) MQTT.init();
  
  //----------------------------------------------------
  if (JSON1_action_relay.payloadFlag){
        action_relay_to_buf();
        task_update_relay();
      JSON1_action_relay.payloadFlag = 0;
  }
  if (JSON1_report_relay.payloadFlag){
      task_report_relay();
      JSON1_report_relay.payloadFlag=0;
  }
  if (JSON1_weeklySchedule.payloadFlag){
      weeklySchedule_to_buf();
      JSON1_weeklySchedule.payloadFlag=0;
  }
  if (JSON1_setDateTime.payloadFlag){
      setDateTime_to_buf();
      JSON1_setDateTime.payloadFlag=0;
  }
    //----------------------------------------------------
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_report_relay(void) {
  Serial.println("implement_report_relay");
  DynamicJsonDocument doc(2048);
  String str = _TOPIC1 + String('/') + chipSerialNumber();;
  doc["topic"] = str;
  doc["timestamp"] = "2134654764651464";
  doc["type"] = "report_relay";
  JsonArray relayArray = doc.createNestedArray("relay");
  for (int i = 0; i < 12; i++) {
    relayArray.add(ubuf.relay[i]);
  }
  String jsonStr;
  serializeJson(doc, jsonStr);
  Serial.println(jsonStr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_update_relay(void) {

    for (int i = 0; i < _RELAY_NUMBER; i++)
    {
        switch (ubuf.relayMode[i])
        {
        case 'a':
            ubuf.relay[i] = ubuf.relayA[i];
            break;
        case 's':
            ubuf.relay[i] = ubuf.relayS[i];
            break;
        case 'm':
            ubuf.relay[i] = ubuf.relayM[i];
            break;
            //-------------------
        default:
            ;
        }
    }
    char out[100];
    int result = snprintf(out, sizeof(out), "relay[]={%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}",
      ubuf.relay[0], ubuf.relay[1], ubuf.relay[2], ubuf.relay[3],
      ubuf.relay[4], ubuf.relay[5], ubuf.relay[6], ubuf.relay[7],
      ubuf.relay[8], ubuf.relay[9], ubuf.relay[10], ubuf.relay[11]);

      MCU.println(out);
      MCU.flush();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_update_buf_weeklySchedule(void) {
  //Serial.println("____________________________________implement_weeklySchedule___________________________________");
  //---------------------------------
  DateTime now = RTC.now();
  String nameOfDay = RTC.nameOfDay(now);
  int nowSec = RTC.toSecond(now);
  //Serial.println("today is " + nameOfDay);
   //--------------------------------------------------------------------------------------------------------------------------------------------------------
    for (int dayIndex = 0; dayIndex < 7; dayIndex++)
    {
      if (ubuf.weeklySchedule.day[dayIndex]->name == nameOfDay)
      {
        int wrote = 0;
        for (int item_Index = 9; item_Index >= 0; item_Index--)
        {
          //Serial.println("ubuf.weeklySchedule.day["+ String(dayIndex) +"]->item[" + String(item_Index) + "].timeSec=" + String(ubuf.weeklySchedule.day[dayIndex]->item[item_Index].timeSec));
          if ((wrote) || (ubuf.weeklySchedule.day[dayIndex]->item[item_Index].timeSec == -1))
          {
          }
          else if ((nowSec) >= (ubuf.weeklySchedule.day[dayIndex]->item[item_Index].timeSec))
          {
            wrote = 1;
            //Serial.println("relay is being written from item=" + String(item_Index));
            for (int relay_Index = 0; relay_Index < 12; relay_Index++)
            {
              ubuf.relayS[relay_Index] = ubuf.weeklySchedule.day[dayIndex]->item[item_Index].relay[relay_Index];
              //Serial.println("ubuf.weeklySchedule.day["+ String(dayIndex) +"]->item[" + String(item_Index) + "] , ubuf.relay[" + String(relay_Index) + "] = " + String(ubuf.relay[relay_Index]));
            }
            //ubuf.save("relay");
          }
        }
      }
    }
   //--------------------------------------------------------------------------------------------------------------------------------------------------------
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setDateTime_to_buf(void) {
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
void action_relay_to_buf(void) {
  
  Serial.println("implement_action_relay");
  
  int relay_Index = -1;
  for (JsonVariant item_relay : JSON1_action_relay.dB["relay"].as<JsonArray>())
  {
    relay_Index++;
    if ((relay_Index >= 0) && (relay_Index < _RELAY_NUMBER))
    {
        ubuf.relayA[relay_Index] = item_relay.as<int>();
       
        Serial.println("ubuf.relayA[" + String(relay_Index) + "] = " + String(item_relay.as<int>()));
    }
  }

    relay_Index = -1;
  for (JsonVariant item_relay : JSON1_action_relay.dB["mode"].as<JsonArray>())
  {
    relay_Index++;
    if ((relay_Index >= 0) && (relay_Index < _RELAY_NUMBER))
    {
        ubuf.relayMode[relay_Index] = char(item_relay.as<String>()[0]);
       
        Serial.println("ubuf.relayMode[" + String(relay_Index) + "] = " + item_relay.as<String>()[0]);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void weeklySchedule_to_buf(void) {
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

          ubuf.weeklySchedule.day[dayIndex]->item[item_Index].time = items["time"].as<String>();
          Serial.println("items[" + String(item_Index) + "]. = " + String(items["time"].as<String>()));

          ubuf.weeklySchedule.day[dayIndex]->item[item_Index].timeSec = RTC.toSecond(ubuf.weeklySchedule.day[dayIndex]->item[item_Index].time);
          Serial.println("ubuf.weeklySchedule.day[" + String(dayIndex) + "]->item[" + String(item_Index) + "].timeSec = " + String(ubuf.weeklySchedule.day[dayIndex]->item[item_Index].timeSec));

          relay_Index = -1;
          for (JsonVariant item_relay : items["relay"].as<JsonArray>())
          {
            relay_Index++;
            ubuf.weeklySchedule.day[dayIndex]->item[item_Index].relay[relay_Index] = item_relay.as<int>();
            Serial.println("ubuf.weeklySchedule..day[" + String(dayIndex) + "]->item[" + String(item_Index) + "].relay[" + String(relay_Index) + "] = " + String(item_relay.as<int>()));

          }
           Serial.println("-------------------------------------------");
        }
         Serial.println("********************************************");
        while (item_Index < 9)
        {
          item_Index++;
          ubuf.weeklySchedule.day[dayIndex]->item[item_Index].time = "";
          Serial.println("ubuf.weeklySchedule..day[" + String(dayIndex) + "]->item[" + String(item_Index) + "].timeSec = -1");
          ubuf.weeklySchedule.day[dayIndex]->item[item_Index].timeSec = -1;
        }
      }
    }
  }
}








