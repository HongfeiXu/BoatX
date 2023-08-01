#include "boatx/managers/render_manager.h"
#include "boatx/managers/font_manager.h"
#include "boatx/graphics/helpers.h"
#include "boatx/log.h"
#include "glad/glad.h"

namespace boatx::managers
{

    void RenderManager::Initialize()
    {
        // OpenGL info
        {
            GLint maxVertexAttribs;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs); BOATX_CHECK_GL_ERROR;
            BOATX_INFO("OpenGL Info:\n Vendor:\t{}\n Renderer:\t{}\n GL Version:\t{}\n Shading Language Version:\t{}\nMaximum number of vertex attributes supported:\t{}", 
                (const char*)glGetString(GL_VENDOR), 
                (const char*)glGetString(GL_RENDERER), 
                (const char*)glGetString(GL_VERSION), 
                (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION),
                maxVertexAttribs); BOATX_CHECK_GL_ERROR;
        }

        glEnable(GL_DEPTH_TEST); BOATX_CHECK_GL_ERROR;
        glDepthFunc(GL_LEQUAL); BOATX_CHECK_GL_ERROR;

        glEnable(GL_BLEND); BOATX_CHECK_GL_ERROR;
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); BOATX_CHECK_GL_ERROR;

        SetClearColor(
            static_cast<float>(0x64) / static_cast<float>(0xFF),
            static_cast<float>(0x95) / static_cast<float>(0xFF),
            static_cast<float>(0xED) / static_cast<float>(0xFF),
            1
        ); // cornflower blue
    }

    void RenderManager::ShutDown()
    {
        while (mRenderCommands.size() > 0)
        {
            mRenderCommands.pop();
        }
    }

    void RenderManager::Clear()
    {
        BOATX_ASSERT(mRenderCommands.size() == 0, "Unflush render commands in queue!");

        while (!mRenderCommands.empty())
        {
            mRenderCommands.pop();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); BOATX_CHECK_GL_ERROR;
    }

    void RenderManager::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a); BOATX_CHECK_GL_ERROR;

    }

    void RenderManager::SetWireFrameMode(bool enabled)
    {
        if (enabled)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); BOATX_CHECK_GL_ERROR;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); BOATX_CHECK_GL_ERROR;
        }
    }

    void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc)
    {
        mRenderCommands.push(std::move(rc));
    }

    void RenderManager::Flush()
    {
        while (mRenderCommands.size() > 0)
        {
            auto rc = std::move(mRenderCommands.front());
            mRenderCommands.pop();
            rc->Execute();
        }
    }

    void RenderManager::RenderText(const std::string& text, FontManager& fontManager, glm::vec2 startPos, float scale)
    {
        GLfloat x = startPos[0], y = startPos[1];
        for (auto c = text.cbegin(); c != text.cend(); ++c)
        {
            auto& ch = fontManager.GetCharacter(*c);
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
            auto rt = std::make_unique<graphics::rendercommands::RenderTextQuadMesh>(
                fontManager.GetTextQuadMesh(),
                fontManager.GetTextShader()
            );
            fontManager.GetTextQuadMesh()->Config(textVertices, ch.TextureID);
            Submit(std::move(rt));
            Flush();
            x += (ch.Adavance >> 6) * scale;
        }
    }
}

