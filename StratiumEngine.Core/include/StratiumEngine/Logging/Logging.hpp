#pragma once

#include <iostream>
#include <string>
#include <format>

namespace Stratium {

    // ============================================================================
    // Logger Class - Basit Loglama Sistemi
    // ============================================================================

    class Logger {
    public:
        Logger() = default;
        ~Logger() = default;

        // Basit log metotları
        void Info(const std::string& message);
        void Warn(const std::string& message);
        void Error(const std::string& message);
        void Debug(const std::string& message);
    };

} // namespace Stratium

// ============================================================================
// Logging Macros - Loglama Makroları (C++23 std::format kullanıyor)
// ============================================================================

#ifdef STRATIUM_DEBUG
    #define STRATIUM_LOG_INFO(format, ...) \
        std::cout << "[INFO] " << std::format(format, ##__VA_ARGS__) << std::endl

    #define STRATIUM_LOG_WARN(format, ...) \
        std::cerr << "[WARN] " << std::format(format, ##__VA_ARGS__) << std::endl

    #define STRATIUM_LOG_ERROR(format, ...) \
        std::cerr << "[ERROR] " << std::format(format, ##__VA_ARGS__) << std::endl

    #define STRATIUM_LOG_DEBUG(format, ...) \
        std::cout << "[DEBUG] " << std::format(format, ##__VA_ARGS__) << std::endl

    #define STRATIUM_LOG_TRACE(format, ...) \
        std::cout << "[TRACE] " << std::format(format, ##__VA_ARGS__) << std::endl
#else
    #define STRATIUM_LOG_INFO(format, ...) ((void)0)
    #define STRATIUM_LOG_WARN(format, ...) ((void)0)
    #define STRATIUM_LOG_ERROR(format, ...) ((void)0)
    #define STRATIUM_LOG_DEBUG(format, ...) ((void)0)
    #define STRATIUM_LOG_TRACE(format, ...) ((void)0)
#endif
