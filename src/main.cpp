#include <iostream>
#include <SPIFFS.h>
#include <config.hh>
#include <connection.hh>
#include <webserver.hh>

#include <usecase.hh>
#include <WiFi.h>
#include <PubSubClient.h>
#include <mqtt.hh>


Connection* connectionHandler;
WebServer* webserver;
MQTT_handler* mqtt;

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);

    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
    }
    
    connectionHandler = new Connection();
  
    String ssid, pw;
    std::tie(ssid, pw) = config::getWifiCredentialsfromwpaconf();
    if(ssid!=""){
      Serial.print("Trying to connect to ");
      Serial.println(ssid);
      if(connectionHandler->wifi_sta_setup(ssid.c_str(), pw.c_str())){
          // start mqtt stuff
          mqtt = new MQTT_handler(usecase::callback);
      };
    }else{
      Serial.println("Cant find config");
      connectionHandler->wifi_ap_setup();
    }
    webserver = new WebServer();
}


void loop() {
  if (mqtt){
    mqtt->loop();
  }
}
