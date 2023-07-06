#include <iostream>
#include "boatx/engine.h"

int main()
{
    std::cout << "Hello, this is boatx, your first game engine!" << std::endl;

    boatx::Engine& engine = boatx::Engine::Instance();

    engine.Run();
    
    return 0;
}
