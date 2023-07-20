#include "graphics/render_commands.h"
#include "log.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"

#include "glad/glad.h"

namespace boatx::graphics::rendercommands
{
    void RenderMesh::Execute()
    {
        std::shared_ptr<Mesh> mesh = mMesh.lock();
        std::shared_ptr<Shader> shader = mShader.lock();

        if (mesh && shader)
        {
            shader->Bind();
            mesh->Bind();
            if (mesh->GetElementCount() > 0)
            {
                glDrawElements(GL_TRIANGLES, mesh->GetElementCount(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());
            }
            mesh->Unbind();
            shader->Unbind();
        }
        else
        {
            BOATX_ERROR("Attempting to execute RenderMesh with invalid data");
        }
    }
}

