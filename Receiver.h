#ifndef _RECEIVER_H_
#define _RECEIVER_H_
#include <RCSwitch.h>
#include "FastCRC.h"
#include "Reading.h"

class Receiver
{
  public:
    Receiver(unsigned int pin);
    boolean isAvailable();
    Reading receive();

  private:
    RCSwitch *device;
    FastCRC8* CRC8;
    boolean verifyChecksum(Reading reading);
};
#endif
