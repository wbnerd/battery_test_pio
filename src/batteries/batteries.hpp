#ifndef BATTERIES_HPP
#define BATTERIES_HPP

struct BatteryDescription
{
  float lowVoltage;
  float startVoltage;
  float mwh;
  float mah;
  char * name;
};

#endif