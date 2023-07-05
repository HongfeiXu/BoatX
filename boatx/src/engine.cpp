#include <iostream>
#include "engine.h"
#include "sdl2/SDL.h"

namespace boatx
{

	bool Initialize()
	{
		bool ret = true;
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "Error initialize SDL2: " << SDL_GetError() << std::endl;
			ret = false;
		}
		else
		{
			SDL_version version;
			SDL_VERSION(&version);
			std::cout << "Version of SDL2: " << (uint32_t)version.major << "." << (uint32_t)version.minor << "." << (uint32_t)version.patch << std::endl;
		}

		return ret;
	}

	void ShutDown()
	{
		SDL_Quit();
	}

	void GetInfo()
	{
        std::cout << "GetInfo" << std::endl;
#ifdef BOATX_CONFIG_DEBUG
        std::cout << "\tconfigurations:Debug" << std::endl;
#endif
#ifdef BOATX_CONFIG_RELEASE
    	std::cout << "\tconfigurations:Release" << std::endl;
#endif
#ifdef BOATX_PLATFORM_WINDOWS
		std::cout << "\tBOATX_PLATFORM_WINDOWS" << std::endl;
#endif
#ifdef BOATX_PLATFORM_MAC
		std::cout << "\tBOATX_PLATFORM_MAC" << std::endl;
#endif
#ifdef BOATX_PLATFORM_LINUX
		std::cout << "\tBOATX_PLATFORM_LINUX" << std::endl;
#endif
	}

} // namespace boatx
