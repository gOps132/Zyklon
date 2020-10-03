#include "Zyklon/zyklon_pch.h"

#include "Zyklon/zyklon_exports.h"
#include "Zyklon/Core.h"

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Zyklon
{
	OpenGLContext::OpenGLContext(GLFWwindow *window)
	    : m_WindowHandler(window)
	{
		ZYKLON_CORE_ASSERT(m_WindowHandler, "m_WindowHandler is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandler);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ZYKLON_CORE_ASSERT(status, "failed to initialize glad");

		ZYKLON_CORE_INFO("OpenGL Info:");
		ZYKLON_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		ZYKLON_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ZYKLON_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{	
		glfwSwapBuffers(m_WindowHandler);
	}

} // namespace Zyklon