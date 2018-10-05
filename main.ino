#include "config.h"
#include "Receiver.h"

#define LED_DURATION 100 // ms

Receiver receiver(RX_PIN);

char mode = 'U';
unsigned short temperature = 0;
unsigned short humidity = 0;

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

        unsigned long value = receiver.receive();
        if (isMode(value)) {
            mode = (char)value;
            Serial.print("New mode: ");
            Serial.println(mode);
        } else {
            updateValue(value);
            Serial.print("Got value: ");
            Serial.println(value);
        }
    }
    
    if (ledTimeout > 0 && millis() > ledTimeout) {
        digitalWrite(LED_PIN, LOW);
    }
}

boolean isMode(unsigned long value) {
    return (char)value == 'H'
        || (char)value == 'T';
}

void updateValue(unsigned long value) {
    switch (mode) {
        case 'T':
            temperature = (unsigned short) value;
            break;
        case 'H':
            humidity = (unsigned short) humidity;
            break;
        default:
            Serial.print("Received value in unknown mode ");
            Serial.println(mode);
    }
}
