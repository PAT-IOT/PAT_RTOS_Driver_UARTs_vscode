#include <Arduino.h>
//#include <DS3231.h>
//#include <Wire.h>
#include "PAT_RTC.h"

class_RTC RTC;

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
int class_RTC::init(void){ 
    Wire.begin();
    if (begin()) {
      initialized = 1;
      /*if (lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        adjust(DateTime(F(__DATE__), F(__TIME__)));      // January 21, 2014 at 3am you would call:  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));    // When time needs to be set on a new device, or after a power loss, the// following line sets the RTC to the date & time this sketch was compiled
      }*/
      Serial.println("RTC was initialized");
      Serial.flush();
      return 1;
    }
    else {
      initialized = 0;
      Serial.println("RTC wasn't found");
      Serial.flush();
      return 0;  
      }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String class_RTC::nameOfDay(DateTime now){ 

int currentDay = now.dayOfTheWeek();// Get the current day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
  const char* dayNames[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"}; // Define an array of day names to map with the currentDay value
  const char* strDayName = dayNames[currentDay];  // Get the current day name
  return String(strDayName);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_RTC::toSecond(DateTime now) {
  int sec = (int)((now.hour() * 3600) + (now.minute() * 60) + now.second());
  return  sec;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_RTC::toSecond(String time) {
  int32_t itemHour, itemMinute, itemSecond;
  if (sscanf(time.c_str(), "%d:%d:%d", &itemHour, &itemMinute, &itemSecond) == 3) {
    int sec = (int)((itemHour * 3600) + (itemMinute * 60) + itemSecond);
    return sec;
  }
  else {
    return -1;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
