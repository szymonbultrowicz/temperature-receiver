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
BatteryLevel batteryLevelCalculator(4400, 6300);
LEDNotifier ledNotifier(LED_PIN);

uint16_t temperature = 0;
uint16_t humidity = 0;
uint16_t voltage = 0;
uint8_t batteryLevel = 0;
char formattedTemperature[8];
char formattedHumidity[8];
char formattedVoltage[8];

unsigned long ledTimeout = 0;

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    lcd.init();
    analogWrite(5, 150);
}

void updateState(char mode, uint16_t value)
{
    switch (mode)
    {
    case 'T':
        temperature = value;
        formatter.formatTemperature(value, formattedTemperature);
        break;
    case 'H':
        humidity = value;
        formatter.formatHumidity(value, formattedHumidity);
        break;
    case 'V':
        voltage = value;
        formatter.formatVoltage(value, formattedVoltage);
        batteryLevel = batteryLevelCalculator.calculate(value);
        break;
    }
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

        updateState(reading.mode, reading.value);

        if (reading.valid)
        {
            lcd.writeValues(
                formattedTemperature, 
                formattedHumidity, 
                formattedVoltage,
                batteryLevel
                );
        }

        ledNotifier.notify();
    }

    ledNotifier.tryTurnOff();
}
