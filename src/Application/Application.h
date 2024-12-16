#pragma once

#include <memory>

class DisplayHandler;
class MemoryManager;
class Timer;

class Application
{
    public:
        Application();
        ~Application();

        void start();
        void load(const char* fileName);
        void update();

    protected:
        void handleInstruction(uint16_t instruction);

        std::unique_ptr<DisplayHandler> mDisplayHandler;
        std::unique_ptr<MemoryManager> mMemoryManager;
     
        std::unique_ptr<Timer> mSoundTimer;
        std::unique_ptr<Timer> mDelayTimer;

        // program counter
        uint16_t mProgramCounter {};

        // stack pointer
        uint8_t stackPos {};
};