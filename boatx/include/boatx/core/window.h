#pragma once

#include "external/glm/glm.hpp"

struct SDL_Window;

using SDL_GLContext = void *;

namespace boatx::core 
{
    struct WindowCreateInfo
    {
        int         width{ 1280 };
        int         height{ 720 };
        int         minWidth{ 200 };
        int         minHeight{ 200 };
        const char* title{ "BoatX" };
    };

    class Window 
    {
    public:
        Window();
        ~Window();

        bool Create(const WindowCreateInfo& windowCreateInfo);
        void ShutDown();

        void PumpEvents();
        
        void BeginRender();
        void EndRender();

        glm::ivec2 GetWindowSize();

    private:
        SDL_Window*     mWindow;
        SDL_GLContext   mGLContext;
    };
}