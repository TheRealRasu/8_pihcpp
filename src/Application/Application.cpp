#include "Application.h"
#include "ApplicationDefines.h"

#include "MemoryManager.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "SDL_video.h"

Application::Application()
{
    mMemoryManager = std::make_unique<MemoryManager>();

    mProgramCounter = gMemoryStartAddress;
}

Application::~Application()
{
    // SDL_Renderer and SDL_Window ptrs are automatically destroyed
    SDL_Quit();
}

void Application::start()
{
    SDL_Init(SDL_INIT_VIDEO);

    mWindow.reset(SDL_CreateWindow("8_PIHC", gWindowXPos, gWindowYPos, gWindowWidth, gWindowHeight, SDL_WINDOW_SHOWN));
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
    
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

void Application::load(const char* fileName)
{
    std::ifstream fileRom(fileName, std::ios::binary | std::ios::ate);

    if (fileRom.is_open())
    {
        const std::streampos size = fileRom.tellg();
        
        std::vector<uint8_t> buffer(size, 0);

        fileRom.seekg(0, std::ios::beg);
        fileRom.read(reinterpret_cast<char*>(buffer.data()), size);
        fileRom.close();

        for (uint64_t pos = 0; pos < static_cast<uint64_t>(size); pos++)
        {
            mMemoryData.at(gMemoryStartAddress + pos) = buffer.at(pos);
        }
    }
}

void Application::update()
{
    if (mSoundTimer > 0) mSoundTimer--;
    if (mDelayTimer > 0) mDelayTimer--;

    const uint16_t currentInstruction = mMemoryManager->getCurrentInstruction(mProgramCounter);
    handleInstruction(currentInstruction);

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

void Application::handleInstruction(uint16_t instruction)
{
    /*
     *  Instructions are structured as 0x[1st nibble][2nd nibble][3rd nibble][4th nibble]
     *  Or, alternatively, 0x[1st byte][2nd byte]
     * 
    */ 

    const uint8_t firstByte = instruction >> 8 & 0xFF;
    const uint8_t secondByte = instruction & 0xFF;

    const uint8_t firstNibble = firstByte >> 4 & 0xF;
    const uint8_t secondNibble = firstByte & 0xF;
    const uint8_t thirdNibble = secondByte >> 4 & 0xF;
    const uint8_t fourthNibble = secondByte & 0xF;

    switch (firstNibble)
    {
    case 0:
    {
        if (secondByte == 0xE0) // clear window
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
        else if (secondByte == 0xEE)
        {
            mProgramCounter = mMemoryManager->readFromPcStack();
        }
        else
        {
            // do nothing; no machine language routines (0x0NNN) here!
        }
        
        break;
    }
    case 1:
    {
        // Set program counter to value
        const uint16_t pcValue = instruction & 0xFFF;
        mProgramCounter = pcValue;

        break;
    }
    case 2:
    {
        // Call new subroutine
        const uint16_t subroutineAddress = instruction & 0xFFF;

        // store current PC in PC stack
        mMemoryManager->storeInPcStack(mProgramCounter);
        mProgramCounter = subroutineAddress;
        break;
    }
    case 3:
    {
        // TODO
        break;
    }
    case 4:
    {
        // TODO
        break;
    }
    case 5:
    {
        // TODO
        break;
    }
    case 6:
    {
        mMemoryManager->setRegisterValue(secondNibble, secondByte);
        break;
    }
    case 7:
    {
        mMemoryManager->addToRegister(secondNibble, secondByte);
        break;
    }
    case 8:
    {
        mMemoryManager->handleRegisterOnRegisterOperation(fourthNibble, secondNibble, thirdNibble);
        // TODO; arithmetic operations
        break;
    }
    case 9:
    {
        // TODO
        break;
    }
    case 0xA:
    {
        // Set index register
        const int newValue = instruction & 0xFFF;
        mMemoryManager->setIndexRegister(newValue);
        break;
    }
    case 0xB:
    {
        // TODO
        break;
    }
    case 0xC:
    {
        
        
        break;
    }
    case 0xD:
    {
        // TODO
        break;
    }
    case 0xE:
    {
        // TODO
        break;
    }
    case 0xF: // handle Timers
    {
        if (secondByte == 0x07)
        {
            mMemoryManager->setRegisterValue(secondNibble, mDelayTimer);
        }
        else if (secondByte == 0x15)
        {
            mDelayTimer = mMemoryManager->getRegisterValue(secondNibble);
        }
        else if (secondByte == 0x15)
        {
            mSoundTimer = mMemoryManager->getRegisterValue(secondNibble);
        }
        else if (secondByte == 0x1E)
        {
            // TODO
        }
        else if (secondByte == 0x0A)
        {
            // TODO
        }
        break;
    }
    default:
    {
        break;
    }
    }
}