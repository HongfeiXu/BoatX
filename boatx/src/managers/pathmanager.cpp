#include "managers/pathmanager.h"
#include "platform/path.h"

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
        auto logFolderPath = platform::Path::PathJoin({ temp.parent_path().string(), "logs" });
        return logFolderPath;
    }
}

