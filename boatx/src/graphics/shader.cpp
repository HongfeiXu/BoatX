#include "boatx/graphics/shader.h"
#include "boatx/graphics/helpers.h"
#include "boatx/log.h"
#include "glad/glad.h"
#include <fstream>
#include <sstream>

namespace boatx::graphics
{
    Shader::Shader()
        : mShaderProgram(0)
    {
    }

    void Shader::InitFromString(const std::string& vsSrc, const std::string& psSrc)
    {
        mShaderProgram = glCreateProgram(); BOATX_CHECK_GL_ERROR;

        GLint success = GL_FALSE;
        const GLsizei logSize = 512;
        char infoLog[logSize];

        // shader create and attach
        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER); BOATX_CHECK_GL_ERROR;
        {
            const GLchar* glSource = vsSrc.c_str();
            glShaderSource(vertexShader, 1, &glSource, nullptr); BOATX_CHECK_GL_ERROR;
            glCompileShader(vertexShader); BOATX_CHECK_GL_ERROR;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); BOATX_CHECK_GL_ERROR;
            if (success != GL_TRUE)
            {
                glGetShaderInfoLog(vertexShader, logSize, nullptr, infoLog); BOATX_CHECK_GL_ERROR;
                BOATX_ERROR("Vertex Shader compilation error: {}", infoLog);
            }
            else
            {
                glAttachShader(mShaderProgram, vertexShader); BOATX_CHECK_GL_ERROR;
            }
        }

        uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); BOATX_CHECK_GL_ERROR;
        if (success == GL_TRUE)
        {
            const GLchar* glSource = psSrc.c_str();
            glShaderSource(fragmentShader, 1, &glSource, nullptr); BOATX_CHECK_GL_ERROR;
            glCompileShader(fragmentShader); BOATX_CHECK_GL_ERROR;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); BOATX_CHECK_GL_ERROR;
            if (success != GL_TRUE)
            {
                glGetShaderInfoLog(fragmentShader, logSize, nullptr, infoLog); BOATX_CHECK_GL_ERROR;
                BOATX_ERROR("Fragment Shader compilation error: {}", infoLog);
            }
            else
            {
                glAttachShader(mShaderProgram, fragmentShader); BOATX_CHECK_GL_ERROR;
            }
        }

        BOATX_ASSERT(success == GL_TRUE, "Error compiling shader");

        // shader link
        glLinkProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glValidateProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success); BOATX_CHECK_GL_ERROR;
        if (success != GL_TRUE)
        {
            glGetProgramInfoLog(mShaderProgram, logSize, nullptr, infoLog); BOATX_CHECK_GL_ERROR;
            BOATX_ERROR("Shader linking error: {}", infoLog);
            glDeleteProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
            mShaderProgram = 0;
        }

        BOATX_ASSERT(success == GL_TRUE, "Error linking shader");

        glDeleteShader(vertexShader); BOATX_CHECK_GL_ERROR;
        glDeleteShader(fragmentShader); BOATX_CHECK_GL_ERROR;
    }

    void Shader::InitFromFile(const std::string& vsPath, const std::string& psPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vsPath);
            std::stringstream vShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            vShaderFile.close();
            vertexCode = vShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            BOATX_ERROR("shader source file {} read fail", vsPath);
            return;
        }

        try
        {
            fShaderFile.open(psPath);
            std::stringstream fShaderStream;
            fShaderStream << fShaderFile.rdbuf();
            fShaderFile.close();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            BOATX_ERROR("shader source file {} read fail", psPath);
            return;
        }

        InitFromString(vertexCode, fragmentCode);
    }

    Shader::~Shader()
    {
        glUseProgram(0); BOATX_CHECK_GL_ERROR;
        glDeleteProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
    }

    void Shader::Bind()
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
    }

    void Shader::Unbind()
    {
        glUseProgram(0); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformInt(const std::string& name, int val)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniform1i(GetUniformLocation(name), val); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformUnsignedInt(const std::string& name, unsigned val)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniform1ui(GetUniformLocation(name), val); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformFloat(const std::string& name, float val)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniform1f(GetUniformLocation(name), val); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformFloat2(const std::string& name, float val1, float val2)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniform2f(GetUniformLocation(name), val1, val2); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformFloat3(const std::string& name, float val1, float val2, float val3)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniform3f(GetUniformLocation(name), val1, val2, val3); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniform4f(GetUniformLocation(name), val1, val2, val3, val4); BOATX_CHECK_GL_ERROR;
    }

    void Shader::SetUniformMatrix4(const std::string& name, const glm::mat4& mat)
    {
        glUseProgram(mShaderProgram); BOATX_CHECK_GL_ERROR;
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)); BOATX_CHECK_GL_ERROR;
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        auto it = mUniformLocations.find(name);
        if (it == mUniformLocations.end())
        {
            mUniformLocations[name] = glGetUniformLocation(mShaderProgram, name.c_str()); BOATX_CHECK_GL_ERROR;
        }
        return mUniformLocations[name];
    }
}
