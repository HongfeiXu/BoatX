#pragma once

#include <string>

namespace boatx::managers
{
    class PathManager {
    public:
        PathManager() = default;
        ~PathManager() = default;

        void Initialize(const std::string& binFilePath);
        void ShutDown() {}

        inline std::string GetBinFilePath() const{ return mBinFilePath; }
        std::string GetLogFolderPath() const;

    private:
        std::string mBinFilePath;
    };
}