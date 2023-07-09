#include "platform/path.h"
#include <filesystem>

namespace fs = std::filesystem;


namespace boatx::platform
{
    std::string Path::GetFilePureName(const std::string& fileFullName)
    {
        fs::path temp(fileFullName);
        return temp.stem().string();
    }

    std::string Path::PathJoin(const std::initializer_list<std::string>& filePaths)
    {
        fs::path temp;
        for (const auto filePath : filePaths)
        {
            temp = temp / filePath;
        }
        return temp.make_preferred().string();
    }
}

