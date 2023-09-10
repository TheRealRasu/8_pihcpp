#define SDL_MAIN_HANDLED

#include "SDL.h"
#include <vector>

class Application
{
    public:
        Application();
        ~Application();

        void start();
        void load(const char* fileName);
        void update();

    protected:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;

        // index register; point to memory address
        uint16_t mIndexRegister {};

        // program counter
        uint16_t mProgramCounter {};

        // delay timer
        uint8_t mDelayTimer { 60 };

        // sound timer
        uint8_t mSoundTimer {};

        // stack pointer
        uint8_t stackPos {};

        // memory
        std::vector<uint8_t> mMemoryData {};
        
        // registers V0 to VF
        std::vector<uint8_t> mRegisters {};

        // opcode stack
        std::vector<uint16_t> mPcStack {};
};