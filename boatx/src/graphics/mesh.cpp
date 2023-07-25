#include "boatx/graphics/mesh.h"
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
        glGenVertexArrays(1, &mVao);
        glBindVertexArray(mVao);

        glGenBuffers(1, &mPositionVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertexArray, GL_STATIC_DRAW);

        glEnableVertexAttribArray(kPositionAttribIndex);
        glVertexAttribPointer(kPositionAttribIndex, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(GL_FLOAT), 0);
        glDisableVertexAttribArray(kPositionAttribIndex);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(0);
    }

    Mesh::Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions, uint32_t* elementArray, uint32_t elementCount)
        : Mesh(vertexArray, vertexCount, dimensions)
    {
        mElementCount = elementCount;
        glBindVertexArray(mVao);

        glGenBuffers(1, &mEbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(uint32_t), elementArray, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &mPositionVbo);
        if (mEbo > 0)
        {
            glDeleteBuffers(1, &mEbo);
        }
        glDeleteVertexArrays(1, &mVao);
    }

    void Mesh::Bind()
    {
        glBindVertexArray(mVao);
        glEnableVertexAttribArray(kPositionAttribIndex);
    }

    void Mesh::Unbind()
    {
        glDisableVertexAttribArray(kPositionAttribIndex);
        glBindVertexArray(0);
    }

    TextQuadMesh::TextQuadMesh()
        : mVao(0)
        , mVbo(0)
    {
        glGenVertexArrays(1, &mVao);
        glBindVertexArray(mVao);

        glGenBuffers(1, &mVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBufferData(GL_ARRAY_BUFFER, kVertexCount * kDimensions * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(kPositionAttribIndex);
        glVertexAttribPointer(kPositionAttribIndex, kDimensions, GL_FLOAT, 0, kDimensions * sizeof(GLfloat), 0);
        glDisableVertexAttribArray(kPositionAttribIndex);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    TextQuadMesh::~TextQuadMesh()
    {
        glDeleteBuffers(1, &mVbo);
        glDeleteVertexArrays(1, &mVao);
    }

    void TextQuadMesh::Bind()
    {
        glBindVertexArray(mVao);
        glEnableVertexAttribArray(kPositionAttribIndex);

        // set vbo
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, kVertexCount * kDimensions * sizeof(GLfloat), mVertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // bind character texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureID);
    }

    void TextQuadMesh::Config(float* vertexArray, uint32_t textureID)
    {
        mVertexArray = vertexArray;
        mTextureID = textureID;
    }

    void TextQuadMesh::Unbind()
    {
        glDisableVertexAttribArray(kPositionAttribIndex);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}