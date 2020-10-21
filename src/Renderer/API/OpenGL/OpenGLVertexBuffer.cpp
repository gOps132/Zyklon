#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include "OpenGLErrorManager.h"
#include "OpenGLVertexBuffer.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>

namespace Zyklon {
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, size_t size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void OpenGLVertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void OpenGLVertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

} // namespace Zyklon
