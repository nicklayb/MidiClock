#include <Counter.h>

/*
 * Constructs the Counter with the maximumValue, the higher the
 * value is, the longer the counter is.
 */
Counter::Counter(int maximumValue)
{
  this->maximumValue = maximumValue;
}

/*
 * Increments the count when started, returning true when it
 * reaches the maximum, returning false otherwise. It resets
 * automatically once it has reached its maximum value.
 */
bool Counter::count()
{
  if (this->running)
  {
    this->value++;
    if (this->value == this->maximumValue)
    {
      this->reset();
      return true;
    }
  }
  return false;
}

/*
 * Resets counter back to zero and stops the counter.
 */
void Counter::reset()
{
  this->value = 0;
  this->stop();
}

/*
 * Stops the counter.
 */
void Counter::stop()
{
  this->running = false;
}

/*
 * Starts the counter.
 */
void Counter::start()
{
  this->running = true;
}
