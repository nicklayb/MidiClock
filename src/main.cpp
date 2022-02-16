#include <Arduino.h>
#include <MidiClock.h>
#include <Counter.h>
#include <MIDI.h>
#include <VoltageGate.h>

#define START_STOP_PIN 1
#define CLOCK_PIN 2
#define RUNNING_PIN 0
#define GATE_LENGTH 5000

int state = LOW;

MIDI_CREATE_DEFAULT_INSTANCE();
void handleClockRise(void);
void handleStop(void);
void handleStart(void);
void handleClock(void);

MidiClock *midiClock = new MidiClock(handleClockRise);
VoltageGate *clockGate;
VoltageGate *startStopGate;
VoltageGate *runningGate;

void setup()
{
  clockGate = new VoltageGate(CLOCK_PIN, GATE_LENGTH);
  startStopGate = new VoltageGate(START_STOP_PIN, GATE_LENGTH);
  runningGate = new VoltageGate(RUNNING_PIN, 1);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleStop(handleStop);
  MIDI.setHandleContinue(handleStart);
}

void loop()
{
  MIDI.read();
  clockGate->run();
  startStopGate->run();
}

void handleClockRise(void)
{
  clockGate->rise();
}

void handleStart(void)
{
  midiClock->start();
  startStopGate->rise();
  runningGate->rise();
}

void handleStop(void)
{
  midiClock->stop();
  startStopGate->rise();
  runningGate->fall();
}

void handleClock()
{
  midiClock->increment();
}
