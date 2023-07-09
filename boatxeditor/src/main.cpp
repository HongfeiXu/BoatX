#include <iostream>
#include <filesystem>
#include "boatx/engine.h"

int main(int argc, char** argv)
{
    std::cout << "Hello, this is boatx, your first game engine!" << std::endl;

    boatx::Engine& engine = boatx::Engine::Instance();

    std::filesystem::path executablePath(argv[0]);
    engine.Initialize(executablePath.string());

    engine.Run();
    
    return 0;
}
