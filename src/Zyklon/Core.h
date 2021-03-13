#ifndef __CORE_H__
#define __CORE_H__

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

#ifdef ZYKLON_ENABLE_OPENGL
#define ZYKLON_OPENGL_FINAL final
#endif

#endif // __CORE_H__