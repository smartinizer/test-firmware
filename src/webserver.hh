#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <iostream>
#include <string>

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
            request->send(404, "text/plain", "Not found");
        }


class WebServer{

    public: WebServer(){
        // Send web page with input fields to client
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/index.html", String(), false);
        });

        // Route to load style.css file
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/style.css", "text/css");
        });
        // Route to connect
        server.on("/connect", HTTP_POST, [](AsyncWebServerRequest *request){
            Serial.print("Connect pressed!!");
            String ssid = "";
            String pw = "";
            if(request->hasParam("ssid", true) && request->hasParam("pw", true)){
                Serial.println("Got credentials");
                ssid = request->getParam("ssid", true)->value();
                pw = request->getParam("pw", true)->value();
            }
            request->redirect("/");
            config::writeWifiCredentials(ssid,pw);
            ESP.restart();
        });

        server.onNotFound(notFound);

        server.begin();

        Serial.println("HTTP server started");
    }

};
