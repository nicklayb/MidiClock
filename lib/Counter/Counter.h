#ifndef COUNTER_H
#define COUNTER_H

/*
 * Counter
 *
 * Counter that doesn't block the running loop (like `dela`()` does`).
 * The counter is initialized with a maximumValue. Then we use `count()`
 * to increment that value returning false until it reaches the
 * `maximumValue`. Once it is reached, it returns true and the counter
 * doesn't count until it gets started again.
 */
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
