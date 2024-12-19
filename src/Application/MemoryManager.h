#pragma once

#include <cstdint>
#include <vector>

class MemoryManager
{
    public:
        MemoryManager();
        ~MemoryManager();

        uint16_t getCurrentInstruction(uint16_t programCounter) const;

        void loadIntoMemory(uint8_t* data, uint16_t startingPosition, uint16_t dataSize);
        uint8_t* getMemoryData(uint16_t memoryOffset);

        // INDEX REGISTER
        uint16_t getIndexRegister() const;
        void setIndexRegister(uint16_t newValue);

        // PC Stack
        void storeInPcStack(uint16_t stackValue);
        uint16_t readFromPcStack();

        // REGISTERS
        uint8_t getRegisterValue(uint8_t registerIdx) const;
        void setRegisterValue(uint8_t registerIdx, uint8_t value);
        void addToRegister(uint8_t registerIdx, uint8_t value);       
        bool areRegisterValuesEqual(uint8_t firstRegister, uint8_t secondRegister) const;
        void handleRegisterOnRegisterOperation(uint8_t operation, uint8_t firstRegisterIdx, uint8_t secondRegisterIdx);

        void storeRegistersInMemory();
        void loadRegistersFromMemory();

    protected:
        void loadFont();

        // memory
        std::vector<uint8_t> mMemoryData {};
        
        // registers V0 to VF
        std::vector<uint8_t> mRegisters {};

        // opcode stack
        std::vector<uint16_t> mPcStack {};

        // index register; point to memory address
        uint16_t mIndexRegister {};
};