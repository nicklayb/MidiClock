#ifndef MIDI_CLOCK_H
#define MIDI_CLOCK_H

/*
 * Available Pulse counts.
 */
enum PulseCount
{
  // 24 Pulse per quarter note
  Pppn_24 = 24,
};

/*
 * States of the clock, mainly used for the running gate.
 */
enum ClockState
{
  // Clock is stopped
  Stopped,
  // Clock is started
  Started,
  // Clock is paused
  Paused
};

/*
 * Event handler when the clock reaches various steps.
 */
typedef void (*EventHandler)(void);

/*
 * MidiClock
 *
 * Clocks that performs the right division from MIDI clock to
 * voltage gates. Various PPQN (Pulses per quarter note) can be
 * provided to suit various MIDI devices.
 */
class MidiClock
{
private:
  const int PPQN_24_PULSES_FOR_TICK = 6;
  ClockState state = Stopped;
  int counter = 0;
  PulseCount pulseCount;
  EventHandler riseEventHandler;

  bool reachedRise();
  void fireRiseEvent();
  void setRiseEventHandler(EventHandler riseEventHandler);
  int pulsesForTick();
  void setClockState(ClockState clockState);

public:
  MidiClock(EventHandler riseEventHandler);
  MidiClock(EventHandler riseEventHandler, PulseCount pulseCount);
  void setPulseCount(PulseCount pulseCount);
  void increment();
  void reset();
  void start();
  void stop();
  void resume();
};

#endif
