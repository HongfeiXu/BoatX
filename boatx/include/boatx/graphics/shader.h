#pragma once

#include <string>
#include <cinttypes>
#include <unordered_map>

namespace boatx::graphics 
{
    /************************************************************************/
    /* Handles vs\ps setup, uniform setting                                 */
    /************************************************************************/
    class Shader
    {
    public:
        Shader(const std::string& vsSrc, const std::string& psSrc);
        ~Shader();

        void Bind();
        void Unbind();

        void SetUniformInt(const std::string& name, int val);
        void SetUniformUnsignedInt(const std::string& name, unsigned val);
        void SetUniformFloat(const std::string& name, float val);
        void SetUniformFloat2(const std::string& name, float val1, float val2);
        void SetUniformFloat3(const std::string& name, float val1, float val2, float val3);
        void SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4);

    private:
        int GetUniformLocation(const std::string& name);

    private:
        uint32_t mShaderProgram;

        std::unordered_map<std::string, int> mUniformLocations; // 缓存uniform location，减少每次都去获取的时间开销

    };
    

}