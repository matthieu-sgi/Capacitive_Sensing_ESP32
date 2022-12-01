#ifndef AsyncWEBSERVER_H
#define WEBSERVER_H
#include <Arduino.h>
#include "Website.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

class AsyncWebserver
{
public:
    Webserver() = default;
    Webserver(HardwareSerial* serial){this->serial = serial;};
    void setupWebServer(const char* ssid, const char* password);
    void loopWebServer();
private:
    HardwareSerial* serial;
    Website website = Website(serial);
    String header;
    AsyncWebServer server = AsyncWebServer(80);
};


#endif