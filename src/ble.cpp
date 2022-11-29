#include  "ble.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>

//BLE server name
#define bleServerName "Plant_Capacitive_Sensor"



int touchValue = 0;


// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;

bool deviceConnected = false;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "0399a89a-6f4e-11ed-a1eb-0242ac120002"


//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

BLECharacteristic capaSensorCharacteristic("bbf83094-6f50-11ed-a1eb-0242ac120002", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor capaSensorDescriptor(BLEUUID((uint16_t)0x2f23));

int touchPin;

int ble_setup(const int TOUCH_PIN) {
  touchPin = TOUCH_PIN;
  
  // Serial.begin(115200);
  // Create the BLE Device
  BLEDevice::init(bleServerName);

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *capaSensorService = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristics and Create a BLE Descriptor
  // Capacitive Sensor
  
    capaSensorService->addCharacteristic(&capaSensorCharacteristic);
    capaSensorDescriptor.setValue("Capacitive Sensor value");
    capaSensorCharacteristic.addDescriptor(&capaSensorDescriptor);



  // Start the service
  capaSensorService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  // Serial.println("Waiting a client connection to notify...");
  return 0;

}

int ble_loop() {
  if (deviceConnected) {
    if ((millis() - lastTime) > timerDelay) {
      // Read temperature as Celsius (the default)
      touchValue = touchRead(touchPin);


      //Set humidity Characteristic value and notify connected client
      capaSensorCharacteristic.setValue(touchValue);
      capaSensorCharacteristic.notify();   
      // Serial.print(" - Capacitive sensor value: ");
      // Serial.println(touchValue);
      
      lastTime = millis();
    }
  }
  return touchValue;
}
