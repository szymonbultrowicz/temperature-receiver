#include <Arduino.h>

class Formatter
{
  public:
    char* formatTemperature(uint16_t value, char* buffer);
    char* formatHumidity(uint16_t value, char* buffer);
    char* formatVoltage(uint16_t value, char* buffer);
    char* formatBatteryLevel(uint16_t value, char* buffer);
};
