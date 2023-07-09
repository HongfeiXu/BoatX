#pragma once

struct SDL_Window;


namespace boatx::core 
{
    class Window 
    {
    public:
        Window();
        ~Window();

        bool Create();
        void ShutDown();

        void PumpEvents();

    private:
        SDL_Window* mWindow;
    };
}