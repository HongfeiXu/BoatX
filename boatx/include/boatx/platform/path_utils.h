#pragma once

#include <string>

namespace boatx::platform
{
    class PathUtils
    {
    public:
        static std::string GetFilePureName(const std::string& fileFullName);
        static std::string PathJoin(const std::initializer_list<std::string>& filePaths);
    };
}
