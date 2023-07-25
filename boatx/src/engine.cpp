#include "boatx/engine.h"
#include "sdl2/SDL.h"
#include "boatx/log.h"

#include "boatx/graphics/mesh.h"
#include "boatx/graphics/shader.h"
#include "boatx/graphics/render_commands.h"
#include "glad/glad.h"


// {Text Rendering}
#include "ft2build.h"
#include FT_FREETYPE_H
#include "external/glm/glm.hpp"
#include "external/glm/ext.hpp"
#include <map>
// {Text Rendering} end


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

    // {Text Rendering}
    // glyph info
    struct Character {
        GLuint      TextureID;
        glm::ivec2  Size;
        glm::ivec2  Bearing;
        GLuint      Adavance;
    };

    void RenderText(const std::string& text,
        std::map<GLchar, Character>& Characters,
        std::shared_ptr<graphics::TextQuadMesh> textQuadMesh,
        std::shared_ptr<graphics::Shader> textShader,
        managers::RenderManager& renderManager)
    {
        GLfloat x = 0, y = 500, scale = 0.5f;
        for (auto c = text.cbegin(); c != text.cend(); ++c)
        {
            auto &ch = Characters[*c];
            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            GLfloat textVertices[] = {
                xpos,     ypos + h,   0.0, 0.0,
                xpos,     ypos,       0.0, 1.0,
                xpos + w, ypos,       1.0, 1.0,

                xpos,     ypos + h,   0.0, 0.0,
                xpos + w, ypos,       1.0, 1.0,
                xpos + w, ypos + h,   1.0, 0.0
            };
            auto rt = std::make_unique<graphics::rendercommands::RenderTextQuadMesh>(textQuadMesh, textShader);
            textQuadMesh->Config(textVertices, ch.TextureID);
            renderManager.Submit(std::move(rt));
            renderManager.Flush();
            x += (ch.Adavance >> 6) * scale;
        }
    }
    // {Text Rendering} end

    void Engine::Run()
    {
        if (mIsInitialized)
        {
            // {Rectangle Rendering}
            // Test Shader
            std::string vertexShaderPath = mPathManager.GetShaderPath("abc_vert.glsl");
            std::string fragmentShaderPath = mPathManager.GetShaderPath("abc_frag.glsl");
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
            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>();
            shader->InitFromFile(vertexShaderPath, fragmentShaderPath);
            shader->SetUniformFloat3("color", 1, 1, 0);
            // {Rectangle Rendering} end

            // {Text Rendering}
            FT_Library ft;
            if (FT_Init_FreeType(&ft))
            {
                BOATX_ERROR("Could not init FreeType Library");
            }
            FT_Face face;
            if (FT_New_Face(ft, mPathManager.GetFontPath("arial.ttf").c_str(), 0, &face))
            {
                BOATX_ERROR("Failed to load Font");
            }
            FT_Set_Pixel_Sizes(face, 0, 48);
            if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            {
                BOATX_ERROR("Failed to load Glyph");
            }
            std::map<GLchar, Character> Characters; // TODO manager it by font manager?
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // TODO need recover?
            for (GLubyte c = 0; c < 128; ++c)
            {
                // load glyph
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    BOATX_ERROR("Failed to load Glyph");
                    continue;
                }
                // generate texture
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // configure texture
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // save for use
                Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<GLuint>(face->glyph->advance.x)
                };
                Characters.insert(std::pair<GLchar, Character>(c, character));
            }
            // clear freetype resource
            FT_Done_Face(face);
            FT_Done_FreeType(ft);

            std::shared_ptr<graphics::TextQuadMesh> textQuadMesh = std::make_shared<graphics::TextQuadMesh>();
            std::shared_ptr<graphics::Shader> textShader = std::make_shared<graphics::Shader>();
            std::string textVertexShaderPath = mPathManager.GetShaderPath("text_vert.glsl");
            std::string textFragmentShaderPath = mPathManager.GetShaderPath("text_frag.glsl");
            textShader->InitFromFile(textVertexShaderPath, textFragmentShaderPath);
            glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
            textShader->SetUniformMatrix4("projection", projection);
            textShader->SetUniformFloat3("textColor", 1, 0, 0);
            textShader->SetUniformInt("text", 0);
			// {Text Rendering} end

            mRenderManager.SetWireFrameMode(false);

            // core loop
            while (mIsRunning)
            {
                mWindow.PumpEvents();
                mWindow.BeginRender();

                // render stuff..
                auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
                mRenderManager.Submit(std::move(rc));
				mRenderManager.Flush();

                // render text... not elegant, but work..
                RenderText("fps: 999", Characters, textQuadMesh, textShader, mRenderManager);

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
