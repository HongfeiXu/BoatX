#include "boatx/graphics/helpers.h"
#include "glad/glad.h"
#include <string>

namespace boatx::graphics
{
    void CheckGLError()
    {
        GLenum error = glGetError();
        bool shouldAssert = error != GL_NO_ERROR;
        while (error != GL_NO_ERROR)
        {
            std::string errorStr;
            switch (error)
            {
            case GL_INVALID_OPERATION:              errorStr = "GL_INVALID_OPERATION"; break;
            case GL_INVALID_ENUM:                   errorStr = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                  errorStr = "GL_INVALID_VALUE"; break;
            case GL_OUT_OF_MEMORY:                  errorStr = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                                errorStr = std::to_string(error); break;
            }
            BOATX_ERROR("OpenGL Error: {}", errorStr.c_str());
            error = glGetError();
        }
        BOATX_ASSERT(!shouldAssert, "OpenGL Error!");
    }
}