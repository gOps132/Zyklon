#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

namespace Zyklon {

enum class ShaderDataType : uint8_t {
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

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type) {
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
    BufferElement(ShaderDataType type, const std::string &name)
        : m_name(name), m_type(ShaderDataTypeSize(type)), m_offset(0), m_size(0)
    {
    }

    std::string m_name;
    ShaderDataType m_type;
    uint32_t m_offset;
    uint32_t m_size;
};

class BufferLayout {
  public:
    BufferLayout(const std::initializer_list<BufferElement> &element)
        : m_BufferElements(element)
    {
    }

    inline const std::vector<BufferElement> &getBufferElements() const
    {
        return m_BufferElements;
    }

	void CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for(auto& element : m_BufferElements)
		{
			element.m_offset = offset;
			offset += element.m_size;
			m_Stride = element.m_size;
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