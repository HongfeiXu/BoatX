#include "core/window.h"
#include "sdl2/SDL.h"
#include "engine.h"

#include <iostream>

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

    bool Window::Create()
    {
        mWindow = SDL_CreateWindow("BoatXGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        if (!mWindow)
        {
            std::cout << "Error creating window: " << SDL_GetError() << std::endl;
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
            default:
                break;
            }
        }
    }

}
