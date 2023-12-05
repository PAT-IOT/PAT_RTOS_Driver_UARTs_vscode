
#include "PAT_Prototype.h"
#include <ESPAsyncWebServer.h>
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


AsyncWebServer server(80);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void serverinit() {
    static bool setup = false;
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
        server.begin();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void serverRequest(void)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
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
                      "<h1> IoT Control</h1>";

        //--------------------------------------------------------------------------------------
        for (int i = 0; i < _RELAY_NUMBER; ++i)
        {
          html += "<p>Relay " + String(i + 1) + ": "
            "<input type='checkbox' id='\"/Relay" + String(i + 1) + "' name='\"/Relay" + String(i + 1) + "' value='off'>"
            "<a href=\"/Relay" + String(i + 1) + "on\"><button style=\"background-color: #4CAF50; color: white;\">Turn ON</button></a>&nbsp;"
                    "<a href=\"/Relay" + String(i + 1) + "off\"><button style=\"background-color: #f44336; color: white;\">Turn OFF</button></a></p>";
        }
        //----------------------------------------------------------------
        html += " <script>alert('pat');</script></body></html>";

        request->send(200, "text/html", html);
    });
    //========================================================================================================================================================================
    for (int i = 0; i < _RELAY_NUMBER; ++i)
    {
        String relayOnEndpoint = "/Relay" + String(i + 1) + "on";
        String relayOffEndpoint = "/Relay" + String(i + 1) + "off";

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
}





















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















