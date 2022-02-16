#include <Arduino.h>
#include <VoltageGate.h>

VoltageGate::VoltageGate(int pin, int gateLength)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->gateDuration = new Counter(gateLength);
}

void VoltageGate::rise()
{
  this->gateDuration->start();
  digitalWrite(this->pin, HIGH);
}

void VoltageGate::fall()
{
  digitalWrite(this->pin, LOW);
}

void VoltageGate::run()
{
  if (this->gateDuration->count())
  {
    this->fall();
  }
}
