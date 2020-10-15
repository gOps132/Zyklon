#include "Zyklon/zyklon_pch.h"

#include "Log.h"

namespace Zyklon {
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::init(const std::string &logging_name) {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("ZYKLON");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt(logging_name);
    s_ClientLogger->set_level(spdlog::level::trace);
}
} // namespace Zyklon