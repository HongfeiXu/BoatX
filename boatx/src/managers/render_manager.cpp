#include "boatx/managers/render_manager.h"
#include "boatx/log.h"
#include "glad/glad.h"

namespace boatx::managers
{

    void RenderManager::Initialize()
    {
        // OpenGL info
        {
            GLint maxVertexAttribs;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
            BOATX_INFO("OpenGL Info:\n Vendor:\t{}\n Renderer:\t{}\n GL Version:\t{}\n Shading Language Version:\t{}\nMaximum number of vertex attributes supported:\t{}", 
                (const char*)glGetString(GL_VENDOR), 
                (const char*)glGetString(GL_RENDERER), 
                (const char*)glGetString(GL_VERSION), 
                (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION),
                maxVertexAttribs);
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderManager::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);

    }

    void RenderManager::SetWireFrameMode(bool enabled)
    {
        if (enabled)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
}

