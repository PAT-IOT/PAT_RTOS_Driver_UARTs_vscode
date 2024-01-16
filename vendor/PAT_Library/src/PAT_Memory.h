#ifndef PAT_MEMORY_H
#define PAT_MEMORY_H
#include "SPIFFS.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class class_nonVolatileMemory {
private:

public:
  class_nonVolatileMemory();
  void init(const char* nameSpace);
  void write(const char* key, String str);
  void write(const char* key, int value);
  int read(const char* key, String& str);
  void update(const char* key, int value);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class class_file {
private:
    String path;
    bool initialized = false;
public:
//===============================================================================================================================================================================
    class_file(const char* nameFile) {
        path = "/" + String(nameFile);
        if (SPIFFS.begin(true)){
            initialized = true;
        }
        else
        {
        initialized = false;
        Serial.println("Failed to mount file system");
        }
    }
//===============================================================================================================================================================================
    bool write(const T & data) {
    //----------------------------------------------------
    if (!initialized)
        if (SPIFFS.begin(true))
            initialized = true;
    //----------------------------------------------------
    File file = SPIFFS.open(path, "w");
    //----------------------------------------------------
    if (file)
    {
        size_t bytesWritten = file.write((uint8_t*)&data, sizeof(data));
        file.close();
        if (bytesWritten == sizeof(data))   return true;
    }
    //----------------------------------------------------
    else if (!SPIFFS.exists(path))
    {
        SPIFFS.mkdir(path);
        File file = SPIFFS.open(path, "w");
        if (file)
        {
            size_t bytesWritten = file.write((uint8_t*)&data, sizeof(data));
            file.close();
            if (bytesWritten == sizeof(data))   return true;
        }
    }
    //----------------------------------------------------
    Serial.println("Failed to open file for writing");
    return false;
    }
    //===============================================================================================================================================================================
    bool save(const T& data) {
        return (this->write(data));
    }
    //===============================================================================================================================================================================
    bool read(const T& data) {
        //----------------------------------------------------
        if (!initialized)
            if (SPIFFS.begin(true))
                initialized = true;
        //----------------------------------------------------
        File file = SPIFFS.open(path, "r");
        //----------------------------------------------------
        if (file)
        {
            size_t bytesRead = file.read((uint8_t*)&data, sizeof(data));
            file.close();
            if (bytesRead == sizeof(data)) return false;
            //---------
            Serial.print("File content: ");
            for (size_t i = 0; i < sizeof(data); ++i) {
                Serial.print(((uint8_t*)&data)[i]);
                Serial.print(' ');
            }
            Serial.println();
            //---------
        }
        //----------------------------------------------------
        Serial.println("Failed to open file for writing");
        return false;
    }
    bool load(const T& data) {
        return (this->read(data));
    }
    //===============================================================================================================================================================================
};





















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // PAT_MEMORY_H

