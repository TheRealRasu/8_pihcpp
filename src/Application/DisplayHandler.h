#define SDL_MAIN_HANDLED
#pragma once

#include "SDL.h"

#include <memory>

class DisplayHandler
{
    public:
        DisplayHandler();
        ~DisplayHandler();

        void start();
        void stop();

        void drawSprite(uint16_t xPos, uint16_t yPos, uint8_t spriteHeight, void* spriteData);
    
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
};
