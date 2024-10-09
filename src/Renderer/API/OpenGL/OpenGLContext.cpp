#include <zyklon_exports.h>
#include <Zyklon/Core/zyklon_pch.h>
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

	ZYKLON_CORE_INFO("OPENGL INFO:");
	ZYKLON_CORE_INFO("  VENDOR: {0}", glGetString(GL_VENDOR));
	ZYKLON_CORE_INFO("  RENDERER: {0}", glGetString(GL_RENDERER));
	ZYKLON_CORE_INFO("  VERSION: {0}", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
}

void OpenGLContext::swap_buffers() { glfwSwapBuffers(m_window_handler); }

} // namespace Zyklon