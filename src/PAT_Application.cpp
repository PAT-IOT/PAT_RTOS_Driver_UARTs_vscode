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
void tast_leds(void) { 
  if (WiFi.status() == WL_CONNECTED)
  {
    (mqttClient.isConnected()) ? led_wifi.turnOn() : led_wifi.toggle();
  }
  else {
      led_wifi.turnOff();
  }
 
  /*(nrf24.status()== NRFf24_CONNECTED) ? led_nrf.turnOn() : */led_nrf.turnOff();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_RTC(void){
  if(RTC.initialized){
  static int w=0;
    DateTime now = RTC.now();
    static DateTime future;
  Serial.println("\nCurrent Time: " + String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
    // if(w==0){
    //             future = RTC.now() + TimeSpan(0, 0, 1, 0); // after  1 min
    //             w=1;
    //         }
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
void clearRAM() { 
  esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, NULL);
  if (it == NULL) {
    Serial.println("Error: partition not found.");
    return;
  }
  const esp_partition_t *partition = esp_partition_get(it);
  esp_partition_erase_range(partition, 0, partition->size);
}
  



void task_MQTT(void) {
  mqttClient.update();  // should be called
  static uint32_t millis1 = 0;
  if (!mqttClient.isConnected() || (WiFi.status() != WL_CONNECTED))
  {
    MQTT.init();
    if ((millis() - millis1) > 20000)
    {
      Serial.println("ESP is bieng reseted");
      clearRAM();
      esp_restart();
    }
  }
  else millis1 = millis();

  //----------------------------------------------------
  if (JSON1_actionRelay.payloadFlag)
  {
    JSON1_actionRelay.payloadFlag = 0;
    JSON_to_buf_actionRelay();
  }
  if (JSON1_reportRelay.payloadFlag)
  {
    JSON1_reportRelay.payloadFlag=0;
    buf_to_JSON_reportRelay();
  }
  if (JSON1_weeklySchedule.payloadFlag)
  {
    JSON1_weeklySchedule.payloadFlag = 0;
    JSON_to_buf_weeklySchedule();
  }
  if (JSON1_setDateTime.payloadFlag)
  {
    JSON1_setDateTime.payloadFlag = 0;
    JSON_to_buf_setDateTime();
  }
  //----------------------------------------------------
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PAT:  at the same time , this function can update json of user to ubuf.relayS[0] , ubuf.relayS[1] , ubuf.relayS[2] , .... and   If this is (ubuf.relay[i] != ubuf.relayS[i])  , it will update    ubuf.relay[i] = ubuf.relayS[i]   and    ubuf.relayMode[i] = 's';
int task_run_weeklySchedule(void) {
  //Serial.println("____________________________________implement_weeklySchedule___________________________________");
  //---------------------------------
  DateTime now = RTC.now();
  String nameOfDay = RTC.nameOfDay(now);
  int nowSec = RTC.toSecond(now);
  int wrote = 0;
  //Serial.println("today is " + nameOfDay);
   //--------------------------------------------------------------------------------------------------------------------------------------------------------
    for (int dayIndex = 0; dayIndex < 7; dayIndex++)
    {
      if (ubuf.weeklySchedule.day[dayIndex]->name == nameOfDay)
      {
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
            for (int relay_Index = 0; relay_Index < _RELAY_NUMBER; relay_Index++)
            {
              ubuf.relayS[relay_Index] = ubuf.weeklySchedule.day[dayIndex]->item[item_Index].relay[relay_Index];
              if (ubuf.relay[relay_Index] != ubuf.relayS[relay_Index])
              {
                ubuf.relay[relay_Index] = ubuf.relayS[relay_Index];
                ubuf.relayMode[relay_Index] = 's';
              }
              //Serial.println("ubuf.weeklySchedule.day["+ String(dayIndex) +"]->item[" + String(item_Index) + "] , ubuf.relay[" + String(relay_Index) + "] = " + String(ubuf.relay[relay_Index]));
            }
            file_class_UserBuffer.save(ubuf);
          }
        }
      }
    }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    return wrote;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_MCU_Received(void) {
  if (MCU.checkReceivedData())
  {

    //--------------------------------------------
    if (MCU.flag.pushButtonReceived)
    {
      MCU.flag.pushButtonReceived = 0;

      for (int i = 0; i < 12; i++)
      {
        if (MCU.pushButton[i])
        {
          MCU.pushButton[i] = 0;
          (ubuf.relayM[i]) ? ubuf.relayM[i] = 0 : ubuf.relayM[i] = 1;
          if (ubuf.relayM[i] != ubuf.relay[i])
          {
            ubuf.relay[i] = ubuf.relayM[i];
            ubuf.relayMode[i] = 'm';
          }
        }
      }
      file_class_UserBuffer.save(ubuf);
      MCU.send(ubuf.relay);
    }

    //--------------------------------------------
    if (MCU.flag.relayReceived)
    {
      MCU.flag.relayReceived = 0;
      MCU.lastInterval = millis();
    }
    //--------------------------------------------
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task_MCU_Send(void) {
  MCU.send(ubuf.relay);

  if ((abs(MCU.lastInterval - MCU.firstInterval)) > _MCU_VALID_INTERVAL)
  {
     Serial.println("MCU is bieng reseted"); Serial.println(MCU.lastInterval); Serial.println(MCU.firstInterval);
    MCU.turnOff();
    delay_OS(2000);
    MCU.turnOn();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JSON_to_buf_setDateTime(void) {
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
void JSON_to_buf_actionRelay(void) {
  
  Serial.println("implement_action_relay");
  
  int relay_Index = -1;
  for (JsonVariant item_relay : JSON1_actionRelay.dB["relay"].as<JsonArray>())
  {
    relay_Index++;
    if ((relay_Index >= 0) && (relay_Index < _RELAY_NUMBER))
    {
        ubuf.relayA[relay_Index] = item_relay.as<int>();
        if (ubuf.relay[relay_Index] != ubuf.relayA[relay_Index])
              {
                ubuf.relay[relay_Index] = ubuf.relayA[relay_Index];
                ubuf.relayMode[relay_Index] = 'a';
              }
        Serial.println("ubuf.relayA[" + String(relay_Index) + "] = " + String(item_relay.as<int>()));
    }
  }
  //   relay_Index = -1;
  // for (JsonVariant item_relay : JSON1_actionRelay.dB["mode"].as<JsonArray>())
  // {
  //   relay_Index++;
  //   if ((relay_Index >= 0) && (relay_Index < _RELAY_NUMBER))
  //   {
  //       ubuf.relayMode[relay_Index] = char(item_relay.as<String>()[0]);     // if we want to change mode of relays
  //       Serial.println("ubuf.relayMode[" + String(relay_Index) + "] = " + item_relay.as<String>()[0]);
  //   }
  // }
   file_class_UserBuffer.save(ubuf);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PAT: ubuf is very important for buffer management, and I wrote the json structure code, this command can help to understand the ubuf object.
// {
//   "timestamp": 164521452,
//   "type": "weeklySchedule",
//   "weeklySchedule": {                                                        //    ubuf.weeklySchedule...
//     "tuesday": [                                                             //    ubuf.weeklySchedule.day[dayIndex = 2]...    =>    dayIndex = {sunday = 0 , monday = 1 , tuesday=2 , ...}     if we want to get string of day we can use     ubuf.weeklySchedule.day[2]->name      that this case(day[2])  name is tuesday
//       {"time": "18:52:00", "relay": [0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1]},   //    ubuf.weeklySchedule.day[dayIndex]->item[0].time = 18:52:00     //    ubuf.weeklySchedule.day[dayIndex]->item[0].relay[0] = 0    // ubuf.weeklySchedule.day[dayIndex]->item[0].relay[1] = 0      // ubuf.weeklySchedule.day[dayIndex]->item[0].relay[2] = 0    ...
//       {"time": "18:52:30", "relay": [0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0]},   //    ubuf.weeklySchedule.day[dayIndex]->item[1].time = 18:52:30     //    ubuf.weeklySchedule.day[dayIndex]->item[1].relay[0] = 0    // ubuf.weeklySchedule.day[dayIndex]->item[1].relay[1] = 0      // ubuf.weeklySchedule.day[dayIndex]->item[1].relay[2] = 1    ...
//       {"time": "18:53:00", "relay": [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0]},   //    ubuf.weeklySchedule.day[dayIndex]->item[2].time = 18:53:00     //    ubuf.weeklySchedule.day[dayIndex]->item[2].relay[0] = 0    // ubuf.weeklySchedule.day[dayIndex]->item[2].relay[1] = 1      // ubuf.weeklySchedule.day[dayIndex]->item[2].relay[2] = 0    ...
//       {"time": "18:53:30", "relay": [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0]}    //    ubuf.weeklySchedule.day[dayIndex]->item[3].time = 18:53:30     //    ubuf.weeklySchedule.day[dayIndex]->item[3].relay[0] = 1    // ubuf.weeklySchedule.day[dayIndex]->item[3].relay[1] = 0      // ubuf.weeklySchedule.day[dayIndex]->item[3].relay[2] = 0    ...
//     ]
//   }
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JSON_to_buf_weeklySchedule(void) {
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void buf_to_JSON_reportRelay(void) {
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



