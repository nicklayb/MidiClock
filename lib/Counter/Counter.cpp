#include <Counter.h>

Counter::Counter(int maximumValue)
{
  this->maximumValue = maximumValue;
}

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

void Counter::reset()
{
  this->value = 0;
  this->stop();
}

void Counter::stop()
{
  this->running = false;
}

void Counter::start()
{
  this->running = true;
}
