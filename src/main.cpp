#include <Arduino.h>

const int LED = 8;

void blink_burst(int, int);

void setup()
{
    Serial.begin(460800);
    pinMode(LED, OUTPUT);
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
