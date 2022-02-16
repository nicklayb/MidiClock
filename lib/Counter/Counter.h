#ifndef COUNTER_H
#define COUNTER_H

class Counter
{
private:
  int value;
  int maximumValue;
  bool running = true;

public:
  Counter(int maximumValue);
  bool count();
  void reset();
  void stop();
  void start();
};

#endif
