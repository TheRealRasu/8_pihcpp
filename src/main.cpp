#include <stdlib.h>
#include <vector>

int main()
{
    // registers V0 to VF
    std::vector<uint8_t> registers (16, 0);

    uint16_t indexRegister {};

    // provide 4 kB of memory (0x000 to 0xFFF)
    std::vector<uint8_t> memoryData (4096, 0);
    // TODO
    std::cout << "Hello World! Verbose: " << std::boolalpha << gVerbose << "\n";

    return EXIT_SUCCESS;
}
