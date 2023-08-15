#pragma once

#include "boatx/core/window.h"
#include "boatx/managers/log_manager.h"
#include "boatx/managers/path_manager.h"
#include "boatx/managers/render_manager.h"
#include "boatx/managers/font_manager.h"
#include <chrono>
#include <cstdint>

namespace boatx
{
    class Engine 
    {
        static const float sFpsAlpha;

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
        inline managers::FontManager& GetFontManager() { return mFontManager; }

        float GetDeltaTime() const noexcept { return mDeltaTime; }
        uint32_t GetFps() const noexcept { return mFps; }

    private:
        // Singleton
        Engine();

        void GetInfo();
        void ShutDown();

        void InitializeManagers(const std::string& binPath);
        void ShutDownManagers();

        /**
         *  Each frame can only be called once
         */
        void CalculateDeltaTime();
        void CalculateFps();

    private:
        core::Window    mWindow;
        bool            mIsRunning{ false };
        bool            mIsInitialized{false};

        // Managers
        managers::PathManager   mPathManager;
        managers::LogManager    mLogManager;
        managers::RenderManager mRenderManager;
        managers::FontManager   mFontManager;

        // delta time and fps
        float                                   mDeltaTime{ 1 };
        std::chrono::steady_clock::time_point   mLastTickTimePoint {std::chrono::steady_clock::now()};
        float                                   mAverageDuration{ 0.f };
        uint32_t                                mFrameCount{ 0 };
        uint32_t                                mFps{ 0 };
    };
}
