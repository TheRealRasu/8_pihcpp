#include "ApplicationDefines.h"
#include <cstdint>
#define SDL_MAIN_HANDLED
#pragma once

#include "SDL.h"

#include <array>
#include <memory>

class DisplayHandler
{
    public:
        DisplayHandler();
        ~DisplayHandler();

        void start();
        void stop();

        bool drawSprite(uint16_t xPos, uint16_t yPos, uint8_t spriteHeight, uint8_t* spriteData);
    
        void clearWindow();
        void debugDraw();

    protected:

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

        std::unique_ptr<SDL_Renderer, SdlRendererDtor> mRenderer {};
        std::unique_ptr<SDL_Window, SdlWindowDtor> mWindow {};

        std::array<uint8_t, gWindowHeight * gWindowWidth> mImageData;
};
