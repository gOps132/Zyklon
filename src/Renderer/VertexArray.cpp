#include "Renderer.h"

#include "VertexArray.h"

#include "Renderer/API/OpenGL/OpenGLVertexArray.h"

namespace Zyklon {

VertexArray *VertexArray::create()
{
    switch (Renderer::get_api()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Vertex Array Available");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexArray();
    }

    ZYKLON_CORE_ASSERT(false, "No Vertex Array Available");
    return nullptr;
}

} // namespace Zyklon
