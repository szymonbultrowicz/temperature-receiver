#include "LEDNotifier.h"

#define LED_DURATION 100 // ms

LEDNotifier::LEDNotifier(uint8_t pin)
{
    this->pin = pin;
}

void LEDNotifier::notify()
{
    this->timeout = millis() + LED_DURATION;
    digitalWrite(this->pin, HIGH);
}

void LEDNotifier::tryTurnOff()
{
    if (this->timeout > 0 && millis() > this->timeout)
    {
        digitalWrite(this->pin, LOW);
        this->timeout = 0;
    }
}