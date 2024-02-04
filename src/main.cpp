#include <Arduino.h>
#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define DEVICE_NAME "esp32-rgb-crystal-"
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


const int LED = 8;

void blink_burst(int, int);

void setup()
{
    Serial.begin(460800);
    pinMode(LED, OUTPUT);

    uint32_t chipID = ESP.getEfuseMac();

    // Den Chip-Namen erstellen
    String device_name = DEVICE_NAME + String(chipID, HEX);


    Serial.printf("Starting BLE work as %s...\n", device_name.c_str());

    BLEDevice::init(device_name.c_str());
    BLEServer* pServer = BLEDevice::createServer();
    BLEService* pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic* pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE
    );


    pCharacteristic->setValue("Hello World says Neil");
    pService->start();
    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("BLE is advertising.");
}

void loop()
{
    for (int i = 0; i < 3; i++)
    {
        Serial.println("HIGH");
        digitalWrite(LED, HIGH);
        delay(1000);
        Serial.println("LOW");
        digitalWrite(LED, LOW);
        delay(1000);
    }
    blink_burst(5, 100);
}

void blink_burst(int n, int sleep)
{
    bool value = false;
    for (int i = 0; i < n * 2; i++)
    {
        digitalWrite(LED, value);
        value = !value;
        delay(sleep);
    }
}
