#ifndef __OPENGLCONTEXT_H__
#define __OPENGLCONTEXT_H__

#include "Renderer/GraphicsContext.h"

class GLFWwindow;

namespace Zyklon
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* glfwWindow);

        virtual void Init() override;
        virtual void SwapBuffers() override;   

    private:
        GLFWwindow* m_WindowHandler;
    };

} // namespace Zyklon
    
#endif // __OPENGLCONTEXT_H__