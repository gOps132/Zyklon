#include <zyklon_pch.h>

#include <Zyklon/zyklon_exports.h>
#include <Zyklon/Core/Core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLContext.h"

namespace Zyklon {
OpenGLContext::OpenGLContext(GLFWwindow *p_glfw_window)
	: m_window_handler(p_glfw_window)
{
	ZYKLON_CORE_ASSERT(m_window_handler, "m_window_handler is null");
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(m_window_handler);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ZYKLON_CORE_ASSERT(status, "failed to initialize glad");

	ZYKLON_CORE_WARN("OPENGL INFO:");
	ZYKLON_CORE_WARN("  VENDOR: {0}", glGetString(GL_VENDOR));
	ZYKLON_CORE_WARN("  RENDERER: {0}", glGetString(GL_RENDERER));
	ZYKLON_CORE_WARN("  VERSION: {0}", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
}

void OpenGLContext::swapBuffers() { glfwSwapBuffers(m_window_handler); }

} // namespace Zyklon