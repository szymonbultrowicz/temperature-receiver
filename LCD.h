#ifndef LCD_h
#define LCD_h

#include <LiquidCrystal.h>
#include <Arduino.h>

class LCD
{
public:
  LCD(uint8_t startPin, uint8_t backlightPin);
  void init();
  void writeValues(char *temp, char *humidity, char *voltage, uint8_t level);

private:
  LiquidCrystal* lcd;
  uint8_t backlightPin;
};

#endif