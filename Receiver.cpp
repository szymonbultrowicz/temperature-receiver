#include "Receiver.h"
#include "FastCRC.h"

#define BYTE_SIZE 8
#define BUFF_SIZE 4
#define CRC_SIZE 1

union ReadingConverter {
    uint32_t raw;
    Reading reading;
};

Receiver::Receiver(unsigned int pin) {
    this->device = new RCSwitch();
    this->device->enableReceive(digitalPinToInterrupt(pin));
    this->CRC8 = new FastCRC8();
}

boolean Receiver::isAvailable() {
    return this->device->available();
}

Reading decodeReading(uint32_t receivedValue) {
    Reading reading;
    reading.mode = (receivedValue & 0xFF000000) >> 24;
    reading.value = (receivedValue & 0x00FFFF00) >> 8;
    reading.crc = receivedValue & 0x000000FF;
    return reading;
}

Reading Receiver::receive() {
    unsigned long receivedValue = this->device->getReceivedValue();
    Reading reading = decodeReading(receivedValue);
    reading.valid = verifyChecksum(reading);

    this->device->resetAvailable();
    return reading;
}

boolean Receiver::verifyChecksum(Reading reading) {
    uint8_t buff[BUFF_SIZE - CRC_SIZE];
    buff[0] = reading.mode;
    buff[1] = (reading.value & 0xFF00) >> BYTE_SIZE;
    buff[2] = reading.value & 0xFF;

    uint8_t calculatedCRC = this->CRC8->smbus(buff, BUFF_SIZE - CRC_SIZE);
    return reading.crc == calculatedCRC;
}
