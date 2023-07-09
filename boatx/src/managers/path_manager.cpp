#include "managers/path_manager.h"
#include "platform/path_utils.h"

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
        auto logFolderPath = platform::PathUtils::PathJoin({ temp.parent_path().string(), "logs" });
        return logFolderPath;
    }
}

