#include "DisplayHandler.h"

#include "ApplicationDefines.h"

#include "SDL.h"
#include "SDL_video.h"

DisplayHandler::DisplayHandler()
{}

DisplayHandler::~DisplayHandler()
{}

void DisplayHandler::start()
{
    SDL_Init(SDL_INIT_VIDEO);

    mWindow.reset(SDL_CreateWindow("8_PIHC", gWindowXPos, gWindowYPos, gWindowWidth, gWindowHeight, SDL_WINDOW_SHOWN));
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
    
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

void DisplayHandler::stop()
{

}

void DisplayHandler::clearWindow()
{
    SDL_Rect windowBox;
    windowBox.w = gWindowWidth;
    windowBox.h = gWindowHeight;
    windowBox.x = gWindowXPos;
    windowBox.y = gWindowYPos;

    SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0);
    SDL_RenderDrawRect(mRenderer.get(), &windowBox);
    SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0);
    SDL_RenderFillRect(mRenderer.get(), &windowBox);
}

void DisplayHandler::update()
{
    SDL_SetRenderDrawColor(mRenderer.get(), 255, 255, 255, 0);

    for (int x = 100; x < 200; x++)
    {
        for (int y = 100; y < 200; y++)
        {
            SDL_RenderDrawPoint(mRenderer.get(), x, y);
        }
    }

    SDL_RenderPresent(mRenderer.get());
}