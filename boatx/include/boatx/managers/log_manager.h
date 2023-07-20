#pragma once

#include <string>

namespace boatx::managers
{
    /************************************************************************/
    /* Handles spdlog setup                                                 */
    /************************************************************************/
    class LogManager 
    {
    public:
        LogManager() = default;
        ~LogManager() = default;

        void Initialize(const std::string& logFolderPath);
        void ShutDown();
    };
}

