#pragma once

#include <cinttypes>

namespace boatx::graphics
{
    /************************************************************************/
    /* Handles VAO VBO EBO setup                                            */
    /************************************************************************/
    class Mesh 
    {
    public:
        Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions);
        Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions, uint32_t* elementArray, uint32_t elementCount);
        ~Mesh();

        void Bind();
        void Unbind();

        inline uint32_t GetVertexCount() const { return mVertexCount; }
        inline uint32_t GetElementCount() const { return mElementCount; }

    private:
        uint32_t mVertexCount, mElementCount;
        uint32_t mVao, mEbo;
        uint32_t mPositionVbo;

        static const uint32_t kPositionAttribIndex{ 0 };
    };

    class TextQuadMesh
    {
    public:
        TextQuadMesh();
        ~TextQuadMesh();

        void Config(float* vertexArray, uint32_t textureID);
        void Bind();
        void Unbind();

        inline uint32_t GetVertexCount() const { return kVertexCount; }
    private:
        uint32_t mVao;
        uint32_t mVbo;
        uint32_t mTextureID;
        float* mVertexArray{ nullptr };
        

        static const uint32_t kDimensions{ 4 }; // vec2 pos, vec2 tex
        static const uint32_t kVertexCount{ 6 }; // 1 text quad has 2 triangles, 2 triangles has 6 vertices
        static const uint32_t kPositionAttribIndex{ 0 };
    };
}