#include "AsyncWebServer.h"
#include "Arduino.h"
#include "WiFi.h"
#include "Website.h"
#include <SPIFFS.h>
#include "ESPAsyncWebServer.h"




// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

bool serialState = false;



void AsyncWebserver::setupWebServer(const char* ssid, const char* password) {
  // Connect to Wi-Fi network with SSID and password

    WiFi.mode(WIFI_AP);
    
    serial->print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    if(sizeof(password) < 1){
        WiFi.softAP(ssid);
    }
    else WiFi.softAP(ssid,password);
    IPAddress IP = WiFi.softAPIP();

    serial->print("AP IP address: ");
    serial->println(IP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });

    server.begin();

}

void AsyncWebserver::loopWebServer(){

  
}
