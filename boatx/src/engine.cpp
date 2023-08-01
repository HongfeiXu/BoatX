#include "boatx/engine.h"
#include "sdl2/SDL.h"
#include "boatx/log.h"

#include "boatx/graphics/mesh.h"
#include "boatx/graphics/shader.h"
#include "boatx/graphics/render_commands.h"
#include "glad/glad.h"

#include <chrono>

namespace boatx
{
    Engine& Engine::Instance()
    {
        static Engine instance;
        return instance;
    }

    bool Engine::Initialize(const std::string& binPath)
    {
        BOATX_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize() more than once!");

        // Initialize Managers
        InitializeManagers(binPath);

        // GetInfo after Managers initialized
        GetInfo();

        bool ret = false;
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            BOATX_ERROR("Error initialize SDL2: {}", SDL_GetError());
        }
        else
        {
            SDL_version version;
            SDL_VERSION(&version);
            BOATX_INFO("Version of SDL2: {}.{}.{}", (uint32_t)version.major, (uint32_t)version.minor, (uint32_t)version.patch);

            core::WindowCreateInfo windowCreateInfo{800, 600, 200, 200, "BoatXEngine"}; // TODO: Load from file
            if (mWindow.Create(windowCreateInfo))
            {
                // Initialize RenderManager
                mRenderManager.Initialize();

                ret = true;
                mIsRunning = true;
                mIsInitialized = true;
            }
        }

        if (!ret)
        {
            BOATX_ERROR("Engine initialization failed. Shutting down.");
            ShutDown();
        }

        return ret;
    }

    void Engine::Run()
    {
        if (mIsInitialized)
        {
            // {Rectangle Rendering}
            float vertices[] = {
                0.5f, 0.5f, 0.0f,   // right top
                0.5f, -0.5f, 0.0f,  // right bottom
                -0.5f, -0.5f, 0.0f, // left bottom
                -0.5f, 0.5f, 0.0f   // left top
            };
            unsigned int indices[] = {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
            };
            std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh>(vertices, 4, 3, indices, 6);
            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>();
            std::string vertexShaderPath = mPathManager.GetShaderPath("abc_vert.glsl");
            std::string fragmentShaderPath = mPathManager.GetShaderPath("abc_frag.glsl");
            shader->InitFromFile(vertexShaderPath, fragmentShaderPath);
            shader->SetUniformFloat3("color", 1, 1, 1);
            // {Rectangle Rendering} end

            // {Triangle Rendering}
            float vertices2[] = {
                -0.5f, -0.5f, 0.f,
                 0.5f, -0.5f, 0.f,
                 0.0f,  0.5f, 0.f
            };
            std::shared_ptr<graphics::Mesh> triangleMesh = std::make_shared<graphics::Mesh>(vertices2, 3, 3);
            std::shared_ptr<graphics::Shader> triangleShader = std::make_shared<graphics::Shader>();
            triangleShader->InitFromFile(vertexShaderPath, fragmentShaderPath);
            triangleShader->SetUniformFloat3("color", 0.5, 0.5, 0.5);
            // {Triangle Rendering} end

            // {Text Rendering}
            mFontManager.LoadCharacters(mPathManager.GetFontPath("arial.ttf"));
            mFontManager.InitTextQuadMesh();
            mFontManager.InitTextShader(mPathManager.GetShaderPath("text_vert.glsl"), mPathManager.GetShaderPath("text_frag.glsl"));
            // {Text Rendering} end

            // fps
            double fps = 0;
            double deltaTime = 0;
            auto startTime = std::chrono::steady_clock::now();

            mRenderManager.SetWireFrameMode(false);
            // core loop
            while (mIsRunning)
            {
                mWindow.PumpEvents();
                mWindow.BeginRender();
                {
                    // render normal stuff..
                    // rectangle
                    auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
                    mRenderManager.Submit(std::move(rc));
                    // triangle
                    auto rc2 = std::make_unique<graphics::rendercommands::RenderMesh>(triangleMesh, triangleShader);
                    mRenderManager.Submit(std::move(rc2));

                    mRenderManager.Flush();

                    // render fps text...
                    std::string fpsString = "fps: " + std::to_string((int)fps);
                    mRenderManager.RenderText(fpsString, mFontManager, glm::vec2(10, mWindow.GetWindowSize()[1] - 30), 0.4f);
                }
                mWindow.EndRender();

                // fps
                auto endTime = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
                startTime = endTime;
                deltaTime = elapsedTime / 1000.0;
                fps = 1.0 / deltaTime;
            }
        }

        ShutDown();
    }

    void Engine::ShutDown()
    {
        mIsRunning = false;
        mIsInitialized = false;

        // Shutdown Managers
        ShutDownManagers();

        // Shutdown SDL
        mWindow.ShutDown();
        SDL_Quit();
    }

    void Engine::InitializeManagers(const std::string& binPath)
    {
        mPathManager.Initialize(binPath);
        mLogManager.Initialize(mPathManager.GetLogFolderPath());
        mFontManager.Initialize();
    }

    void Engine::ShutDownManagers()
    {
        // usually in reverse order
        mFontManager.ShutDown();
        mRenderManager.ShutDown();
        mLogManager.ShutDown();
        mPathManager.ShutDown();
    }

    Engine::Engine()
        : mIsRunning(false)
        , mIsInitialized(false)
    {
    }

    void Engine::GetInfo()
    {
#ifdef BOATX_CONFIG_DEBUG
        BOATX_DEBUG("Configurations: DEBUG");
#endif
#ifdef BOATX_CONFIG_RELEASE
        BOATX_DEBUG("Configurations: RELEASE");
#endif

#ifdef BOATX_PLATFORM_WINDOWS
        BOATX_DEBUG("Platform: WINDOWS");
#endif
#ifdef BOATX_PLATFORM_MAC
        BOATX_DEBUG("Platform: MAC");
#endif
#ifdef BOATX_PLATFORM_LINUX
        BOATX_DEBUG("Platform: LINUX");
#endif
    }
} // namespace boatx
