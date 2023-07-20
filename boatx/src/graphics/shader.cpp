#include "graphics/shader.h"
#include "log.h"
#include "glad/glad.h"

namespace boatx::graphics
{
    Shader::Shader(const std::string& vsSrc, const std::string& psSrc)
    {
        mShaderProgram = glCreateProgram();

        GLint success = GL_FALSE;
        const GLsizei logSize = 512;
        char infoLog[logSize];
        
        // shader create and attach
        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        {
            const GLchar* glSource = vsSrc.c_str();
            glShaderSource(vertexShader, 1, &glSource, nullptr);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (success != GL_TRUE)
            {
                glGetShaderInfoLog(vertexShader, logSize, nullptr, infoLog);
                BOATX_ERROR("Vertex Shader compilation error: {}", infoLog);
            }
            else
            {
                glAttachShader(mShaderProgram, vertexShader);
            }
        }

        uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        if(success == GL_TRUE)
        {
            const GLchar* glSource = psSrc.c_str();
            glShaderSource(fragmentShader, 1, &glSource, nullptr);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (success != GL_TRUE)
            {
                glGetShaderInfoLog(fragmentShader, logSize, nullptr, infoLog);
                BOATX_ERROR("Fragment Shader compilation error: {}", infoLog);
            }
            else
            {
                glAttachShader(mShaderProgram, fragmentShader);
            }
        }

        BOATX_ASSERT(success == GL_TRUE, "Error compiling shader");

        // shader link
        glLinkProgram(mShaderProgram);
        glValidateProgram(mShaderProgram);
        glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
        if (success != GL_TRUE)
        {
            glGetProgramInfoLog(mShaderProgram, logSize, nullptr, infoLog);
            BOATX_ERROR("Shader linking error: {}", infoLog);
            glDeleteProgram(mShaderProgram);
            mShaderProgram = 0;
        }

        BOATX_ASSERT(success == GL_TRUE, "Error linking shader");

        // Need detatch shader before delete?
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glUseProgram(0);
        glDeleteProgram(mShaderProgram);
    }

    void Shader::Bind()
    {
        glUseProgram(mShaderProgram);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    void Shader::SetUniformInt(const std::string& name, int val)
    {
        glUseProgram(mShaderProgram);
        glUniform1i(GetUniformLocation(name), val);
    }

    void Shader::SetUniformUnsignedInt(const std::string& name, unsigned val)
    {
        glUseProgram(mShaderProgram);
        glUniform1ui(GetUniformLocation(name), val);
    }

    void Shader::SetUniformFloat(const std::string& name, float val)
    {
        glUseProgram(mShaderProgram);
        glUniform1f(GetUniformLocation(name), val);
    }

    void Shader::SetUniformFloat2(const std::string& name, float val1, float val2)
    {
        glUseProgram(mShaderProgram);
        glUniform2f(GetUniformLocation(name), val1, val2);
    }

    void Shader::SetUniformFloat3(const std::string& name, float val1, float val2, float val3)
    {
        glUseProgram(mShaderProgram);
        glUniform3f(GetUniformLocation(name), val1, val2, val3);
    }

    void Shader::SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4)
    {
        glUseProgram(mShaderProgram);
        glUniform4f(GetUniformLocation(name), val1, val2, val3, val4);
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        auto it = mUniformLocations.find(name);
        if (it == mUniformLocations.end())
        {
            mUniformLocations[name] = glGetUniformLocation(mShaderProgram, name.c_str());
        }
        return mUniformLocations[name];
    }
}
