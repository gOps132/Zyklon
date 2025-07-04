#include <zyklon_pch.h>

#include "RendererAPI.h"
#include "Renderer.h"
#include "GraphicsContext.h"

#include <Platform/OpenGL/OpenGLContext.h>

namespace Zyklon {
GraphicsContext *GraphicsContext::create(GLFWwindow *p_window)
{
	switch (Renderer::getAPI()) {
	case RendererAPI::API::None:
		ZYKLON_CORE_ASSERT(false, "No Graphics Context Available ");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return new OpenGLContext(p_window);
	}

	ZYKLON_CORE_ASSERT(false, "No Graphics Context Available");
	return nullptr;
}
} // namespace Zyklon
