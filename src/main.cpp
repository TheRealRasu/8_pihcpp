#include "Application/Application.h"
#include "Application/ApplicationDefines.h"

#include <memory>
#include <stdlib.h>
#include <Windows.h>
    
bool gTerminate {};

int main(int argc, char** argv)
{
    if (argc < 2) return EXIT_FAILURE;



    const char* fileName = argv[1];

    std::unique_ptr<Application> application = std::make_unique<Application>();
    application->start();
    application->load(fileName);


    while (gTerminate == false)
    {
        application->update();
        Sleep(1000 / gFrameRate);
    }

    return EXIT_SUCCESS;
}