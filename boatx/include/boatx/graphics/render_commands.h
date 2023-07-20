#pragma once

#include <memory>

namespace boatx::graphics
{
    class Mesh;
    class Shader;

    namespace rendercommands
    {
        class RenderCommand 
        {
        public:
            ~RenderCommand() {}

            virtual void Execute() = 0;
        };

        class RenderMesh : public RenderCommand
        {
        public:
            RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader) 
                : mMesh(mesh), mShader(shader) {}

            void Execute() override;

        private:
            std::weak_ptr<Mesh>     mMesh;      // use weak ptr cause we don't want to controll Mesh's lifecircle
            std::weak_ptr<Shader>   mShader;
        };
    }
}