#include "boatx/graphics/render_commands.h"
#include "boatx/log.h"

#include "boatx/graphics/mesh.h"
#include "boatx/graphics/shader.h"
#include "boatx/graphics/helpers.h"

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
                glDrawElements(GL_TRIANGLES, mesh->GetElementCount(), GL_UNSIGNED_INT, 0); BOATX_CHECK_GL_ERROR;
            }
            else
            {
                glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount()); BOATX_CHECK_GL_ERROR;
            }
            mesh->Unbind();
            shader->Unbind();
        }
        else
        {
            BOATX_ERROR("Attempting to execute RenderMesh with invalid data");
        }
    }

    void RenderTextQuadMesh::Execute()
    {
        std::shared_ptr<TextQuadMesh> textQuadMesh = mTextQuadMesh.lock();
        std::shared_ptr<Shader> shader = mShader.lock();

        if (textQuadMesh && shader)
        {
            shader->Bind();
            textQuadMesh->Bind();
            glDrawArrays(GL_TRIANGLES, 0, textQuadMesh->GetVertexCount()); BOATX_CHECK_GL_ERROR;
            textQuadMesh->Unbind();
            shader->Unbind();
        }
        else
        {
            BOATX_ERROR("Attempting to execute RenderTextQuadMesh with invalid data");
        }
    }

}

