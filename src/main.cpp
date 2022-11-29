#include <Arduino.h>

// #include "OTA.h"
// #include "ble.h"

#define LED 2

const char* ssid = "PoleDeVinci_DVIC";
const char* password = "8PfURsp!dvic";

static const int TOUCH_PIN = 4;

void setup() {
  pinMode(LED,OUTPUT);

  Serial.begin(115200);


}

void loop() {
  
}