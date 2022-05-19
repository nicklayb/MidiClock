#include <Arduino.h>
#include <MidiClock.h>
#include <Counter.h>
#include <MIDI.h>
#include <VoltageGate.h>

#define START_STOP_PIN 2
#define CLOCK_PIN 1
#define RUNNING_PIN 0
// Clock gate is a short couple of ms pulse
#define CLOCK_GATE_LENGTH 5000
// Start stop gate is longer as this is an event that occurs less often
#define START_STOP_GATE_LENGTH 30000

MIDI_CREATE_DEFAULT_INSTANCE();

bool awaitStartRise = false;

/*
 * Handler for when MIDI clock has risen
 */
void handleClockRise(void);

/*
 * Handler when STOP message is received from MIDI
 */
void handleMidiStop(void);

/*
 * Handler when START message is received from MIDI
 */
void handleMidiStart(void);

/*
 * Handler when CLOCK message is received from MIDI
 */
void handleMidiClock(void);

MidiClock *midiClock = new MidiClock(handleClockRise);
VoltageGate *clockGate;
VoltageGate *startStopGate;
VoltageGate *runningGate;

/*
 *  Initializes MIDI and set handlers
 */
void initMidi()
{
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleClock(handleMidiClock);
  MIDI.setHandleStart(handleMidiStart);
  MIDI.setHandleStop(handleMidiStop);
  MIDI.setHandleContinue(handleMidiStart);
}

void setup()
{
  clockGate = new VoltageGate(CLOCK_PIN, CLOCK_GATE_LENGTH);
  startStopGate = new VoltageGate(START_STOP_PIN, START_STOP_GATE_LENGTH);
  runningGate = new VoltageGate(RUNNING_PIN);
  initMidi();
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
  if (awaitStartRise)
  {
    startStopGate->rise();
    awaitStartRise = false;
  }
}

void handleMidiStart(void)
{
  midiClock->start();
  runningGate->rise();
  awaitStartRise = true;
}

void handleMidiStop(void)
{
  midiClock->stop();
  startStopGate->rise();
  runningGate->fall();
}

void handleMidiClock()
{
  midiClock->increment();
}
