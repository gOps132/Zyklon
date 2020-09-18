#include "Zyklon/zyklon_pch.h"

#include "Zyklon/zyklon_exports.h"

#include "Zyklon/Platform/OpenGL/OpenGLContext.h"

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
	}

	void OpenGLContext::SwapBuffers()
	{	
		glfwSwapBuffers(m_WindowHandler);
	}     

} // namespace Zyklon