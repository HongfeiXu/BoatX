#pragma once


namespace boatx::managers
{
    class LogManager {
    public:
        LogManager() = default;
        ~LogManager() = default;

        void Initialize();
        void ShutDown();
    };
}

