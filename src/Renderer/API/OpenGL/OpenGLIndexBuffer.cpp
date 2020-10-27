#include "Zyklon/zyklon_pch.h"

#include <glad/glad.h>

#include "Zyklon/Core.h"

#include "OpenGLBuffer.h"
#include "OpenGLErrorManager.h"

namespace Zyklon {

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
    : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t),
                        indices, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void OpenGLIndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void OpenGLIndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

uint32_t OpenGLIndexBuffer::GetCount() const { return m_Count; }

} // namespace Zyklon