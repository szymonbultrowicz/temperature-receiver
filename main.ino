#include "config.h"
#include "Receiver.h"

Receiver receiver(RX_PIN);

char mode = 'U';
unsigned short temperature = 0;
unsigned short humidity = 0;

void setup()
{
    Serial.begin(BAUD_RATE);
}

void loop()
{
    if(receiver.isAvailable()) {
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
