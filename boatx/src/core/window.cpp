#include "core/window.h"
#include "sdl2/SDL.h"
#include "engine.h"
#include "log.h"
#include "glad/glad.h"

namespace boatx::core
{
    Window::Window() : mWindow(nullptr) { }

    Window::~Window() 
    {
        if (mWindow)
        {
            ShutDown();
        }
    }

    bool Window::Create(const WindowCreateInfo& windowCreateInfo)
    {
        mWindow = SDL_CreateWindow(windowCreateInfo.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowCreateInfo.width, windowCreateInfo.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!mWindow)
        {
            BOATX_ERROR("Error creating window: {}", SDL_GetError());
            return false;
        }

#ifdef BOATX_PLATFORM_MAC
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_SetWindowMinimumSize(mWindow, 200, 200);
        
        mGLContext = SDL_GL_CreateContext(mWindow);
        if (mGLContext == nullptr)
        {
            BOATX_ERROR("Error creating OpenGL context {}", SDL_GetError());
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        // TODO: Move this to a renderer initialization
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClearColor(
            static_cast<float>(0x64) / static_cast<float>(0xFF),
            static_cast<float>(0x95) / static_cast<float>(0xFF),
            static_cast<float>(0xED) / static_cast<float>(0xFF),
            1
        );

        return true;
    }

    void Window::ShutDown()
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    void Window::PumpEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                Engine::Instance().Quit();
                break;
            default:
                break;
            }
        }
    }

    void Window::BeginRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EndRender()
    {
        SDL_GL_SwapWindow(mWindow);
    }
}
