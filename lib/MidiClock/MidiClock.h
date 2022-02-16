#ifndef MIDI_CLOCK_H
#define MIDI_CLOCK_H

enum PulseCount
{
  Pppn_24 = 24,
};

enum ClockState
{
  Stopped,
  Started,
  Paused
};

typedef void (*EventHandler)(void);

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
  int gateLenth();
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
