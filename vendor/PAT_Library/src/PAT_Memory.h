#ifndef PAT_MEMORY_H
#define PAT_MEMORY_H
#include "SPIFFS.h"
#include "PAT_Debug.h"

#define DB_println(xxx) Debug_println(xxx) 
//#define DB_println(xxx) 

#define DB_print(xxx) Debug_print(xxx) 
//#define DB_print(xxx) 
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
        DB_println("Failed to mount file system");
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
        file.close();
        SPIFFS.mkdir(path);
        File file = SPIFFS.open(path, "w");
        if (file)
        {
            size_t bytesWritten = file.write((uint8_t*)&data, sizeof(data));
            file.close();
            if (bytesWritten == sizeof(data))   return true;
        }
        file.close();
    }
    //----------------------------------------------------
    DB_println("Failed to open file for writing");
    return false;
    }
    //===============================================================================================================================================================================
    bool save(const T& data) {
        for (size_t i = 0; i < 3; i++)
        {
            if (this->write(data)) return true;
        }
        return false;
    }
    //===============================================================================================================================================================================
    bool read(const T& data){
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
            if (bytesRead == sizeof(data))
            {
            //---------
            DB_println("File content: read");
            // DB_print("File content: ");
            // for (size_t i = 0; i < sizeof(data); ++i) {
            //     DB_print(((uint8_t*)&data)[i]);
            //     DB_print(' ');
            // }
            //  DB_println(); 
             //---------
             return true;
            }
        }
        file.close();
        //----------------------------------------------------
        DB_println("Failed to open file for readding");
        return false;
    }
    //===============================================================================================================================================================================
    bool load(const T& data) {       
        for (size_t i = 0; i < 3; i++)
        {
            if (this->read(data)) return true;
        }
        return false;
    }
    //===============================================================================================================================================================================
};




















#undef DB_println
#undef DB_print
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  // PAT_MEMORY_H

