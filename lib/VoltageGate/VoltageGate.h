#ifndef VOLTAGE_GATE_H
#define VOLTAGE_GATE_H

#include <Counter.h>

enum GateState
{
  High,
  Low,
};

/*
 * VoltageGate
 *
 * Outputs a gate from the microcontroller. Providing a gateLength parameter
 * will make the gate fall by itself after `run()` has been called for the
 * given gateLength. The VoltageGate can also be inverted, in such case, the
 * VoltageGate will be permanentyl HIGH and will go LOW when the gate rises
 * and returns to HIGH when the gate falls.
 */
class VoltageGate
{
private:
  Counter *gateDuration;
  int pin;
  bool inverted = false;
  GateState state = Low;
  int getHigh();
  int getLow();
  void writeToPin();

public:
  VoltageGate(int pin);
  VoltageGate(int pin, int gateLength);
  VoltageGate(int pin, int gateLength, bool inverted);
  void run();
  void fall();
  void rise();
};

#endif
