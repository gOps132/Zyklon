
#ifndef ZYKLON_EXPORT_H
#define ZYKLON_EXPORT_H

#ifdef ZYKLON_STATIC_DEFINE
#  define ZYKLON_EXPORT
#  define ZYKLON_NO_EXPORT
#else
#  ifndef ZYKLON_EXPORT
#    ifdef Zyklon_EXPORTS
        /* We are building this library */
#      define ZYKLON_EXPORT 
#    else
        /* We are using this library */
#      define ZYKLON_EXPORT 
#    endif
#  endif

#  ifndef ZYKLON_NO_EXPORT
#    define ZYKLON_NO_EXPORT 
#  endif
#endif

#ifndef ZYKLON_DEPRECATED
#  define ZYKLON_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ZYKLON_DEPRECATED_EXPORT
#  define ZYKLON_DEPRECATED_EXPORT ZYKLON_EXPORT ZYKLON_DEPRECATED
#endif

#ifndef ZYKLON_DEPRECATED_NO_EXPORT
#  define ZYKLON_DEPRECATED_NO_EXPORT ZYKLON_NO_EXPORT ZYKLON_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ZYKLON_NO_DEPRECATED
#    define ZYKLON_NO_DEPRECATED
#  endif
#endif

#endif /* ZYKLON_EXPORT_H */
