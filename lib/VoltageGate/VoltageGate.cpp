#include <Arduino.h>
#include <VoltageGate.h>

/*
 * Constructs a VoltageGate class without counter.
 */
VoltageGate::VoltageGate(int pin) : VoltageGate::VoltageGate(pin, -1){};

/*
 * Constructs a VoltageGate class with a counter with gateLength as length
 * for self-falling gates. Each loop, the `run()` method makes the counter
 * count, once the counter returns to zero the VoltageGate falls if it was
 * started. It gets started when the VoltageGate rises. This is meant to
 * have a fixed duration gate that doesn't delay the running loop.
 */
VoltageGate::VoltageGate(int pin, int gateLength) : VoltageGate::VoltageGate(pin, gateLength, false){};

/*
 * Constructs a VoltageGate class with a counter with the possibility of
 * being inverted. This can be useful for cases where you want to send
 * a constant voltage and pull the gate to 0v when rising (S-Trig).
 */
VoltageGate::VoltageGate(int pin, int gateLength, bool inverted)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->gateDuration = new Counter(gateLength);
  this->inverted = inverted;
}

/*
 * Rises the voltage gate starting the counter.
 */
void VoltageGate::rise()
{
  this->gateDuration->start();
  this->state = High;
  this->writeToPin();
}

/*
 * Falls the voltage gate.
 */
void VoltageGate::fall()
{
  this->state = Low;
  this->writeToPin();
}

/*
 * Runs the voltage gate's counter. When the counter reaches 0
 * the voltage gate falls automatically.
 */
void VoltageGate::run()
{
  if (this->gateDuration->count())
  {
    this->fall();
  }
}

/*
 * Gets the LOW value (HIGH when the voltage gate is inverted).
 */
int VoltageGate::getLow()
{
  if (this->inverted)
  {
    return HIGH;
  }
  return LOW;
}

/*
 * Gets the HIGH value (LOW when the voltage gate is inverted).
 */
int VoltageGate::getHigh()
{
  if (this->inverted)
  {
    return LOW;
  }
  return HIGH;
}

/*
 * Writes voltage to pin from gate's state.
 */
void VoltageGate::writeToPin()
{
  digitalWrite(this->pin, this->state == Low ? this->getLow() : this->getHigh());
}
