#ifndef __PAT_RTC_h__
#define __PAT_RTC_h__
//#include <DS3231.h>
#include <Wire.h>
#include <RTClib.h>





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class class_RTC: public RTC_DS3231 {
private:
public:
  int initialized;
  // DateTime estimatedTime;
  //------------------------------------------------------
  int init(void);
  //------------------------------------------------------
  DateTime now() {
    if ((initialized) || (!RTC_DS3231::lostPower()))
    {
      DateTime now = RTC_DS3231::now();
      if ((now.year() >= 2023)  &&  (now.year() <= 2039) &&
          (now.month() >= 0)    &&  (now.month() <= 12)  &&
          (now.day() >= 0)      &&  (now.day() <= 31)  &&
          (now.hour() >= 0)     &&  (now.month() <= 12) &&
          (now.minute() >= 0)   &&  (now.minute() <= 59) &&
        (now.second() >= 0) && (now.second() <= 59))
      {
       // estimatedTime = now;
         return now;
      }
       
    }
    else {
      this->init();
    }
    return  DateTime(0,0,0,0,0,0);
  }
  //------------------------------------------------------
String nameOfDay(DateTime now);
 int toSecond(DateTime now);
 int toSecond(String time);
 //void operator()(bool activeMode);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // __PAT_RTC_h__