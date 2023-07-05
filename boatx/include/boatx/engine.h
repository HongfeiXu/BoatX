#pragma once

#include "core/window.h"

namespace boatx
{
    class Engine {
    public:
        ~Engine() {}
        static Engine& Instance();
        void Run();

        inline void Quit() { mIsRunning = false; };

    private:
        void GetInfo();
        bool Initialize();
        void ShutDown();

    private:
        core::Window mWindow;
        bool mIsRunning;

        // singleton
        Engine();
        static Engine* mInstance;
    };
}
