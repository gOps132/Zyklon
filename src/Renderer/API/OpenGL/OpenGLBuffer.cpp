#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include "OpenGLBuffer.h"
#include "OpenGLErrorManager.h"

namespace Zyklon {

GLenum OpenGLHelperFunc::ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {   
        case ShaderDataType::Float:     return GL_FLOAT;
        case ShaderDataType::Float2:    return GL_FLOAT;
        case ShaderDataType::Float3:    return GL_FLOAT;
        case ShaderDataType::Float4:    return GL_FLOAT;
        case ShaderDataType::Mat3:      return GL_FLOAT;
        case ShaderDataType::Mat4:      return GL_FLOAT;
        case ShaderDataType::Int:       return GL_INT;
        case ShaderDataType::Int2:      return GL_INT;
        case ShaderDataType::Int3:      return GL_INT;
        case ShaderDataType::Int4:      return GL_INT;
        case ShaderDataType::Bool:      return GL_BOOL; 
    } 

    ZYKLON_CORE_ASSERT(false, "Unkown Shader type");
    return 0;
}

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

void OpenGLVertexBuffer::SetLayout(BufferLayout &layout)
{
    uint32_t index = 0;
    for (const auto &element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index, element.GetComponentCount(),
            OpenGLHelperFunc::ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
            element.Size, (const void *)element.Offset);
        index++;
    }
}

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
