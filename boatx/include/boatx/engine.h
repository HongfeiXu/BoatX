#pragma once

#include "core/window.h"
#include "managers/log_manager.h"
#include "managers/path_manager.h"

namespace boatx
{
    class Engine {
    public:
        ~Engine() = default;
        // Singleton
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        static Engine& Instance();

        bool Initialize(const std::string& binPath);
        void Run();
        inline void Quit() { mIsRunning = false; };

    private:
        // Singleton
        Engine();

        void GetInfo();
        void ShutDown();

        void InitializeManagers(const std::string& binPath);
        void ShutDownManagers();

    private:
        core::Window mWindow;
        bool mIsRunning;
        bool mIsInitialized;

        // Managers
        managers::PathManager mPathManager;
        managers::LogManager mLogManager;
    };
}
