#include "PAT_Prototype.h"
#include <PAT_Memory.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class_JSON        JSONx  ("JSONx" , "JSONx");
class_JSON        JSON1_actionRelay   (_TOPIC1 , "action_relay"  );
class_JSON        JSON1_reportRelay   (_TOPIC1 , "report_relay"  );
class_JSON        JSON1_weeklySchedule (_TOPIC1 , "weeklySchedule");
class_JSON        JSON1_setDateTime    (_TOPIC1 , "setDateTime"   );

class_file<class_UserBuffer> file_class_UserBuffer("file_class_UserBuffer.bin");
class_UserBuffer ubuf;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class_JSON::class_JSON(const char* mytopic, const char* mykey) /*: vdoc( 2048 , SpiRamAllocator())*/ {
    topic = mytopic;
    key = mykey;
    payloadFlag = 0;
    payloadTemporaryFlag = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_JSON::save(MemoryJsonDocument<_JSON_DOCUMENT_SIZE>& dB_nvs) {
  String jsonString = "";
  serializeJson(dB_nvs, jsonString);
  class_nonVolatileMemory::write(this->key.c_str(), jsonString);  // Inherited from nonVolatileMemory
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_JSON::load(MemoryJsonDocument<_JSON_DOCUMENT_SIZE>& dB_nvs) {
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
void class_UserBuffer::save(String str) {
  if (str == "relay")
  {
    char out[100];
    int result = snprintf(out, 100, "{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}", 
      this->relay[0], this->relay[1], this->relay[2], this->relay[3], 
      this->relay[4], this->relay[5], this->relay[6], this->relay[7], 
      this->relay[8], this->relay[9], this->relay[10], this->relay[11]);
    
    class_nonVolatileMemory::write(str.c_str(), String(out));
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_UserBuffer::load(String str) {
  if (str == "relay"){
    int val[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    char out[100];
    String strloaded;
    class_nonVolatileMemory::read(str.c_str(), strloaded);
    if (sscanf(strloaded.c_str(), "{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}", \
      val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8], val[9], val[10], val[11]) == 12)
    {
      for (int i = 0; i < 12; i++)
      {
        this->relay[i] = val[i];
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
  if (!payloadError)
  {
    this->dB = this->vdoc;
    this->save(this->dB);
    this->payloadFlag = 1;
    return 1;
  } 
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_JSON::putTemporary(const String& payload) {
  this->payloadError = deserializeJson(this->vdoc, payload);
  if (!payloadError)
  {
    this->dB = this->vdoc;
    Serial.println("Json is Valid : ");
    serializeJson(this->dB, Serial);
    Serial.println();
    return 1;
  }
  Serial.println("Json isNot Valid : ");
  Serial.println(payloadError.c_str());
  return 0;
}
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



