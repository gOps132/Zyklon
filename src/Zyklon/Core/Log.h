#ifndef __LOG_H__
#define __LOG_H__

/*
 * Logging system for Zyklon that is a wrapper for spd logger
 *
 * Don't run this from distribution builds*
 */

#include <zyklon_pch.h>
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
#ifdef _WIN32
#define ZYKLON_FILE_NAME                                                       \
	(strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define ZYKLON_FILE_NAME                                                       \
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

// We are now explicitly including file/line in the message format.
// The `fmt::format` around `__VA_ARGS__` ensures that the user's
// format string and arguments are processed into a single string
// before being combined with our file/line prefix.
#define ZYKLON_CORE_TRACE(...)                                                 \
	::Zyklon::Log::getCoreLogger()->trace("[{}:{}] {}", ZYKLON_FILE_NAME,      \
										  __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_CORE_INFO(...)                                                  \
	::Zyklon::Log::getCoreLogger()->info("[{}:{}] {}", ZYKLON_FILE_NAME,       \
										 __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_CORE_WARN(...)                                                  \
	::Zyklon::Log::getCoreLogger()->warn("[{}:{}] {}", ZYKLON_FILE_NAME,       \
										 __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_CORE_ERROR(...)                                                 \
	::Zyklon::Log::getCoreLogger()->error("[{}:{}] {}", ZYKLON_FILE_NAME,      \
										  __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_CORE_CRITICAL(...)                                              \
	::Zyklon::Log::getCoreLogger()->critical(                                  \
		"[{}:{}] {}", ZYKLON_FILE_NAME, __LINE__, fmt::format(__VA_ARGS__))

#define ZYKLON_TRACE(...)                                                      \
	::Zyklon::Log::getClientLogger()->trace(                                   \
		"[{}:{}] {}", ZYKLON_FILE_NAME, __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_INFO(...)                                                       \
	::Zyklon::Log::getClientLogger()->info("[{}:{}] {}", ZYKLON_FILE_NAME,     \
										   __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_WARN(...)                                                       \
	::Zyklon::Log::getClientLogger()->warn("[{}:{}] {}", ZYKLON_FILE_NAME,     \
										   __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_ERROR(...)                                                      \
	::Zyklon::Log::getClientLogger()->error(                                   \
		"[{}:{}] {}", ZYKLON_FILE_NAME, __LINE__, fmt::format(__VA_ARGS__))
#define ZYKLON_CRITICAL(...)                                                   \
	::Zyklon::Log::getClientLogger()->critical(                                \
		"[{}:{}] {}", ZYKLON_FILE_NAME, __LINE__, fmt::format(__VA_ARGS__))

#endif // __LOG_H__