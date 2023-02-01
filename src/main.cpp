#include <iostream>
<<<<<<< HEAD
=======

#include <stdlib.h>
>>>>>>> added debug hw
#include <vector>

#include <stdlib.h>

int main()
{
    // registers V0 to VF
    std::vector<uint8_t> registers (16, 0);

    uint16_t indexRegister {};

    // provide 4 kB of memory (0x000 to 0xFFF)
    std::vector<uint8_t> memoryData (4096, 0);

    // TODO
    std::cout << "Hello World!\n";

    return EXIT_SUCCESS;
}
