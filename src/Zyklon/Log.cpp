#include "Zyklon/zyklon_pch.h"

#include "Log.h"

namespace Zyklon {
std::shared_ptr<spdlog::logger> Log::s_core_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::init(const std::string &logging_name)
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_core_logger = spdlog::stdout_color_mt("ZYKLON");
    s_core_logger->set_level(spdlog::level::trace);

    s_client_logger = spdlog::stdout_color_mt(logging_name);
    s_client_logger->set_level(spdlog::level::trace);
}
} // namespace Zyklon