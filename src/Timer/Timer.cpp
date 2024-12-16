#include "Timer.h"

uint8_t Timer::value() const
{
    return mValue;
}

void Timer::setValue(uint8_t newValue)
{
    mValue = newValue;
}

void Timer::decreaseTimer()
{
    if (mValue > 0) mValue--;
}