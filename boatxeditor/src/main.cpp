#include <iostream>
#include "boatx\engine.h"

int main()
{
    std::cout << "Hello, this is boatx, your first game engine!" << std::endl;
	boatx::GetInfo();

    boatx::Initialize();
    boatx::ShutDown();

#ifdef BOATX_PLATFORM_WINDOWS
    system("pause");
#endif
    return 0;
}
