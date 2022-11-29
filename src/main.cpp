#include <Arduino.h>
#include "WebServer.h"
// #include "OTA.h"
// #include "ble.h"

#define LED 2

const char* ssid = "Interactive_Plant";
const char* password = "";

static const int TOUCH_PIN = 4;

Webserver webserver;

void setup() {
  pinMode(LED,OUTPUT);

  Serial.begin(115200);
  Serial.println("Booting");
  webserver = Webserver(&Serial);
  webserver.setupWebServer(ssid, password);

}

void loop() {
  webserver.loopWebServer();

}