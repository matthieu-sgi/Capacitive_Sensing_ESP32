#ifndef WEBSERVER2_H
#define WEBSERVER2_H
#include <Arduino.h>
// #include "Website.h"
#include "WiFi.h"
#include <ESPAsyncWebServer.h>

class WebServer
{
public:
    WebServer() = default;
    WebServer(HardwareSerial* serial){this->serial = serial;};
    void setupWebServer(const char* ssid, const char* password);
    void loopWebServer();
    static String processor(const String& var);
    AsyncWebServer server = AsyncWebServer(80);
private:
    HardwareSerial* serial;
    // Website website = Website(serial);
    String header;
    static String outputState(int output);
};


#endif