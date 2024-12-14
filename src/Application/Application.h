#pragma once

#include <memory>

class DisplayHandler;
class MemoryManager;

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

        // program counter
        uint16_t mProgramCounter {};

        // delay timer
        uint8_t mDelayTimer { 60 };

        // sound timer
        uint8_t mSoundTimer {};

        // stack pointer
        uint8_t stackPos {};
};