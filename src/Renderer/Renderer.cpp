#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include "Renderer/API/OpenGL/OpenGLContext.h"
#include "Renderer/API/OpenGL/OpenGLIndexBuffer.h"
#include "Renderer/API/OpenGL/OpenGLShader.h"
#include "Renderer/API/OpenGL/OpenGLVertexBuffer.h"

#include "GraphicsContext.h"
#include "Renderer.h"

namespace Zyklon {
// hotswap interface this later
RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;

GraphicsContext *GraphicsContext::Create(GLFWwindow *window)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Graphics Context Available ");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLContext(window);
    }

    ZYKLON_CORE_ASSERT(false, "No Graphics Context Available");
    return nullptr;
}

VertexBuffer *VertexBuffer::Create(float *vertices, size_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Renderer API is supported. !");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    }
    ZYKLON_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Shader *Shader::Create(const std::string &vertexSource,
                       const std::string &fragmentSource)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Shader is supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLShader(vertexSource, fragmentSource);
    }
    ZYKLON_CORE_ASSERT(false, "Unknown Shader!");
    return nullptr;
}

IndexBuffer *IndexBuffer::Create(uint32_t *indices, size_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ZYKLON_CORE_ASSERT(false, "No Renderer API is supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
    }
    ZYKLON_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Zyklon
