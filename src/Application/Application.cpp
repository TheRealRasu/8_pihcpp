#include "Application.h"

#include "ApplicationDefines.h"

#include <fstream>
#include <cmath>
#include <iostream>
#include <string>

#include <Windows.h>

#include "SDL_video.h"
//#include "SDL_wvideo.h"


Application::Application()
{
    mProgramCounter = MEMORY_START_ADDRESS;

    // registers V0 to VF
    mRegisters.resize(REGISTERS_SIZE, 0);

    // opcode stack
    mPcStack.resize(STACK_SIZE, 0);

    // provide 4 kB of memory (0x000 to 0xFFF)
    mMemoryData.resize(MEMORY_SIZE_BYTE, 0);

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

        memcpy(mMemoryData.data() + FONT_OFFSET, font.data(), font.size());
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

    mWindow.reset(SDL_CreateWindow("8_PIHC", 300, 100, 640, 320, SDL_WINDOW_SHOWN));
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

        std::cout << size << "\n";
        for (uint64_t pos = 0; pos < static_cast<uint64_t>(size); pos++)
        {
            mMemoryData.at(MEMORY_START_ADDRESS + pos) = buffer.at(pos);
        }
    }
}

void Application::update()
{
    Sleep(500);

    SDL_SetRenderDrawColor(mRenderer.get(), 255, 255, 255, 0);

    for (int x = 100; x < 200; x++)
    {
        for (int y = 100; y < 200; y++)
        {
            SDL_RenderDrawPoint(mRenderer.get(), x, y);
        }
    }

    SDL_RenderPresent(mRenderer.get());

    Sleep(500);
}