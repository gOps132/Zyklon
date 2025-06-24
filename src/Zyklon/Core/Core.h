#ifndef __CORE_H__
#define __CORE_H__

#include <zyklon_pch.h>

#ifdef zyklon_ENABLE_ASSERTS
#define ZYKLON_ASSERT(x, ...)                                                  \
	{                                                                          \
		if (!(x)) {                                                            \
			ZYKLON_ERROR("Assertion Failed: {0}", __VA_ARGS__);                \
			debug_break();                                                     \
		}                                                                      \
	}
#define ZYKLON_CORE_ASSERT(x, ...)                                             \
	{                                                                          \
		if (!(x)) {                                                            \
			ZYKLON_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);           \
			debug_break();                                                     \
		}                                                                      \
	}
#else
#define ZYKLON_ASSERT(x, ...)
#define ZYKLON_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Zyklon 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ...Args>
	constexpr Scope<T> createScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ...Args>
	constexpr Ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#ifdef ZYKLON_ENABLE_OPENGL
#define ZYKLON_OPENGL_FINAL final
#endif

#endif // __CORE_H__