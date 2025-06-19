#ifndef __OPENGLCONTEXT_H__
#define __OPENGLCONTEXT_H__

#include <Zyklon/Core/Core.h>

#include <Renderer/GraphicsContext.h>

class GLFWwindow;
namespace Zyklon {
class OpenGLContext ZYKLON_OPENGL_FINAL : public GraphicsContext {
public:
	OpenGLContext(GLFWwindow *p_glfw_window);

	virtual void init() override;
	virtual void swapBuffers() override;

private:
	GLFWwindow *m_window_handler;
};

} // namespace Zyklon

#endif // __OPENGLCONTEXT_H__