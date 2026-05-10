#include "StratiumEngine/Logging/Logging.hpp"

namespace Stratium {

    void Logger::Info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }

    void Logger::Warn(const std::string& message) {
        std::cerr << "[WARN] " << message << std::endl;
    }

    void Logger::Error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }

    void Logger::Debug(const std::string& message) {
#ifdef STRATIUM_DEBUG
        std::cout << "[DEBUG] " << message << std::endl;
#endif
    }

} // namespace Stratium
