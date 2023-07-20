#include "engine.h"
#include "sdl2/SDL.h"
#include "log.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/render_commands.h"
#include "glad/glad.h"

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

            core::WindowCreateInfo windowCreateInfo{800, 600, 200, 200, "BoatXEngine"};
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
            // Test Shader
            std::string vertexShaderSource = R"(
                #version 410 core
                layout (location = 0) in vec3 vPos;
                void main()
                {
                    gl_Position = vec4(vPos, 1.0);
                }
            )";

            std::string fragmentShaderSource = R"(
                #version 410 core
                out vec4 outColor;

                uniform vec3 color = vec3(0.0);
                void main()
                {
                    outColor = vec4(color, 1.0);
                }
            )";

            // Test Mesh
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
            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(vertexShaderSource, fragmentShaderSource);

            shader->SetUniformFloat3("color", 1, 1, 0);

            mRenderManager.SetWireFrameMode(true);

            // core loop
            while (mIsRunning)
            {
                mWindow.PumpEvents();
                mWindow.BeginRender();

                // render stuff..
                auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
                mRenderManager.Submit(std::move(rc));
                mRenderManager.Flush();

                mWindow.EndRender();
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
    }

    void Engine::ShutDownManagers()
    {
        // usually in reverse order
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
