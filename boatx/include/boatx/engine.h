#pragma once

#include "core/window.h"
#include "managers/logmanager.h"

namespace boatx
{
    class Engine {
    public:
        ~Engine() = default;
        // Singleton
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        static Engine& Instance();

        void Run();
        inline void Quit() { mIsRunning = false; };

    private:
        // Singleton
        Engine();

        void GetInfo();

        bool Initialize();
        void ShutDown();

    private:
        core::Window mWindow;
        bool mIsRunning;
        bool mIsInitialized;

        // Managers
        managers::LogManager mLogManager;
    };
}
