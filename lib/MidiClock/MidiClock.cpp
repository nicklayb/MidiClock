#include <MidiClock.h>

MidiClock::MidiClock(EventHandler riseEventHandler) : MidiClock(riseEventHandler, Pppn_24){};

MidiClock::MidiClock(EventHandler riseEventHandler, PulseCount pulseCount)
{
  this->setRiseEventHandler(riseEventHandler);
  this->setPulseCount(pulseCount);
};

void MidiClock::setPulseCount(PulseCount pulseCount)
{
  this->pulseCount = pulseCount;
  this->reset();
};

void MidiClock::reset()
{
  this->counter = 0;
};

void MidiClock::increment()
{
  if (this->reachedRise())
  {
    this->fireRiseEvent();
  }

  if (this->counter == this->pulseCount)
  {
    this->reset();
  }
  this->counter++;
};

void MidiClock::fireRiseEvent()
{
  (*this->riseEventHandler)();
};

bool MidiClock::reachedRise()
{
  return (this->counter % this->pulsesForTick()) == 0;
};

void MidiClock::setRiseEventHandler(EventHandler riseEventHandler)
{
  this->riseEventHandler = riseEventHandler;
};

int MidiClock::pulsesForTick()
{
  switch (this->pulseCount)
  {
  case Pppn_24:
    return PPQN_24_PULSES_FOR_TICK;
  default:
    return 2;
  };
};

int MidiClock::gateLenth()
{
  return this->pulsesForTick() / 2;
}

void MidiClock::setClockState(ClockState state)
{
  this->state = state;
}

void MidiClock::start()
{
  this->reset();
  this->setClockState(Started);
}

void MidiClock::stop()
{
  this->setClockState(Stopped);
}
