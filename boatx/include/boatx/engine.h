#pragma once

#include "core/window.h"

namespace boatx
{
    class Engine {
    public:
        ~Engine() = default;
        // singleton
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        static Engine& Instance();

        void Run();
        inline void Quit() { mIsRunning = false; };

    private:
        // singleton
        Engine();

        void GetInfo();
        bool Initialize();
        void ShutDown();

    private:
        core::Window mWindow;
        bool mIsRunning;
    };
}
