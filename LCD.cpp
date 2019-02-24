#include "LCD.h"

#define BACKLIGHT_INTENSITY 150

LCD::LCD(uint8_t startPin, uint8_t backlightPin)
{
    this->backlightPin = backlightPin;
    this->lcd = new LiquidCrystal(
        startPin,
        startPin + 1,
        startPin + 2,
        startPin + 3,
        startPin + 4,
        startPin + 5
    );
}

void LCD::init()
{
    analogWrite(this->backlightPin, BACKLIGHT_INTENSITY);
    this->lcd->begin(16, 2);
}

void LCD::writeValues(char *temp, char *humidity, char *voltage, char* level)
{
    this->lcd->clear();

    this->lcd->setCursor(0, 0);
    this->lcd->print(temp);
    this->lcd->print((char)223);
    this->lcd->print('C');

    this->lcd->setCursor(0, 1);
    this->lcd->print(humidity);
    this->lcd->print('%');

    this->lcd->setCursor(11, 0);
    this->lcd->print(voltage);
    this->lcd->print('V');

    this->lcd->setCursor(12, 1);
    this->lcd->print(level);
    this->lcd->print('%');
}
