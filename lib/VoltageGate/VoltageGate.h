#ifndef VOLTAGE_GATE_H
#define VOLTAGE_GATE_H

#include <Counter.h>

class VoltageGate
{
private:
  Counter *gateDuration;
  int pin;

public:
  VoltageGate(int pin, int gateLength);
  void run();
  void fall();
  void rise();
};

#endif
