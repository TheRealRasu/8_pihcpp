#pragma once

constexpr uint8_t gRegistersSize { 16 }; // 0x10
constexpr uint8_t gStackSize { 16 }; // 0x10
constexpr uint16_t gMemorySizeBytes { 4096 }; // 0x1000

constexpr uint16_t gMemoryStartAddress { 512 }; // 0x200

constexpr uint8_t gFontOffset { 50 }; // 0x22; address where font data is being loaded into

constexpr uint8_t gFrameRate { 60 };


// WINDOW DIMENSIONS
constexpr uint16_t gWindowXPos { 500 };
constexpr uint16_t gWindowYPos { 500 };
constexpr uint16_t gWindowWidth { 64 };
constexpr uint16_t gWindowHeight { 32 };