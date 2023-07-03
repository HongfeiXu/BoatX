#include <iostream>
#include "boatx\engine.h"

int main()
{
    std::cout << "Hello, this is boatx, your first game engine!" << std::endl;
	boatx::GetInfo();

    int a = boatx::Add(10, 5);
    int b = boatx::Sub(10, 5);


    return 0;
}
