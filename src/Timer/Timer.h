#pragma once

#include <cstdint>

class Timer
{
    public:
        Timer() = default;
        ~Timer() = default;

        uint8_t value() const;
        void setValue(uint8_t newValue);

        void decreaseTimer();

    protected:
            uint8_t mValue;
};