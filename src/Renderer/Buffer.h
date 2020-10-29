#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Zyklon/zyklon_pch.h"
#include "Zyklon/Core.h"

#include <glad/glad.h>

namespace Zyklon {

enum class ShaderDataType : uint32_t {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool,
    Struct
};

static uint32_t ShaderDataTypeSize(ShaderDataType pType)
{
    switch (pType) 
    {
        case ShaderDataType::Float:     return 4;
        case ShaderDataType::Float2:    return 4 * 2;
        case ShaderDataType::Float3:    return 4 * 3;
        case ShaderDataType::Float4:    return 4 * 4;
        case ShaderDataType::Mat3:      return 4 * 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4 * 4;
        case ShaderDataType::Int:       return 4;
        case ShaderDataType::Int2:      return 4 * 2;
        case ShaderDataType::Int3:      return 4 * 3;
        case ShaderDataType::Int4:      return 4 * 4;
        case ShaderDataType::Bool:      return 1;
    }

    ZYKLON_CORE_ASSERT(false, "Unkown shader data Type");
    return 0;
}

// temporary helper function
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
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

struct BufferElement {
    std::string Name;
    ShaderDataType Type;
    uint32_t Offset;
    uint32_t Size;

    BufferElement(ShaderDataType pType, const std::string &pName)
        : Name(pName), Type(pType), Offset(0), Size(0)
    {
    }

    uint32_t GetComponentCount() const
    {
        switch (Type) 
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;

            case ShaderDataType::Bool:      return 1;
        }

        ZYKLON_CORE_ASSERT(false, "Unkown Shader type");
        return 0;
    }
};

class BufferLayout {
  public:
    BufferLayout(const std::initializer_list<BufferElement> &element)
        : m_BufferElements(element)
    {
        calculateOffsetsAndStrides();
    }

    inline const std::vector<BufferElement> &getBufferElements() const
    {
        return m_BufferElements;
    }

    void calculateOffsetsAndStrides()
    {
        uint32_t l_offset = 0;
        m_Stride = 0;
        for (auto &element : m_BufferElements) {
            element.Offset = l_offset;
            l_offset += element.Size;
            m_Stride += element.Size;
        }
    }

    std::vector<BufferElement>::iterator begin()
    {
        return m_BufferElements.begin();
    }
    std::vector<BufferElement>::iterator end()
    {
        return m_BufferElements.end();
    }

  private:
    std::vector<BufferElement> m_BufferElements;
    uint32_t m_Stride;
};

class VertexBuffer {
  public:
    virtual ~VertexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetLayout(const BufferLayout &layout) = 0;
    virtual const BufferLayout &GetLayout() const = 0;

    static VertexBuffer *Create(float *vertices, size_t size);
};

class IndexBuffer {
  public:
    virtual ~IndexBuffer(){};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    inline virtual uint32_t GetCount() const = 0;

    static IndexBuffer *Create(uint32_t *indices, size_t size);
};

} // namespace Zyklon

#endif // __BUFFER_H__