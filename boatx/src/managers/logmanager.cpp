#include "managers/logmanager.h"

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <memory>


namespace boatx::managers
{
    void LogManager::Initialize()
    {        
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        // pattern format check pattern_formatter-inl.h
        consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%l] %v%$");

        // output log to current running project dir, change to bin dir by hardcode
        // maybe a more flexable way?
        auto fileSink= std::make_shared<spdlog::sinks::basic_file_sink_mt>("../bin/logs/multisink.txt", true);
        fileSink->set_level(spdlog::level::trace);
        fileSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%l] %v%$");


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
