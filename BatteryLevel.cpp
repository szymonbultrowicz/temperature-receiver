#include "BatteryLevel.h"

/**
 * Symmetric sigmoidal approximation
 * https://www.desmos.com/calculator/7m9lu26vpy
 *
 * c - c / (1 + k*x/v)^3
 */
static inline uint8_t sigmoidal(uint16_t voltage, uint16_t minVoltage, uint16_t maxVoltage) {
	// slow
	// uint8_t result = 110 - (110 / (1 + pow(1.468 * (voltage - minVoltage)/(maxVoltage - minVoltage), 6)));

	// steep
	// uint8_t result = 102 - (102 / (1 + pow(1.621 * (voltage - minVoltage)/(maxVoltage - minVoltage), 8.1)));

	// normal
	uint8_t result = 105 - (105 / (1 + pow(1.724 * (voltage - minVoltage)/(maxVoltage - minVoltage), 5.5)));
	return result >= 100 ? 100 : result;
}

/**
 * Linear mapping
 * https://www.desmos.com/calculator/sowyhttjta
 *
 * x * 100 / v
 */
static inline uint8_t linear(uint16_t voltage, uint16_t minVoltage, uint16_t maxVoltage) {
	return (unsigned long)(voltage - minVoltage) * 100 / (maxVoltage - minVoltage);
}

BatteryLevel::BatteryLevel(uint16_t minV, uint16_t maxV)
{
    this->minV = minV;
    this->maxV = maxV;
}

uint8_t BatteryLevel::calculate(uint16_t voltage)
{
    return voltage > 0 ? sigmoidal(voltage, this->minV, this->maxV) : 0;
}
