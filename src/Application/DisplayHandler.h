#define SDL_MAIN_HANDLED
#pragma once

#include "SDL.h"

#include <memory>

class SDL_Renderer;

class DisplayHandler
{
    public:
        DisplayHandler();
        ~DisplayHandler();

        void start();
        void stop();
    
        void clearWindow();
        void update();

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
