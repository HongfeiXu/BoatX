#pragma once

#include <queue>
#include <string>

#include "boatx/graphics/render_commands.h"
#include "external/glm/glm.hpp"

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
        void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

        void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);

        // Execute submitted RenderCommands _in the order they were received_.
        // We can extend the API if we need to mitigate performance impact
        void Flush();

        void RenderText(const std::string& text, const glm::vec2&windowSize, const glm::vec2& startPos, float scale);

    private:
        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> mRenderCommands;
    };
}
