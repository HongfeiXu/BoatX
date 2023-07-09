#pragma once

#include <string>

namespace boatx::managers
{
    class LogManager {
    public:
        LogManager() = default;
        ~LogManager() = default;

        void Initialize(const std::string& logFolderPath);
        void ShutDown();
    };
}

