#include "engine.h"
#include "sdl2/SDL.h"
#include "log.h"

namespace boatx
{
    Engine& Engine::Instance()
    {
        static Engine instance;
        return instance;
    }

    void Engine::Run()
    {
        if (Initialize())
        {
            // core loop
            while (mIsRunning)
            {
                mWindow.PumpEvents();
            }
        }

        ShutDown();
    }

    bool Engine::Initialize()
    {
        BOATX_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize() more than once!");

        // Managers
        mLogManager.Initialize();

        GetInfo();

        bool ret = false;
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            BOATX_ERROR("Error initialize SDL2: {}", SDL_GetError());
        }
        else
        {
            SDL_version version;
            SDL_VERSION(&version);
            BOATX_INFO("Version of SDL2: {}.{}.{}", (uint32_t)version.major, (uint32_t)version.minor, (uint32_t)version.patch);

            if (mWindow.Create())
            {
                ret = true;
                mIsRunning = true;
                mIsInitialized = true;
            }
        }

        if (!ret)
        {
            BOATX_ERROR("Engine initialization failed. Shutting down.");
            ShutDown();
        }

        return ret;
    }

    void Engine::ShutDown()
    {
        mIsRunning = false;
        mIsInitialized = false;

        // Managers - usually in reverse order
        mLogManager.ShutDown();

        // Shutdown SDL
        mWindow.ShutDown();
        SDL_Quit();
    }

    Engine::Engine()
        : mIsRunning(false)
        , mIsInitialized(false)
    {
    }

    void Engine::GetInfo()
    {
#ifdef BOATX_CONFIG_DEBUG
        BOATX_DEBUG("Configurations: DEBUG");
#endif
#ifdef BOATX_CONFIG_RELEASE
        BOATX_DEBUG("Configurations: RELEASE");
#endif
#ifdef BOATX_PLATFORM_WINDOWS
        BOATX_DEBUG("Platform: WINDOWS");
#endif
#ifdef BOATX_PLATFORM_MAC
        BOATX_DEBUG("Platform: MAC");
#endif
#ifdef BOATX_PLATFORM_LINUX
        BOATX_DEBUG("Platform: LINUX");
#endif
    }
} // namespace boatx
