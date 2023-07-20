#pragma once

#include <queue>
#include "graphics/render_commands.h"

namespace boatx::managers
{
    class RenderManager
    {
    public:
        RenderManager() {};
        ~RenderManager() {};

        void Initialize();
        void ShutDown();

        void Clear();
        void SetClearColor(float r, float g, float b, float a);
        void SetWireFrameMode(bool enabled);

        void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);

        // Execute submitted RenderCommands _in the order they were received_.
        // We can extend the API if we need to mitigate performance impact
        void Flush();

    private:
        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> mRenderCommands;
    };
}
