#ifndef __ERRORMANAGER_H__
#define __ERRORMANAGER_H__

#include "Zyklon/Core.h"

#include "Zyklon/zyklon_pch.h"

/*
 * FIXME: Deal with bug that breakpoints even if assertion is okay
 */

#ifndef DEBUG
#define GLCall(x)                                                              \
    GLClearError();                                                            \
    x;                                                                         \
    ZYKLON_CORE_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "GLCALL FAILED!");
#else
#define GLCall(x) x
#endif

void GLClearError();

int GLLogCall(const char *function, const char *file, int line);

#endif // __ERRORMANAGER_H__
