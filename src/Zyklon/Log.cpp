#include "Zyklon/zyklon_pch.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Zyklon
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

// set pattern may cause segementation fault in multithreaded program
// https://github.com/gabime/spdlog/issues/419
// Aug 6 11:43 segmentation fault due to spd log, this init function may be the cause.
    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("ZYKLON");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_CoreLogger = spdlog::stdout_color_mt("APP");
        s_CoreLogger->set_level(spdlog::level::trace);
    }
}