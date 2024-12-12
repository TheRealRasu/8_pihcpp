#pragma once
#define SDL_MAIN_HANDLED

#include "SDL.h"
#include <memory>
#include <vector>

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

        struct SdlWindowDtor
        {
            void operator()(SDL_Window* window) const
            {
                SDL_DestroyWindow(window);
            }
        };

        struct SdlRendererDtor
        {
            void operator()(SDL_Renderer* renderer) const
            {
                SDL_DestroyRenderer(renderer);
            }
        };

        std::unique_ptr<SDL_Renderer, SdlRendererDtor> mRenderer { nullptr };
        std::unique_ptr<SDL_Window, SdlWindowDtor> mWindow { nullptr };
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