// version 021010


#ifndef _PAT_DEBUG_H
#define _PAT_DEBUG_H

#define PAT_Debug





#ifdef PAT_Debug

extern unsigned long start_time_MEASURE;
extern unsigned long end_time_MEASURE;
extern unsigned long start_time_MEASURE0;
extern unsigned long end_time_MEASURE0;
String limitString(const String& str, size_t maxLength);
//----------------------------------------------------------------------------------------------------
#define DEBUG_MEASURE_TIME(FUNC_X) \
  start_time_MEASURE = millis(); \
  FUNC_X \
  end_time_MEASURE = millis(); \
  Serial.println("________________________________________________________________________"); \
  Serial.print(start_time_MEASURE); \
  Serial.print(" : Execution time of Line "); \
  Serial.print(__LINE__); \
  Serial.print(":"); \
  Serial.print(end_time_MEASURE - start_time_MEASURE); \
  Serial.print(" ms into core:"); \
  Serial.println(xPortGetCoreID()); \
  Serial.println(limitString(#FUNC_X, 50)); \
  Serial.println("_________________________________________________________________________");\
  Serial.flush();
//----------------------------------------------------------------------------------------------------
#define DEBUG_MEASURE_TIME0(FUNC_X) \
  start_time_MEASURE0 = millis(); \
  FUNC_X \
  end_time_MEASURE0 = millis(); \
  Serial.println("________________________________________________________________________"); \
  Serial.println(start_time_MEASURE0); \
  Serial.print(" : Execution time of Line "); \
  Serial.print(__LINE__); \
  Serial.print(":"); \
  Serial.print(end_time_MEASURE0 - start_time_MEASURE0); \
  Serial.print(" ms into core:"); \
  Serial.println(xPortGetCoreID()); \
  Serial.println(limitString(#FUNC_X, 50)); \
  Serial.println("_________________________________________________________________________");\
  Serial.flush();
//----------------------------------------------------------------------------------------------------
#define DEBUG_EXECUTE_(FUNC_X) FUNC_X
//----------------------------------------------------------------------------------------------------


#define Debug_print(FUNC_X) Serial.print(FUNC_X); Serial.flush()
#define Debug_println(FUNC_X) Serial.println(FUNC_X); Serial.flush()



#else
#define DB_print(FUNC_X) 
#define DB_println(FUNC_X) 
#define DEBUG_MEASURE_TIME(func) func
#define DEBUG_MEASURE_TIME0(func) func
#define DEBUG_EXECUTE(FUNC_X)
#endif


#endif  //_PAT_DEBUG_H


