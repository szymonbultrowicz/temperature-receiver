#include "Receiver.h"

Receiver::Receiver(unsigned int pin) {
    this->device = new RCSwitch();
    this->device->enableReceive(pin);
}

boolean Receiver::isAvailable() {
    return this->device->available();
}

unsigned long Receiver::receive() {
    unsigned long value = this->device->getReceivedValue();
    this->device->resetAvailable();
    return value;
}
