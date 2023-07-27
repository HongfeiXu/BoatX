#pragma once

#include "boatx/core/window.h"
#include "boatx/managers/log_manager.h"
#include "boatx/managers/path_manager.h"
#include "boatx/managers/render_manager.h"
#include "boatx/managers/font_manager.h"

namespace boatx
{
    class Engine 
    {
    public:
        ~Engine() = default;
        // Singleton
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        static Engine& Instance();

        bool Initialize(const std::string& binPath);
        void Run();
        inline void Quit() { mIsRunning = false; };

        // Managers
        inline managers::RenderManager& GetRenderManager() { return mRenderManager; }
        inline managers::PathManager& GetPathManager() { return mPathManager; }

    private:
        // Singleton
        Engine();

        void GetInfo();
        void ShutDown();

        void InitializeManagers(const std::string& binPath);
        void ShutDownManagers();

    private:
        core::Window    mWindow;
        bool            mIsRunning;
        bool            mIsInitialized;

        // Managers
        managers::PathManager   mPathManager;
        managers::LogManager    mLogManager;
        managers::RenderManager mRenderManager;
        managers::FontManager   mFontManager;
    };
}
