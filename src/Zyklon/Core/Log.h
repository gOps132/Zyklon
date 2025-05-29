#ifndef __LOG_H__
#define __LOG_H__

/*
 * Logging system for Zyklon that is a wrapper for spd logger
 *
 * Don't run this from distribution builds*
 */

#include <Zyklon/zyklon_exports.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Zyklon {
class ZYKLON_EXPORT Log {
public:
	static void init(const std::string &p_logging_name);

	inline static std::shared_ptr<spdlog::logger> &getCoreLogger()
	{
		return s_core_logger;
	}
	inline static std::shared_ptr<spdlog::logger> &getClientLogger()
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
	::Zyklon::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ZYKLON_CORE_INFO(...)                                                  \
	::Zyklon::Log::getCoreLogger()->info(__VA_ARGS__)
#define ZYKLON_CORE_WARN(...)                                                  \
	::Zyklon::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ZYKLON_CORE_ERROR(...)                                                 \
	::Zyklon::Log::getCoreLogger()->error(__VA_ARGS__)
#define ZYKLON_CORE_CRITICAL(...)                                              \
	::Zyklon::Log::getCoreLogger()->critical(__VA_ARGS__)

#define ZYKLON_TRACE(...) ::Zyklon::Log::getClientLogger()->trace(__VA_ARGS__)
#define ZYKLON_INFO(...) ::Zyklon::Log::getClientLogger()->info(__VA_ARGS__)
#define ZYKLON_WARN(...) ::Zyklon::Log::getClientLogger()->warn(__VA_ARGS__)
#define ZYKLON_ERROR(...) ::Zyklon::Log::getClientLogger()->error(__VA_ARGS__)
#define ZYKLON_CRITICAL(...)                                                   \
	::Zyklon::Log::getClientLogger()->critical(__VA_ARGS__)

#endif // __LOG_H__