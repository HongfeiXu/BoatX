#include "boatx/core/window.h"
#include "sdl2/SDL.h"
#include "boatx/engine.h"
#include "boatx/log.h"
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

        SDL_SetWindowMinimumSize(mWindow, windowCreateInfo.minWidth, windowCreateInfo.minHeight);
        
        mGLContext = SDL_GL_CreateContext(mWindow);
        if (mGLContext == nullptr)
        {
            BOATX_ERROR("Error creating OpenGL context {}", SDL_GetError());
            return false;
        }

        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        {
            BOATX_ERROR("Error gladLoadGLLoader");
            return false;
        }

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
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    Engine::Instance().Quit();
                }
                break;
            default:
                break;
            }
        }
    }

    void Window::BeginRender()
    {
        Engine::Instance().GetRenderManager().Clear();
    }

    void Window::EndRender()
    {
        SDL_GL_SwapWindow(mWindow);
    }

    glm::ivec2 Window::GetWindowSize()
    {
        if (!mWindow)
        {
            return glm::ivec2(0, 0);
        }
        int x;
        int y;
        SDL_GetWindowSize(mWindow, &x, &y);
        return glm::ivec2(x, y);
    }

    void Window::SetTitle(const std::string& title)
    {
        SDL_SetWindowTitle(mWindow, title.c_str());
    }

    void Window::SetSwapInterval(int interval)
    {
        int succ = SDL_GL_SetSwapInterval(interval);
        if (succ != 0)
        {
            BOATX_ERROR("Error SetSwapInterval {}", SDL_GetError());
        }
    }
}
