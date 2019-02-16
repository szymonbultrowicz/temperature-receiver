#ifndef BatteryLevel_h
#define BatteryLevel_h

class BatteryLevel
{
  public:
    BatteryLevel(uint16_t minV, uint16_t maxV);
    uint8_t calculate(uint16_t voltage);

  private:
    uint16_t minV;
    uint16_t maxV;
};

#endif
