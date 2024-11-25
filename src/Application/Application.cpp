#include "Application.h"

#include "ApplicationDefines.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "SDL_video.h"

Application::Application()
{
    mProgramCounter = gMemoryStartAddress;

    // registers V0 to VF
    mRegisters.resize(gRegistersSize, 0);

    // opcode stack
    mPcStack.resize(gStackSize, 0);

    // provide 4 kB of memory (0x000 to 0xFFF)
    mMemoryData.resize(gMemorySizeBytes, 0);

    // load font; font vector does not need to live beyond this scope
    {
        const std::vector<uint8_t> font = 
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        memcpy(mMemoryData.data() + gFontOffset, font.data(), font.size());
    }
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

    const uint16_t currentInstruction = (mMemoryData.at(mProgramCounter) << 8) + mMemoryData.at(mProgramCounter + 1);
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
    switch (instruction >> 12 & 0xF)
    {
        case 0:
        {
            if (instruction == 0x00E0) // clear window
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
            else if (instruction == 0x00EE)
            {
                mProgramCounter = mPcStack.back();
                mPcStack.pop_back();
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
            mPcStack.push_back(mProgramCounter);
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
            // Set Register to value
            const int registerAddress = (instruction >> 8) & 0x0F;
            const int newRegisterValue = instruction & 0xFF;

            mRegisters.at(registerAddress) = newRegisterValue;
            break;
        }
        case 7:
        {
            // Add value to register address
            const int registerAddress = (instruction >> 8) & 0x0F;
            const int additionalValue = instruction & 0xFF;

            mRegisters.at(registerAddress) += additionalValue;
            break;
        }
        case 8:
        {
            const uint8_t firstRegisterIdx = (instruction >> 8) & 0xF;
            const uint8_t secondRegisterIdx = (instruction >> 4) & 0xF;
            const uint8_t operationCmd = instruction & 0xF;

            switch (operationCmd)
            {
                case 0:
                {
                    mRegisters.at(firstRegisterIdx) = mRegisters.at(secondRegisterIdx);
                    break;
                }
                case 1:
                {
                    mRegisters.at(firstRegisterIdx) |= mRegisters.at(secondRegisterIdx);
                    break;
                }
                case 2:
                {
                    mRegisters.at(firstRegisterIdx) &= mRegisters.at(secondRegisterIdx);
                    break;
                }
                case 3:
                {
                    mRegisters.at(firstRegisterIdx) ^= mRegisters.at(secondRegisterIdx);
                    break;
                }
                case 3:
                {
                    mRegisters.at(firstRegisterIdx) += mRegisters.at(secondRegisterIdx);
                    break;
                }
                case 5:
                {
                    mRegisters.at(firstRegisterIdx) -= mRegisters.at(secondRegisterIdx);
                    break;
                }
                case 7:
                {
                    mRegisters.at(firstRegisterIdx) = mRegisters.at(secondRegisterIdx) - mRegisters.at(firstRegisterIdx);
                    break;
                }
            }
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
            mIndexRegister = newValue;
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
        case 0xF:
        {
            // TODO
            break;
        }
        default:
        {
            break;
        }
    }
}