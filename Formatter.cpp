#include "Formatter.h"

char *format(float value, uint8_t width, uint8_t precision, char *buffer)
{
    dtostrf(value, width, precision, buffer);
    return buffer;
}

char *Formatter::formatTemperature(uint16_t value, char *buffer)
{
    return format(value / 100.0, 4, 1, buffer);
}

char *Formatter::formatHumidity(uint16_t value, char *buffer)
{
    return format(value / 100.0, 2, 0, buffer);
}

char *Formatter::formatVoltage(uint16_t value, char *buffer)
{
    return format(value / 1000.0, 4, 2, buffer);
}
