#include <Arduino.h>

class LEDNotifier
{
  public:
    LEDNotifier(uint8_t pin);
    void notify();
    void tryTurnOff();

  private:
    uint8_t pin;
    unsigned long timeout;
};