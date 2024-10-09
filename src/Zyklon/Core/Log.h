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

namespace Zyklon {
class ZYKLON_EXPORT Log {
public:
	static void init(const std::string &p_logging_name);

	inline static std::shared_ptr<spdlog::logger> &get_core_logger()
	{
		return s_core_logger;
	}
	inline static std::shared_ptr<spdlog::logger> &get_client_logger()
	{
		return s_client_logger;
	}

private:
	static std::shared_ptr<spdlog::logger> s_core_logger;
	static std::shared_ptr<spdlog::logger> s_client_logger;
};

} // namespace Zyklon

/* Strip these from distribution builds */
#define ZYKLON_CORE_TRACE(...)                                                 \
	::Zyklon::Log::get_core_logger()->trace(__VA_ARGS__)
#define ZYKLON_CORE_INFO(...)                                                  \
	::Zyklon::Log::get_core_logger()->info(__VA_ARGS__)
#define ZYKLON_CORE_WARN(...)                                                  \
	::Zyklon::Log::get_core_logger()->warn(__VA_ARGS__)
#define ZYKLON_CORE_ERROR(...)                                                 \
	::Zyklon::Log::get_core_logger()->error(__VA_ARGS__)
#define ZYKLON_CORE_CRITICAL(...)                                              \
	::Zyklon::Log::get_core_logger()->critical(__VA_ARGS__)

#define ZYKLON_TRACE(...) ::Zyklon::Log::get_client_logger()->trace(__VA_ARGS__)
#define ZYKLON_INFO(...) ::Zyklon::Log::get_client_logger()->info(__VA_ARGS__)
#define ZYKLON_WARN(...) ::Zyklon::Log::get_client_logger()->warn(__VA_ARGS__)
#define ZYKLON_ERROR(...) ::Zyklon::Log::get_client_logger()->error(__VA_ARGS__)
#define ZYKLON_CRITICAL(...)                                                   \
	::Zyklon::Log::get_client_logger()->critical(__VA_ARGS__)

#endif // __LOG_H__