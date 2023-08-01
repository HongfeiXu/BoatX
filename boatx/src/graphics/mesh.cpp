#include "boatx/graphics/mesh.h"
#include "boatx/graphics/helpers.h"
#include "glad/glad.h"

namespace boatx::graphics
{
    Mesh::Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions)
        : mVertexCount(vertexCount)
        , mElementCount(0)
        , mVao(0)
        , mEbo(0)
        , mPositionVbo(0)
    {
        glGenVertexArrays(1, &mVao); BOATX_CHECK_GL_ERROR;
        glBindVertexArray(mVao); BOATX_CHECK_GL_ERROR;

        glGenBuffers(1, &mPositionVbo); BOATX_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo); BOATX_CHECK_GL_ERROR;
        glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertexArray, GL_STATIC_DRAW); BOATX_CHECK_GL_ERROR;

        glEnableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
        glVertexAttribPointer(kPositionAttribIndex, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(GL_FLOAT), 0); BOATX_CHECK_GL_ERROR;
        glDisableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, 0); BOATX_CHECK_GL_ERROR;
        
        glBindVertexArray(0); BOATX_CHECK_GL_ERROR;
    }

    Mesh::Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions, uint32_t* elementArray, uint32_t elementCount)
        : Mesh(vertexArray, vertexCount, dimensions)
    {
        mElementCount = elementCount;
        glBindVertexArray(mVao); BOATX_CHECK_GL_ERROR;

        glGenBuffers(1, &mEbo); BOATX_CHECK_GL_ERROR;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo); BOATX_CHECK_GL_ERROR;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(uint32_t), elementArray, GL_STATIC_DRAW); BOATX_CHECK_GL_ERROR;

        // leave ebo bound, not like vbo

        glBindVertexArray(0); BOATX_CHECK_GL_ERROR;
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &mPositionVbo); BOATX_CHECK_GL_ERROR;
        if (mEbo > 0)
        {
            glDeleteBuffers(1, &mEbo); BOATX_CHECK_GL_ERROR;
        }
        glDeleteVertexArrays(1, &mVao); BOATX_CHECK_GL_ERROR;
    }

    void Mesh::Bind()
    {
        glBindVertexArray(mVao); BOATX_CHECK_GL_ERROR;
        glEnableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
    }

    void Mesh::Unbind()
    {
        glDisableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
        glBindVertexArray(0); BOATX_CHECK_GL_ERROR;
    }

    TextQuadMesh::TextQuadMesh()
        : mVao(0)
        , mVbo(0)
    {
        glGenVertexArrays(1, &mVao); BOATX_CHECK_GL_ERROR;
        glBindVertexArray(mVao); BOATX_CHECK_GL_ERROR;

        glGenBuffers(1, &mVbo); BOATX_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, mVbo); BOATX_CHECK_GL_ERROR;
        glBufferData(GL_ARRAY_BUFFER, kVertexCount * kDimensions * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW); BOATX_CHECK_GL_ERROR;

        glEnableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
        glVertexAttribPointer(kPositionAttribIndex, kDimensions, GL_FLOAT, 0, kDimensions * sizeof(GLfloat), 0); BOATX_CHECK_GL_ERROR;
        glDisableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, 0); BOATX_CHECK_GL_ERROR;

        glBindVertexArray(0); BOATX_CHECK_GL_ERROR;
    }

    TextQuadMesh::~TextQuadMesh()
    {
        glDeleteBuffers(1, &mVbo); BOATX_CHECK_GL_ERROR;
        glDeleteVertexArrays(1, &mVao); BOATX_CHECK_GL_ERROR;
    }

    void TextQuadMesh::Bind()
    {
        glBindVertexArray(mVao); BOATX_CHECK_GL_ERROR;
        glEnableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;

        // set vbo
        glBindBuffer(GL_ARRAY_BUFFER, mVbo); BOATX_CHECK_GL_ERROR;
        glBufferSubData(GL_ARRAY_BUFFER, 0, kVertexCount * kDimensions * sizeof(GLfloat), mVertexArray); BOATX_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, 0); BOATX_CHECK_GL_ERROR;

        // bind character texture
        glActiveTexture(GL_TEXTURE0); BOATX_CHECK_GL_ERROR;
        glBindTexture(GL_TEXTURE_2D, mTextureID); BOATX_CHECK_GL_ERROR;
    }

    void TextQuadMesh::Config(float* vertexArray, uint32_t textureID)
    {
        mVertexArray = vertexArray;
        mTextureID = textureID;
    }

    void TextQuadMesh::Unbind()
    {
        glDisableVertexAttribArray(kPositionAttribIndex); BOATX_CHECK_GL_ERROR;
        glBindVertexArray(0); BOATX_CHECK_GL_ERROR;
        glBindTexture(GL_TEXTURE_2D, 0); BOATX_CHECK_GL_ERROR;
    }
}