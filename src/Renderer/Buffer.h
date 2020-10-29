#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

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
    switch (pType) {

    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
        case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    }

    ZYKLON_CORE_ASSERT(false, "Unkown shader data type");
    return 0;
}

struct BufferElement {
    BufferElement(ShaderDataType pType, const std::string &pName)
        : m_Name(pName), m_Type(ShaderDataTypeSize(pType)), m_Offset(0),
          m_Size(0)
    {
    }

    std::string m_Name;
    uint32_t m_Type;
    uint32_t m_Offset;
    uint32_t m_Size;
};

class BufferLayout {
  public:
    BufferLayout(const std::initializer_list<BufferElement> &element)
        : m_BufferElements(element)
    {
        calculate_offsets_and_stride();
    }

    inline const std::vector<BufferElement> &getBufferElements() const
    {
        return m_BufferElements;
    }

    void calculate_offsets_and_stride()
    {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto &element : m_BufferElements) {
            element.m_Offset = offset;
            offset += element.m_Size;
            m_Stride += element.m_Size;
        }
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