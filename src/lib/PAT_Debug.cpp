// version 020729
#include <Arduino.h>


unsigned long start_time_MEASURE;
unsigned long end_time_MEASURE;
unsigned long start_time_MEASURE0;
unsigned long end_time_MEASURE0;

String limitString(const String &str, size_t maxLength) {
  if (str.length() <= maxLength) {
    return str;
  } else {
    String truncatedStr = str.substring(0, maxLength - 15);
    truncatedStr += "...";
    truncatedStr += str.substring(str.length() - 15);
    return truncatedStr;
  }
}

