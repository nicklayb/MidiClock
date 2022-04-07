#include <MidiClock.h>

/*
 * Constructs a MidiClock using an event handler and 24 Pulses per quarter note
 */
MidiClock::MidiClock(EventHandler riseEventHandler) : MidiClock(riseEventHandler, Pppn_24){};

/*
 * Constructs a MidiClock using an event handler and a given pulse count.
 */
MidiClock::MidiClock(EventHandler riseEventHandler, PulseCount pulseCount)
{
  this->setRiseEventHandler(riseEventHandler);
  this->setPulseCount(pulseCount);
};

/*
 * Sets the pulse count at runtime. Useful to support
 * live pulse count update through jumpers or pots.
 */
void MidiClock::setPulseCount(PulseCount pulseCount)
{
  this->pulseCount = pulseCount;
  this->reset();
};

/*
 * Resets the MidiClock counter back to it's initial state.
 */
void MidiClock::reset()
{
  this->counter = 0;
};

/*
 * Increments the MIDI counter. It invokes the `riseEventHandler` when
 * it needs to output a gate. Resets back when the pulse count is reached
 */
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

/*
 * Invokes the`riseEventHandler`
 */
void MidiClock::fireRiseEvent()
{
  (*this->riseEventHandler)();
};

/*
 * Checks if the clock has reached a point where it needs to rise a gate.
 */
bool MidiClock::reachedRise()
{
  return (this->counter % this->pulsesForTick()) == 0;
};

/*
 * Updates the`riseEventHandler`.
 */
void MidiClock::setRiseEventHandler(EventHandler riseEventHandler)
{
  this->riseEventHandler = riseEventHandler;
};

/*
 * Gets the pulses required before firing a gate depending on the pulse count.
 */
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

/*
 * Updates clock state.
 */
void MidiClock::setClockState(ClockState state)
{
  this->state = state;
}

/*
 * Starts the Clock
 */
void MidiClock::start()
{
  this->reset();
  this->setClockState(Started);
}

/*
 * Stops the Clock
 */
void MidiClock::stop()
{
  this->setClockState(Stopped);
}
