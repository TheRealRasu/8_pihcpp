#include "MemoryManager.h"

#include "ApplicationDefines.h"

#include <cstring>

MemoryManager::MemoryManager()
{
    // registers V0 to VF
    mRegisters.resize(gRegistersSize, 0);

    // opcode stack
    mPcStack.resize(gStackSize, 0);

    // provide 4 kB of memory (0x000 to 0xFFF)
    mMemoryData.resize(gMemorySizeBytes, 0);

    loadFont();
}

MemoryManager::~MemoryManager()
{}

uint16_t MemoryManager::getCurrentInstruction(uint16_t programCounter) const
{
    const uint16_t currentInstruction = (mMemoryData.at(programCounter) << 8) + mMemoryData.at(programCounter + 1);
    return currentInstruction;
}

void MemoryManager::setIndexRegister(uint16_t newValue)
{
    mIndexRegister = newValue;
}

void MemoryManager::storeInPcStack(uint16_t stackValue)
{
    mPcStack.push_back(stackValue);
}

uint16_t MemoryManager::readFromPcStack()
{
    const uint16_t pcStackValue = mPcStack.back();
    mPcStack.pop_back();

    return pcStackValue;
}

uint8_t MemoryManager::getRegisterValue(uint8_t registerIdx) const
{
    return mRegisters.at(registerIdx);
}

void MemoryManager::setRegisterValue(uint8_t registerIdx, uint8_t value)
{
    mRegisters.at(registerIdx) = value;
}

void MemoryManager::addToRegister(uint8_t registerIdx, uint8_t value)
{
    mRegisters.at(registerIdx) += value;
}

bool MemoryManager::areRegisterValuesEqual(uint8_t firstRegister, uint8_t secondRegister) const
{
    return mRegisters.at(firstRegister) == mRegisters.at(secondRegister);
}

void MemoryManager::handleRegisterOnRegisterOperation(uint8_t operation, uint8_t firstRegister, uint8_t secondRegister)
{
    switch (operation)
    {
    case 0: // Set
    {
        mRegisters.at(firstRegister) = mRegisters.at(secondRegister);
        break;
    }
    case 1: // OR
    {
        mRegisters.at(firstRegister) |= mRegisters.at(secondRegister);
        break;
    }
    case 2: // AND
    {
        mRegisters.at(firstRegister) &= mRegisters.at(secondRegister);
        break;
    }
    case 3: // XOR
    {
        mRegisters.at(firstRegister) ^= mRegisters.at(secondRegister);
        break;
    }
    case 4: // Add
    {
        mRegisters.at(firstRegister) += mRegisters.at(secondRegister);
        break;
    }
    case 5: // Subtract second register from first, save in first register
    {
        mRegisters.at(firstRegister) -= mRegisters.at(secondRegister);
        break;
    }
    case 6:
    {
        // TODO implement shift
        break;
    }
    case 7: // Subtract first register from second, save in first register
    {
        mRegisters.at(firstRegister) = mRegisters.at(secondRegister) - mRegisters.at(firstRegister);
        break;
    }
    case 0xE:
    {
        // TODO implement shift
        break;
    }
    default:
    {
        break;
    }
    }
}

void MemoryManager::loadFont()
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

    std::memcpy(mMemoryData.data() + gFontOffset, font.data(), font.size());
}