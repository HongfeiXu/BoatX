#pragma once

#include <string>

namespace boatx::managers
{
    class PathManager 
    {
    public:
        PathManager() = default;
        ~PathManager() = default;

        void Initialize(const std::string& binFilePath);
        void ShutDown();

        inline std::string GetBinFilePath() const{ return mBinFilePath; }
        std::string GetLogFolderPath() const;
        std::string GetShaderFolderPath() const;
        std::string GetShaderPath(const std::string& shaderRelativePath) const;
        std::string GetFontPath(const std::string& fontRelativePath) const;

    private:
        std::string mBinFilePath;
    };
}