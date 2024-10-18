#include "Application/Application.h"

#include <memory>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc < 2) return EXIT_FAILURE;

    bool gTerminate {};

    const char* fileName = argv[1];

    std::unique_ptr<Application> application = std::make_unique<Application>();
    application->start();
    application->load(fileName);

    //while (gTerminate == false)
    {
        application->update();
    }

    return EXIT_SUCCESS;
}