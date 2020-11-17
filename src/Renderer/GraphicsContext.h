#ifndef __GRAPHICSCONTEXT_H__
#define __GRAPHICSCONTEXT_H__

#include <GLFW/glfw3.h>

namespace Zyklon {
class GraphicsContext {
  public:
    virtual void init() = 0;
    virtual void swap_buffers() = 0;

    static GraphicsContext *create(GLFWwindow *p_window);
};

} // namespace Zyklon

#endif // __GRAPHICSCONTEXT_H__