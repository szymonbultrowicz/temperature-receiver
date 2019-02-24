#include <Arduino.h>

class Formatter
{
  public:
    char* formatTemperature(int16_t value, char* buffer);
    char* formatHumidity(int16_t value, char* buffer);
    char* formatVoltage(int16_t value, char* buffer);
    char* formatBatteryLevel(int16_t value, char* buffer);
};
