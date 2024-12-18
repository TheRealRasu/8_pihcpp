#include "DisplayHandler.h"

#include "ApplicationDefines.h"

#include "SDL.h"
#include "SDL_video.h"
#include <cstdint>

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

bool DisplayHandler::drawSprite(uint16_t xPos, uint16_t yPos, uint8_t spriteHeight, uint8_t* spriteData)
{
    bool spritesFlipped {};

    const uint16_t startX = (xPos % gWindowWidth);
    const uint16_t startY = (yPos % gWindowHeight);

    for (uint16_t yPos = startY; yPos < (startY + spriteHeight); yPos++)
    {
        if (yPos > gWindowHeight) break;

        const uint8_t incomingColorData = *spriteData;

        uint8_t newColorByte {};

        for (uint16_t xPos = startX; xPos < startX + 8; xPos++)
        {
            if (xPos > gWindowWidth) break;

            uint8_t& memoryColorData = mImageData[yPos * gWindowWidth + xPos];

            const bool newBit = (incomingColorData >> (xPos - startX)) & 1;
            if (newBit == false) continue;

            const bool memoryBit = memoryColorData & 1;

            memoryColorData = (newBit ^ memoryBit);

            if (newBit && memoryBit)
            {
                spritesFlipped = true;
            }
        }

        spriteData++;
    }

    return spritesFlipped;
}

void DisplayHandler::clearWindow()
{
    std::fill(mImageData.begin(), mImageData.end(), 0);
}

void DisplayHandler::drawWindow()
{
    for (int xPos = 0; xPos < gWindowWidth; xPos++)
    {
        for (int yPos = 0; yPos < gWindowHeight; yPos++)
        {
            const uint8_t pixel = mImageData[yPos * gWindowWidth + xPos];
            const uint32_t color = pixel == 0 ? 0x00000000 : 0xFFFFFF00;
            
            SDL_SetRenderDrawColor(mRenderer.get(), (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

            for (uint8_t i = 0; i < scale; i++)
            {
                for (uint8_t ii = 0; ii < scale; ii++)
                {
                    SDL_RenderDrawPoint(mRenderer.get(), (xPos * scale) + i, (yPos * scale) + ii);
                }
            }
        }
    }
    
    SDL_RenderPresent(mRenderer.get());
}