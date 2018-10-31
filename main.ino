#include "config.h"
#include "Receiver.h"
#include "Reading.h"

#define LED_DURATION 100 // ms

Receiver receiver(RX_PIN);

uint16_t temperature = 0;
uint16_t humidity = 0;
uint16_t voltage = 0;


unsigned long ledTimeout = 0;

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    if(receiver.isAvailable()) {
        digitalWrite(LED_PIN, HIGH);
        ledTimeout = millis() + LED_DURATION;

        Reading reading = receiver.receive();
        Serial.print(reading.mode);
        Serial.print(" ");
        Serial.print(reading.value);
        Serial.print(" ");
        Serial.println(reading.valid);
    }
    
    if (ledTimeout > 0 && millis() > ledTimeout) {
        digitalWrite(LED_PIN, LOW);
    }
}
