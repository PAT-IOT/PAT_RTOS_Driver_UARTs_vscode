
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//#include <WebServer.h>
#include <ESPmDNS.h>
#include "PAT_Prototype.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "PAT_Task_WebServer.h"


/// موارد مورد نیاز جهت نمایش در وب سرور
/// وضعیت تمامی رله ها ( بصورت آرایه ای )
/// توکن
/// وضعیت اتصال ام کیو تی تی connedted / disconnected
/// وضعیت اتصال به اینترنت
/// روشن یا خاموش بودن وای فای
/// آی پی
/// مک آدرس
/// سریال نامبر
/// تعداد رله ها
/// 
static AsyncWebServer webServer(80);
//WebServer server(80);
/* Put your SSID & Password */
const char* webServer_ssid = _WEBSERVER_SSID_NAME;            //Novaday Enter SSID here
const char* webServer_password  =  _WEBSERVER_PASSWORD_NAME;    //"11112222"  //Enter Password here
/* Put IP Address details */
// IPAddress webServer_local_ip(192,168,1,1);
// IPAddress webServer_gateway(192,168,1,1);
// IPAddress webServer_subnet(255,255,255,0);
IPAddress webServer_local_ip(192,168,137,185);
IPAddress webServer_gateway(192,168,1,1);
IPAddress webServer_subnet(255,255,255,0);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int webServerInit() {
    static bool initialized = false;
    if (initialized)return 1;
      // Initialize SPIFFS
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        initialized = false;
        return 0;
    }
    WiFi.mode(WIFI_AP_STA);  //ESP32 Access point configured
    WiFi.softAP(_WEBSERVER_SSID_NAME, _WEBSERVER_PASSWORD_NAME);
    WiFi.softAPConfig(webServer_local_ip, webServer_gateway, webServer_subnet);
    delay_OS(500);
        if (MDNS.begin(_WEBSERVER_SSID_NAME)) // Set the hostname to "Novaday"
        {  
            Serial.print("softAPIP=");
            Serial.println(WiFi.softAPIP());
            serverRequest();
            initialized = 1;
            return 1;
        }
    initialized = false;
    Serial.println("webServer was failed");
      return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Config {
    const char* WEBSOCKET_SERVER_IP;
    const char* WEBSOCKET_SERVER_IP_ARRAY;
    const char* PASSWORD_SERVER;
    const char* USERNAME_SERVER;
    const char* CLIENT_NAME;
    const char* WEBSOCKET_PORT;
    const char* SEPARATOR_PATH;
    const char* URL_PATH;
    const char* TOPIC[3];
    const char* WIFI_SSID[3];
    const char* WIFI_PASSWORD[3];
};

Config Config_webServer;


void serverRequest() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Serve index.html on root request 
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });

    webServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });
    webServer.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send(SPIFFS, "/bootstrap.min.css", "text/css");
      });

    
    webServer.on("/javascript.js", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(SPIFFS, "/javascript.js", "application/js");
      });

    webServer.on("/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send(SPIFFS, "/jquery.min.js", "application/js");
      });
    webServer.on("/bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send(SPIFFS, "/bootstrap.min.js", "application/js");
      });
    

    // Handle POST request to update configuration
    webServer.on("/updateConfig", HTTP_POST, [](AsyncWebServerRequest *request){
        // Collect data from the request
        if (request->hasParam("WEBSOCKET_SERVER_IP", true)) {
            const char* value = request->getParam("WEBSOCKET_SERVER_IP", true)->value().c_str();
            Config_webServer.WEBSOCKET_SERVER_IP = strdup(value);  // Assign the const char* directly
        }
        // ... (Repeat for other parameters)

        // Respond with success or failure
        request->send(200, "text/plain", "Configuration updated successfully");
    });

    webServer.begin();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
String processor(const String& var) {
  Serial.println(var);
  if(var == "STATE"){
    return "On or Off";
  }
  return String();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void serverRequest(void)
{
  // Route for root / web page
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  webServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  webServer.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    // digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  webServer.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    // digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  webServer.begin();
  Serial.println("HTTP server started");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/



/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int webServerInit() {
    static bool initialized = false;
    if (initialized)return 1;
    WiFi.mode(WIFI_AP_STA);  //Access point configured
    WiFi.softAP(webServer_ssid, webServer_password);
    WiFi.softAPConfig(webServer_local_ip, webServer_gateway, webServer_subnet);
    delay_OS(500);
        if (MDNS.begin(webServer_ssid)) // Set the hostname to "Novaday"
        {  
            Serial.print("softAPIP=");
            Serial.println(WiFi.softAPIP());
            serverRequest();
            initialized = 1;
            return 1;
        }
    initialized = false;
    Serial.println("webServer was failed");
      return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void serverRequest(void)
{
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        String html = "<!DOCTYPE html>"
                      "<html>"
                      "<head>"
                      "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                      "<title> IoT Control</title>"
                      "<style>"
                      "body { text-align: center; margin-top: 50px; background-color: #f0f8ff; color: #333; }"
                      "h1 { font-size: 36px; color: #003366; }"
                      "p { font-size: 18px; color: #333; }"
                      "button { font-size: 18px; padding: 10px 20px; margin: 5px; }"
                      "</style>"
                      "</head>"
                      "<body>"
                      "<h1> IoT Control</h1>"
        //--------------------------------------------------------------------------------------
            "<script>"
            "for (int i = 0; i < 12; ++i)"
            "{"
            "<p>Relay + String.valueOf(i + 1)+:"
            "<input type='checkbox' id='\"/Relay + String.valueOf(i + 1) + ' name='\"/Relay + String.valueOf(i + 1) + ' value='off'>"
            "<a href=\"/Relay + String.valueOf(i + 1) + on\"><button style=\"background-color: #4CAF50; color: white;\">Turn ON</button></a>&nbsp;"
            "<a href=\"/Relay + String.valueOf(i + 1) + off\"><button style=\"background-color: #f44336; color: white;\">Turn OFF</button></a></p>";
        "}"
        //----------------------------------------------------------------
        " alert('PAT: Page wasn't Found');</script></body></html>";
        //+ String(_RELAY_NUMBER) +
        request->send(200, "text/html", html);
    });
    //========================================================================================================================================================================
    for (int i = 0; i < _RELAY_NUMBER; ++i)
    {
        String relayOnEndpoint = "/Relay" + String(i + 1) + "on";
        String relayOffEndpoint = "/Relay" + String(i + 1) + "off";

        webServer.on(relayOnEndpoint.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request)
        {
            ubuf.relayM[i] = 1;
            request->redirect("/");
        });

        webServer.on(relayOffEndpoint.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request)
        {
            ubuf.relayM[i] = 0;
            request->redirect("/");
        });
    }
  webServer.begin();
  Serial.println("HTTP server started");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*void serverinit() {
    static bool initialized = false;
    for (int i = 0; i < _RELAY_NUMBER; i++)
    {
        ubuf.relayMode[i] = 'm';
    }
         if (WiFi.status() != WL_CONNECTED)
    {
        setup = false;
        WiFi_Init();
    }
    else if (!setup)
    {
        setup = true;
        WiFi_PrintStatus();
        serverRequest();
         }      
}*/




















/*void serverRequest(void)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        String html = "<html><body><h1 style=\"font-size: 128px;\">Relay Test</h1>";
        //--------------------------------------------------------------------------------------
        for (int i = 0; i < _RELAY_NUMBER; ++i)
        {
            html += "<p style=\"font-size: 24px;\">Relay" + String(i+1) + ":<a href=\"/Relay" + String(i+1) + "on\"><button style=\"font-size: 72px; padding: 20px 60px;\"  >ON</button></a>&nbsp;<a href=\"/Relay" + String(i+1) + "off\"><button style=\"font-size: 72px; padding: 20px 60px;\">OFF</button></a></p>";
        }
        //----------------------------------------------------------------
        html += "</body></html>";
        request->send(200, "text/html", html);
    });
    //========================================================================================================================================================================
    for (int i = 0; i < _RELAY_NUMBER; ++i)
    {
        String relayOnEndpoint = "/Relay" + String(i+1) + "on";
        String relayOffEndpoint = "/Relay" + String(i+1) + "off";

        server.on(relayOnEndpoint.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request)
        {
            ubuf.relayM[i] = 1;
            request->redirect("/");
        });

        server.on(relayOffEndpoint.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request)
        {
            ubuf.relayM[i] = 0;
            request->redirect("/");
        });
    }
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void serverRequest(void)
{
    //========================================================================================================================================================================
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String html = "<html><body><h1 style=\"font-size: 128px;\">Relay0 Test</h1>";
//--------------------------------------------------------------------------------------
  html += "<p style=\"font-size: 72px;\">Relay1:<a href=\"/Relay1on\"><button style=\"font-size: 72px; padding: 20px 60px;\"  >ON</button></a>&nbsp;<a href=\"/Relay1off\"><button style=\"font-size: 72px; padding: 20px 60px;\">OFF</button></a></p>";
  html += "<p style=\"font-size: 72px;\">Relay2:<a href=\"/Relay2on\"><button style=\"font-size: 72px; padding: 20px 60px;\"  >ON</button></a>&nbsp;<a href=\"/Relay2off\"><button style=\"font-size: 72px; padding: 20px 60px;\">OFF</button></a></p>";
  html += "<p style=\"font-size: 72px;\">Relay3:<a href=\"/Relay3on\"><button style=\"font-size: 72px; padding: 20px 60px;\"  >ON</button></a>&nbsp;<a href=\"/Relay3off\"><button style=\"font-size: 72px; padding: 20px 60px;\">OFF</button></a></p>";
  html += "<p style=\"font-size: 72px;\">Relay4:<a href=\"/Relay4on\"><button style=\"font-size: 72px; padding: 20px 60px;\"  >ON</button></a>&nbsp;<a href=\"/Relay4off\"><button style=\"font-size: 72px; padding: 20px 60px;\">OFF</button></a></p>";
  //----------------------------------------------------------------
  html += "</script></body></html>";
   request->send(200, "text/html", html); });
  //========================================================================================================================================================================
  server.on("/Relay1on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[0] = 1;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay1off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[0] = 0;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay2on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[1] = 1;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay2off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[1] = 0;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay3on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[2] = 1;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay3off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[2] = 0;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay4on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[3] = 1;
          request->redirect("/"); });
  //========================================================================================================================================================================
  server.on("/Relay4off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
          ubuf.relayM[3] = 0;
          request->redirect("/"); });
  //========================================================================================================================================================================
}
*/















