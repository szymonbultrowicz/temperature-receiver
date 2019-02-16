#include "Formatter.h"

char *format(uint16_t value, float divider, uint8_t width, uint8_t precision, char *buffer)
{
    if (value == 0) {
        for (int i = 0; i < width; i++)
        {
            buffer[i] = '-';
        }
        buffer[width] = '\0';
        return buffer;
    }
    dtostrf((float)value / divider, width, precision, buffer);
    return buffer;
}

char *Formatter::formatTemperature(uint16_t value, char *buffer)
{
    return format(value, 100.0, 4, 1, buffer);
}

char *Formatter::formatHumidity(uint16_t value, char *buffer)
{
    return format(value, 100.0, 2, 0, buffer);
}

char *Formatter::formatVoltage(uint16_t value, char *buffer)
{
    return format(value, 1000.0, 4, 2, buffer);
}

char *Formatter::formatBatteryLevel(uint16_t value, char *buffer)
{
    return format(value, 1.0, 3, 0, buffer);
}
