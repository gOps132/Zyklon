#include "Renderer.h"
#include "VertexArray.h"

#include "API/OpenGL/OpenGLVertexArray.h"

namespace Zyklon {

VertexArray *VertexArray::create()
{
	switch (Renderer::get_api()) {
	case RendererAPI::API::None:
		ZYKLON_CORE_ASSERT(false, "No Vertex Array Available");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return new OpenGLVertexArray();
	}

	ZYKLON_CORE_ASSERT(false, "No Vertex Array Available");
	return nullptr;
}

} // namespace Zyklon
