#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string value = pCharacteristic->getValue();
        if (value[0] == 'o') {
            digitalWrite(4, HIGH);
        }
        else if (value[0] == 'f') {
            digitalWrite(4, LOW);
        }


    }
};

void setup(){
    BLEDevice::init("SpidBot");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService("e7c32e81-19f6-4030-af20-f2fba2612556");
    BLECharacteristic *pCharacteristic = pService->createCharacteristic("67c9803f-9d13-4131-9465-2d36f29c603d", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    pCharacteristic->setCallbacks(new MyCallbacks());
    pService->start();
    pServer->getAdvertising()->start();
    Serial.begin(115200);
    pinMode(4, OUTPUT);

}

void loop(){
    // long cMillis = millis();
    // static long pMillis = 0;
    // int interval = 1000;
    // if(cMillis - pMillis >= interval){
    //     digitalWrite(4, !digitalRead(4));
    //     pMillis = cMillis;
    // }


}