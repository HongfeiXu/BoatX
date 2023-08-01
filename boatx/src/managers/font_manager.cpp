#include "boatx/managers/font_manager.h"
#include "boatx/log.h"
#include "glad/glad.h"
#include "external/glm/ext.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace boatx::managers
{

    void FontManager::Initialize()
    {
    }

    void FontManager::ShutDown()
    {
        mFontPath.clear();
        mCharacters.clear();
        mTextQuadMesh.reset();
        mTextShader.reset();
    }

    void FontManager::LoadCharacters(const std::string& fontPath)
    {
        mCharacters.clear();
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            BOATX_ERROR("Could not init FreeType Library");
        }
        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        {
            BOATX_ERROR("Failed to load Font");
        }
        FT_Set_Pixel_Sizes(face, 0, 48);
        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        {
            BOATX_ERROR("Failed to load Glyph");
        }
        std::map<GLchar, Character> Characters; // TODO manager it by font manager?
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // TODO need recover?
        for (GLubyte c = 0; c < 128; ++c)
        {
            // load glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                BOATX_ERROR("Failed to load Glyph");
                continue;
            }
            // generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // configure texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // save for use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            };
            mCharacters.insert(std::pair<GLchar, Character>(c, character));
        }
        // clear freetype resource
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    Character FontManager::GetCharacter(char c)
    {
        return mCharacters[c];  // not safe!
    }

    void FontManager::InitTextQuadMesh()
    {
        mTextQuadMesh = std::make_shared<graphics::TextQuadMesh>();
    }

    void FontManager::InitTextShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
       mTextShader = std::make_shared<graphics::Shader>();
       mTextShader->InitFromFile(vertexShaderPath, fragmentShaderPath);
       glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
       mTextShader->SetUniformMatrix4("projection", projection);
       mTextShader->SetUniformFloat3("textColor", 0, 1, 0);
       mTextShader->SetUniformInt("text", 0);
    }
}
