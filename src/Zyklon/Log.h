#ifndef __LOG_H__
#define __LOG_H__

/* 
 * Logging system for Zyklon that is a wrapper for spd logger 
 * 
 * Don't run this from distribution builds*
 */

#include "zyklon_exports.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Zyklon
{
    class ZYKLON_EXPORT Log
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }
    };

} // namespace Zyklon

/* Strip these from distribution builds */

#define ZYKLON_CORE_TRACE(...)    ::Zyklon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZYKLON_CORE_INFO(...)     ::Zyklon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZYKLON_CORE_WARN(...)     ::Zyklon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZYKLON_CORE_ERROR(...)    ::Zyklon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZYKLON_CORE_CRITICAL(...) ::Zyklon::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ZYKLON_TRACE(...)         ::Zyklon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZYKLON_INFO(...)          ::Zyklon::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZYKLON_WARN(...)          ::Zyklon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZYKLON_ERROR(...)         ::Zyklon::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZYKLON_CRITICAL(...)      ::Zyklon::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif // __LOG_H__