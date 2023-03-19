#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <Windows.h>

#include "SDL.h"
#include "SDL_video.h"
//#include "SDL_wvideo.h"

//bool gVerbose {};

int main()
{
    // provide 4 kB of memory (0x000 to 0xFFF)
    std::vector<uint8_t> memoryData (4096, 0);

    // index register; point to memory address
    uint16_t indexRegister {};

    // program counter
    uint16_t programCounter {};

    // delay timer
    uint8_t delayTimer { 60 };

    // sound timer
    uint8_t soundTimer {};

    // registers V0 to VF
    std::vector<uint8_t> registers (16, 0);

    // opcode stack
    std::vector<uint16_t> pcStack (16, 0);

    // stack pointer
    uint8_t stackPos {};

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

        memcpy(memoryData.data() + 50, font.data(), font.size());
    }

    // TODO
    {
        SDL_Init(SDL_INIT_VIDEO);
        std::cout << "Hello World!\n";

    }
    SDL_Window* window = SDL_CreateWindow("YEP", 0, 0, 500, 500, SDL_WINDOW_SHOWN);
    
    for (int i = 40; i < 140; i++)
    {
        std::cout << "data[" << i << "]: " << std::to_string(memoryData[i]) << "\n";
    }

    Sleep(2000);
    SDL_Quit();
    return EXIT_SUCCESS;
}