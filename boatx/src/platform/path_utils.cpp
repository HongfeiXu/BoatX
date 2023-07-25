#include "boatx/platform/path_utils.h"
#include <filesystem>

namespace fs = std::filesystem;


namespace boatx::platform
{
    std::string PathUtils::GetFilePureName(const std::string& fileFullName)
    {
        fs::path temp(fileFullName);
        return temp.stem().string();
    }

    std::string PathUtils::PathJoin(const std::initializer_list<std::string>& filePaths)
    {
        fs::path temp;
        for (const auto filePath : filePaths)
        {
            temp = temp / filePath;
        }
        return temp.make_preferred().string();
    }
}

