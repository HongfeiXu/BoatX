#pragma once

#include "spdlog/spdlog.h"


#define BOATX_DEFAULT_LOGGER_NAME "boatxlogger"

#if defined(BOATX_PLATFORM_WINDOWS)
#define BOATX_BREAK __debugbreak();
#elif defined(BOATX_PLATFORM_MAC)
#define BOATX_BREAK __builtin_debugtrap();
#else
#define BOATX_BREAK __builtin_trap();
#endif

#ifndef BOATX_CONFIG_RELEASE
#define BOATX_TRACE(...)        if(spdlog::get(BOATX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(BOATX_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#define BOATX_DEBUG(...)        if(spdlog::get(BOATX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(BOATX_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define BOATX_INFO(...)         if(spdlog::get(BOATX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(BOATX_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define BOATX_WARN(...)         if(spdlog::get(BOATX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(BOATX_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define BOATX_ERROR(...)        if(spdlog::get(BOATX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(BOATX_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define BOATX_FATAL(...)        if(spdlog::get(BOATX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(BOATX_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}
#define BOATX_ASSERT(x, msg)    if((x)) {} else {BOATX_FATAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); BOATX_BREAK}
#else
#define BOATX_TRACE(...)        (void)0
#define BOATX_DEBUG(...)        (void)0
#define BOATX_INFO(...)         (void)0
#define BOATX_WARN(...)         (void)0
#define BOATX_ERROR(...)        (void)0
#define BOATX_FATAL(...)        (void)0
#define BOATX_ASSERT(x, msg)    (void)0
#endif

