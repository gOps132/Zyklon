#ifndef __ERRORMANAGER_H__
#define __ERRORMANAGER_H__

#include <Zyklon/Core/zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#ifndef DEBUG
#define GLCall(x)                                                              \
    GLClearError();                                                            \
    x;                                                                         \
    ZYKLON_CORE_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "GLCALL FAILED!");
#else
#define GLCall(x) x
#endif

void GLClearError();

int GLLogCall(const char *p_function, const char *p_file, int p_line);

#endif // __ERRORMANAGER_H__
