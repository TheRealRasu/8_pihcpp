#include "DisplayHandler.h"

#include "ApplicationDefines.h"

#include "SDL.h"
#include "SDL_video.h"

constexpr int scale = 10;

DisplayHandler::DisplayHandler()
{}

DisplayHandler::~DisplayHandler()
{
    SDL_Quit();
}

void DisplayHandler::start()
{
    SDL_Init(SDL_INIT_VIDEO);

    mWindow.reset(SDL_CreateWindow("8_PIHC", gWindowXPos, gWindowYPos, gWindowWidth * scale, gWindowHeight * scale, SDL_WINDOW_SHOWN));
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
    
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

void DisplayHandler::stop()
{

}

void DisplayHandler::drawSprite(uint16_t xPos, uint16_t yPos, uint8_t spriteHeight, void* spriteData)
{
    const uint16_t startX = (xPos % gWindowWidth) * scale;
    const uint16_t startY = (yPos % gWindowHeight) * scale;

    for (int x = startX; x < (startX + scale); x++)
    {
        if (x > gWindowWidth * scale) break;

        for (int y = startY; y < startY + (spriteHeight * scale); y++)
        {
            if (y > gWindowHeight * scale) break;

            // TODO get pixel information, draw other color
        }
    }
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

void DisplayHandler::debugDraw()
{
    SDL_SetRenderDrawColor(mRenderer.get(), 255, 255, 255, 0);

    for (int x = 10 * scale; x < 20 * scale; x++)
    {
        for (int y = 10 * scale; y < 20 * scale; y++)
        {
            SDL_RenderDrawPoint(mRenderer.get(), x, y);
        }
    }

    SDL_RenderPresent(mRenderer.get());
}