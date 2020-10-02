#include "Zyklon/zyklon_pch.h"
#include <glad/glad.h>
#include "OpenGLVertexBuffer.h"

namespace Zyklon
{
    OpenGLVertexBuffer::~OpenGLVertexBuffer(float* vertices, size_t size) 
    {
        glCreateBuffers(1, &m_RendererID);

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    
    OpenGLVertexBuffer::OpenGLVertexBuffer() 
    {
        glDeleteBuffer(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    
    void OpenGLVertexBuffer::Unbind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
} // namespace Zyklon
