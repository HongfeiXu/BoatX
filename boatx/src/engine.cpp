#include <iostream>
#include "engine.h"
#include "sdl2/SDL.h"

namespace boatx
{
    Engine& Engine::Instance()
    {
        if (!mInstance)
        {
            mInstance = new Engine();
        }
        return *mInstance;
    }

    void Engine::Run()
    {
        if (Initialize())
        {
            // core loop
            while(mIsRunning)
            {
                mWindow.PumpEvents();
            }
        }

        ShutDown();
    }

    bool Engine::Initialize()
    {
        bool ret = false;
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cout << "Error initialize SDL2: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_version version;
            SDL_VERSION(&version);
            std::cout << "Version of SDL2: " << (uint32_t)version.major << "." << (uint32_t)version.minor << "." << (uint32_t)version.patch << std::endl;

            if (mWindow.Create())
            {
                ret = true;
                mIsRunning = true;
            }
        }

        if (!ret)
        {
            std::cout << "Engine initialization failed. Shutting down." << std::endl;
            ShutDown();
        }

        return ret;
    }

    void Engine::ShutDown()
    {
        mIsRunning = false;
        mWindow.ShutDown();
        SDL_Quit();
    }

    // singleton
    Engine* Engine::mInstance = nullptr;

    Engine::Engine()
        : mIsRunning(false)
    {
        GetInfo();
    }

    void Engine::GetInfo()
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
