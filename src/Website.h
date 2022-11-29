#ifndef WEBSITE_H
#define WEBSITE_H
#include <Arduino.h>
#include <WiFi.h>

class Website
{
public:
    Website() = default;

    void HomePage(WiFiClient* client);

private:
    void SendSuccessHeader(WiFiClient* client); //Send a 200 OK header
    void SendFooter(WiFiClient* client); //Send a footer
    void SendFailureHeader(WiFiClient* client); //Send a 404 Not Found header
};


#endif