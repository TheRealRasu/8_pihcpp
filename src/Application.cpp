#include "Application.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <Windows.h>

#include "SDL_video.h"
//#include "SDL_wvideo.h"

#define START_ADDRESS 0x200

Application::Application()
{
    mProgramCounter = START_ADDRESS;

    // registers V0 to VF
    mRegisters.resize(16, 0);

    // opcode stack
    mPcStack.resize(16, 0);

    // provide 4 kB of memory (0x000 to 0xFFF)
    mMemoryData.resize(4096, 0);

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

        memcpy(mMemoryData.data() + 50, font.data(), font.size());
    }
}

Application::~Application()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Application::start()
{
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow("8_PIHC", 300, 100, 640, 320, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void Application::load(const char* fileName)
{
    std::ifstream fileRom(fileName, std::ios::binary | std::ios::ate);

    if (fileRom.is_open())
    {
        const std::streampos size = fileRom.tellg();

        std::vector<uint8_t> buffer(size, 0);

        fileRom.seekg(0, std::ios::beg);
        fileRom.read((char*)buffer.data(), size);
        fileRom.close();

        std::cout << size << "\n";
        for (uint64_t pos = 0; pos < size; pos++)
        {
            mMemoryData[START_ADDRESS + pos] = buffer[pos];
        }
    }
}

void Application::update()
{
    Sleep(500);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 0);

    for (int x = 100; x < 200; x++)
    {
        for (int y = 100; y < 200; y++)
        {
            SDL_RenderDrawPoint(mRenderer, x, y);
        }
    }

    SDL_RenderPresent(mRenderer);

    Sleep(500);
}