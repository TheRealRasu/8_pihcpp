#include "Application.h"
#include "ApplicationDefines.h"

#include "DisplayHandler.h"
#include "MemoryManager.h"

#include "Timer/Timer.h"

#include <fstream>
#include <iosfwd>

Application::Application()
{
    mDisplayHandler = std::make_unique<DisplayHandler>();
    mMemoryManager = std::make_unique<MemoryManager>();

    mDelayTimer = std::make_unique<Timer>();
    mDelayTimer->setValue(60);

    mSoundTimer = std::make_unique<Timer>();

    mProgramCounter = gMemoryStartAddress;
}

Application::~Application()
{
    // SDL_Renderer and SDL_Window ptrs are automatically destroyed
}

void Application::start()
{
    mDisplayHandler->start();
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

        mMemoryManager->loadIntoMemory(buffer.data(), gMemoryStartAddress, static_cast<uint16_t>(size));
    }
}

void Application::update()
{
    mSoundTimer->decreaseTimer();
    mDelayTimer->decreaseTimer();

    // Step 1: Get current instruction
    const uint16_t currentInstruction = mMemoryManager->getCurrentInstruction(mProgramCounter);

    // Step 2: process current Instruction
    handleInstruction(currentInstruction);
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

    const uint8_t instructionNibble = firstByte >> 4 & 0xF;
    const uint8_t secondNibble = firstByte & 0xF;
    const uint8_t thirdNibble = secondByte >> 4 & 0xF;
    const uint8_t fourthNibble = secondByte & 0xF;

    switch (instructionNibble)
    {
    case 0:
    {
        if (secondByte == 0xE0) // clear window
        {
            mDisplayHandler->clearWindow();
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
    case 0xC: // random number
    {
        int randomNumber = std::rand() % 256;
        randomNumber &= secondByte;

        mMemoryManager->setRegisterValue(secondNibble, randomNumber);
        
        break;
    }
    case 0xD:
    {
        const int xValue = mMemoryManager->getRegisterValue(secondNibble) % gWindowWidth;
        const int yValue = mMemoryManager->getRegisterValue(thirdNibble) % gWindowHeight;

        void* spriteData = mMemoryManager->getMemoryData(mMemoryManager->getIndexRegister());

        mDisplayHandler->drawSprite(xValue, yValue, fourthNibble, spriteData);
        // TODO
        break;
    }
    case 0xE:
    {
        if (secondByte == 0x9E)
        {
            // TODO
        }
        else if (secondByte == 0xA1)
        {
            // TODO
        }
        break;
    }
    case 0xF: // handle Timers
    {
        switch (secondByte)
        {
        case 0x07:
        {
            mMemoryManager->setRegisterValue(secondNibble, mDelayTimer->value());
            break;
        }
        case 0x15:
        {
            mDelayTimer->setValue(mMemoryManager->getRegisterValue(secondNibble));
            break;
        }
        case 0x18:
        {
            mSoundTimer->setValue(mMemoryManager->getRegisterValue(secondNibble));
            break;
        }
        case 0x1E:
        {
            // TODO
            break;
        }
        case 0x0A:
        {
            // TODO
            break;
        }
        case 0x29:
        {
            // TODO
            break;
        }
        case 0x33:
        {
            // TODO
            break;
        }
        case 0x55:
        {
            // TODO
            break;
        }
        case 0x65:
        {
            // TODO
            break;
        }
        }
        break;
    }
    default:
    {
        break;
    }
    }
}