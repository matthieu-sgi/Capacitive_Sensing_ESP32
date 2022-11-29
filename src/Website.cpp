#include <Arduino.h>
#include <WiFi.h>

#include "Website.h"

void Website::HomePage(WiFiClient* client)
{
    SendSuccessHeader(client);
    client->println("<h1>Home</h1>");
    SendFooter(client);
}

void Website::SendSuccessHeader(WiFiClient* client){
    client->println("HTTP/1.1 200 OK");
    client->println("Content-type:text/html");
    client->println("Connection: close");
    client->println();
}

void Website::SendFailureHeader(WiFiClient* client){
    client->println("HTTP/1.1 404 Not Found");
    client->println("Content-type:text/html");
    client->println("Connection: close");
    client->println();
}

void Website::SendFooter(WiFiClient* client){
    client->println();
}