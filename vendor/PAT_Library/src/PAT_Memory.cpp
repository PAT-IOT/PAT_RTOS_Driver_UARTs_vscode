#include <Arduino.h>
#include <Preferences.h>
#include <PAT_Memory.h>
#include "SPIFFS.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Preferences preferences;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// constructor
class_nonVolatileMemory::class_nonVolatileMemory() {

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_nonVolatileMemory::init(const char* nameSpace) {
  //preferences.begin(nameSpace, false);
  //preferences.begin("my-app", false);
  // EEPROM.begin(512); // Initialize EEPROM with 512 bytes
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_nonVolatileMemory::write(const char* key, String str) {
  // preferences.begin("nvs", false);
  // preferences.putString(key, str);
  // preferences.end();
}

void class_nonVolatileMemory::write(const char* key, int value) {
  // preferences.begin("nvs", false);
  // preferences.putInt(key, value);
  // preferences.end();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int class_nonVolatileMemory::read(const char* key, String& str) {
  // preferences.begin("nvs", true);
  // str = preferences.getString(key, "");
  // preferences.end();
  // return str.length();  // Return the length of the string read from preferences
  return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void class_nonVolatileMemory::update(const char* key, int value) {
  //preferences.putInt(key, value);
  //if(preferences.getString(key.c_str(), "") != ""){
  //preferences.putString(key.c_str(), value.c_str());
  //int existing = EEPROM.read(address); // Read current value at address
  //if (existing != value){
  //    EEPROM.write(address, value); // Write new value if it is different
  //    EEPROM.commit(); // Commit the write to the EEPROM
  //}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// template <typename T>
// class_file<T>::class_file(const char* nameFile) {
//   nameFile = nameFile;
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*template <typename T>
void class_file<T>::init() {
  // You may need to add your SPIFFS initialization code here
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*template <typename T>
bool class_file<T>::write(T data) {
  File file = SPIFFS.open(nameFile, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return false;
  }
  file.write((uint8_t*)&data, sizeof(data));
  file.close();
  return true;
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// template <typename T>
// bool class_file<T>::read((void*)& data) {
//   File file = SPIFFS.open(nameFile, "r");
//   if (!file) {
//     Serial.println("Failed to open file for reading");
//     return false;
//   }
//   // Your code to read data from the file into the provided 'data' object
//   //file.read((uint8_t*)&data, sizeof(data));
//   file.close();

//   return true;
// }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*template <typename T>
bool class_file<T>::append(T data) {
  // File file = SPIFFS.open(nameFile, "a");
  // if (!file) {
  //   Serial.println("Failed to open file for appending");
  //   return false;
  // }

  // //file.print(data);
  // file.close();
  return true;
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







