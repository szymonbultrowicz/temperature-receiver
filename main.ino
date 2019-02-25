#include "config.h"
#include "Receiver.h"
#include "Reading.h"
#include "LCD.h"
#include "Formatter.h"
#include "BatteryLevel.h"
#include "LEDNotifier.h"

#define LED_DURATION 100 // ms

Receiver receiver(RX_PIN);
LCD lcd(LCD_START_PIN, LCD_BACKLIGHT_PIN);

Formatter formatter;
BatteryLevel batteryLevelCalculator(MIN_BATTERY_LEVEL, MAX_BATTERY_LEVEL);
LEDNotifier ledNotifier(LED_PIN);

int16_t temperature = 0;
int16_t humidity = 0;
int16_t voltage = 0;
int8_t batteryLevel = 0;
char formattedTemperature[8];
char formattedHumidity[8];
char formattedVoltage[8];
char formattedBatteryLevel[8];

unsigned long lastRepaint = 0;

struct LastReadings
{
    unsigned long temperature = 0;
    unsigned long humidity = 0;
    unsigned long voltage = 0;
} lastReadings;

unsigned long ledTimeout = 0;

int16_t clearIfOutdated(unsigned long lastReading, int16_t value)
{
    return (millis() > lastReading + READING_TIMEOUT) ? 0 : value;
}

void updateState(char mode, int16_t value)
{
    switch (mode)
    {
    case 'T':
        temperature = value;
        lastReadings.temperature = millis();
        break;
    case 'H':
        humidity = value;
        lastReadings.humidity = millis();
        break;
    case 'V':
        voltage = value;
        lastReadings.voltage = millis();
        break;
    }
}

void formatValues()
{
    formatter.formatTemperature(temperature, formattedTemperature);
    formatter.formatHumidity(humidity, formattedHumidity);
    formatter.formatVoltage(voltage, formattedVoltage);
    batteryLevel = batteryLevelCalculator.calculate(voltage);
    formatter.formatBatteryLevel(batteryLevel, formattedBatteryLevel);
}

void checkOutdated()
{
    temperature = clearIfOutdated(lastReadings.temperature, temperature);
    humidity = clearIfOutdated(lastReadings.humidity, humidity);
    voltage = clearIfOutdated(lastReadings.voltage, voltage);
}

void repaint()
{
    formatValues();
    lcd.writeValues(
        formattedTemperature,
        formattedHumidity,
        formattedVoltage,
        formattedBatteryLevel);
    lastRepaint = millis();
}

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    lcd.init();
    analogWrite(5, 150);
}

void loop()
{
    if (receiver.isAvailable())
    {
        Reading reading = receiver.receive();
        Serial.print(reading.mode);
        Serial.print(" ");
        Serial.print(reading.value);
        Serial.print(" ");
        Serial.println(reading.valid);

        if (reading.valid)
        {
            updateState(reading.mode, reading.value);
        }

        ledNotifier.notify();
    }

    if (millis() > lastRepaint + REPAINT_INTERVAL) {
        checkOutdated();
        repaint();
    }

    ledNotifier.tryTurnOff();
}
