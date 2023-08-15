#pragma once

#include <string>
#include <cinttypes>
#include <unordered_map>
#include "external/glm/glm.hpp"
#include "external/glm/gtc/type_ptr.hpp"

namespace boatx::graphics 
{
    /************************************************************************/
    /* Handles vs\ps setup, uniform setting                                 */
    /************************************************************************/
    class Shader
    {
    public:
        Shader();
        ~Shader();

        void InitFromString(const std::string& vsSrc, const std::string& psSrc);
        void InitFromFile(const std::string& vsPath, const std::string& psPath);


        void Bind();
        void Unbind();

        void SetUniformInt(const std::string& name, int val);
        void SetUniformUnsignedInt(const std::string& name, unsigned val);
        void SetUniformFloat(const std::string& name, float val);
        void SetUniformFloat2(const std::string& name, float val1, float val2);
        void SetUniformFloat3(const std::string& name, float val1, float val2, float val3);
        void SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4);
		void SetUniformMatrix4(const std::string& name, const glm::mat4& mat);

    private:
        int GetUniformLocation(const std::string& name);
    private:
        uint32_t mShaderProgram;

        std::unordered_map<std::string, int> mUniformLocations; // 缓存uniform location，减少每次都去获取的时间开销

    };
    

}