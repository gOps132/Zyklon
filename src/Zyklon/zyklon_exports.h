
#ifndef ZYKLON_EXPORT_H
#define ZYKLON_EXPORT_H

#ifdef ZYKLON_STATIC_DEFINE
#define ZYKLON_EXPORT
#define ZYKLON_NO_EXPORT
#else
#ifndef ZYKLON_EXPORT
#ifdef Zyklon_EXPORTS // This is defined when building the library
// For Windows (MSVC, MinGW/GCC)
#ifdef _WIN32
#define ZYKLON_EXPORT __declspec(dllexport)
// For Unix-like systems (Linux, macOS) using GCC/Clang
#elif __GNUC__ >= 4 // Or just __GNUC__ if you're targeting recent GCC/Clang
#define ZYKLON_EXPORT __attribute__((visibility("default")))
#else
// Fallback for other compilers, might default to exporting all
#define ZYKLON_EXPORT
#endif
#else // This is defined when using the library (client application)
// For Windows (MSVC, MinGW/GCC)
#ifdef _WIN32
#define ZYKLON_EXPORT __declspec(dllimport)
// For Unix-like systems (Linux, macOS) using GCC/Clang
#elif __GNUC__ >= 4
// On Unix-like systems, importing doesn't usually require a special keyword.
// Symbols are resolved by the linker.
#define ZYKLON_EXPORT
#else
// Fallback
#define ZYKLON_EXPORT
#endif
#endif // End of Zyklon_EXPORTS check
#endif // End of ZYKLON_EXPORT check

#ifndef ZYKLON_NO_EXPORT
// On Unix-like systems, typically hide by default and explicitly export.
// If -fvisibility=hidden is used, this ensures symbols remain hidden.
#ifdef __GNUC__ >= 4
#define ZYKLON_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define ZYKLON_NO_EXPORT
#endif
#endif
#endif

#ifndef ZYKLON_DEPRECATED
#define ZYKLON_DEPRECATED __attribute__((__deprecated__))
#endif

#ifndef ZYKLON_DEPRECATED_EXPORT
#define ZYKLON_DEPRECATED_EXPORT ZYKLON_EXPORT ZYKLON_DEPRECATED
#endif

#ifndef ZYKLON_DEPRECATED_NO_EXPORT
#define ZYKLON_DEPRECATED_NO_EXPORT ZYKLON_NO_EXPORT ZYKLON_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#ifndef ZYKLON_NO_DEPRECATED
#define ZYKLON_NO_DEPRECATED
#endif
#endif

#endif /* ZYKLON_EXPORT_H */
