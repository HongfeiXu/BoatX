#include "engine.h"
#include <iostream>

namespace boatx
{
    int Sub(int a, int b)
    {
        return a - b;
    }

	void GetInfo()
	{
        std::cout << "GetInfo" << std::endl;
#ifdef BOATX_CONFIG_DEBUG
        std::cout << "configurations:Debug" << std::endl;
#endif
#ifdef BOATX_CONFIG_RELEASE
    	std::cout << "configurations:Release" << std::endl;
#endif
#ifdef BOATX_PLATFORM_WINDOWS
		std::cout << "BOATX_PLATFORM_WINDOWS" << std::endl;
#endif
#ifdef BOATX_PLATFORM_MAC
		std::cout << "BOATX_PLATFORM_MAC" << std::endl;
#endif
	}

} // namespace boatx
