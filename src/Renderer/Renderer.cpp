#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include "Renderer/API/OpenGL/OpenGLBuffer.h"
#include "Renderer/API/OpenGL/OpenGLContext.h"
#include "Renderer/API/OpenGL/OpenGLShader.h"
#include "Renderer/API/OpenGL/OpenGLVertexArray.h"

#include "GraphicsContext.h"
#include "Renderer.h"

namespace Zyklon {

GraphicsContext *GraphicsContext::create(GLFWwindow *p_window)
{
    switch (Renderer::get_api()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Graphics Context Available ");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLContext(p_window);
    }

    ZYKLON_CORE_ASSERT(false, "No Graphics Context Available");
    return nullptr;
}

VertexBuffer *VertexBuffer::create(float *p_vertices, size_t p_size)
{
    switch (Renderer::get_api()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Renderer API is supported. !");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(p_vertices, p_size);
    }
    ZYKLON_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer *IndexBuffer::create(uint32_t *p_indices, size_t p_size)
{
    switch (Renderer::get_api()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Renderer API is supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(p_indices, p_size);
    }
    ZYKLON_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

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

Shader *Shader::create(const std::string &p_filepath)
{
    switch (Renderer::get_api()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Shader is supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLShader(p_filepath);
    }
    ZYKLON_CORE_ASSERT(false, "Unknown Shader!");
    return nullptr;
}

} // namespace Zyklon
