#ifndef _RECEIVER_H_
#define _RECEIVER_H_
#include <RCSwitch.h>

class Receiver
{
  public:
    Receiver(unsigned int pin);
    boolean isAvailable();
    unsigned long receive();

  private:
    RCSwitch *device;
};
#endif
