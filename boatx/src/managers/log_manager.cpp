#include "boatx/managers/log_manager.h"

#include "boatx/log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "boatx/platform/path_utils.h"

#include <memory>
#include <filesystem>


namespace boatx::managers
{
    void LogManager::Initialize(const std::string& logFolderPath)
{        
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        // pattern format check pattern_formatter-inl.h
        consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%L] %v%$");

        // output log to file
        auto logFilePath = platform::PathUtils::PathJoin({ logFolderPath, "log.txt" });
        auto fileSink= std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, true);
        fileSink->set_level(spdlog::level::trace);
        fileSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%L] %v%$");


        std::vector<spdlog::sink_ptr> sinks{ consoleSink, fileSink };

        auto logger = std::make_shared<spdlog::logger>(BOATX_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(logger);
    }

    void LogManager::ShutDown()
    {
        spdlog::shutdown();
    }
}
