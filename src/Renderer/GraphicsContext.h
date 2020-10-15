#ifndef __GRAPHICSCONTEXT_H__
#define __GRAPHICSCONTEXT_H__

#include <GLFW/glfw3.h>

namespace Zyklon
{
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static GraphicsContext* Create(GLFWwindow* window);
    };

} // namespace Zyklon

#endif // __GRAPHICSCONTEXT_H__