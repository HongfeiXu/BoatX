#include "boatx/managers/path_manager.h"
#include "boatx/platform/path_utils.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace boatx::managers
{

    void PathManager::Initialize(const std::string& binFilePath)
    {
        mBinFilePath = binFilePath;
    }

    std::string PathManager::GetLogFolderPath() const
    {
        fs::path temp(mBinFilePath);
        return platform::PathUtils::PathJoin({ temp.parent_path().string(), "logs" });
    }

    std::string PathManager::GetShaderFolderPath() const
    {
        fs::path temp(mBinFilePath);
        return platform::PathUtils::PathJoin({ temp.parent_path().string(), "resource", "shader"});
    }

    std::string PathManager::GetShaderPath(const std::string& shaderRelativePath) const
    {
        fs::path temp(mBinFilePath);
        return platform::PathUtils::PathJoin({ temp.parent_path().string(), "resource", "shader", shaderRelativePath });
    }

    std::string PathManager::GetFontPath(const std::string& fontRelativePath) const
    {
        fs::path temp(mBinFilePath);
        return platform::PathUtils::PathJoin({ temp.parent_path().string(), "resource", "fonts", fontRelativePath });
    }

}

