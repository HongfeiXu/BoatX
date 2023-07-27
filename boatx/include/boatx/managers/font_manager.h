#pragma once

#include "external/glm/glm.hpp"
#include "boatx/graphics/mesh.h"
#include "boatx/graphics/shader.h"

#include <string>
#include <map>
#include <memory>

namespace boatx::managers
{
    // Font Character Glyph info
    struct Character {
        unsigned int      TextureID;
        glm::ivec2  Size;
        glm::ivec2  Bearing;
        unsigned int      Adavance;
    };


    /************************************************************************/
    /* Handles spdlog setup                                                 */
    /************************************************************************/
    class FontManager
    {
    public:
        FontManager() = default;
        ~FontManager() = default;

        void Initialize();
        void ShutDown();

        void LoadCharacters(const std::string& fontPath);
        Character GetCharacter(char c);

        void InitTextQuadMesh();
        void InitTextShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        auto GetTextQuadMesh() { return mTextQuadMesh; }
        auto GetTextShader() { return mTextShader; }

    private:
        std::string                 mFontPath;
        std::map<char, Character>   mCharacters; // cache to speed up later text rendering

        std::shared_ptr<graphics::TextQuadMesh> mTextQuadMesh;
        std::shared_ptr<graphics::Shader>       mTextShader;
    };
}
