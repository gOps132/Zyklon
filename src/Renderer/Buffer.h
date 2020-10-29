#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Zyklon/zyklon_pch.h"
#include "Zyklon/Core.h"

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

static uint32_t ShaderDataTypeSize(ShaderDataType pType);

struct BufferElement {
    std::string Name;
    ShaderDataType Type;
    uint32_t Offset;
    uint32_t Size;

    BufferElement(ShaderDataType pType, const std::string &pName);
    
    uint32_t GetComponentCount() const;
};

class BufferLayout {
  public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement> &element);

    inline const std::vector<BufferElement> &getBufferElements() const { return m_BufferElements; }

    void calculateOffsetsAndStrides();

    std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }

  private:
    std::vector<BufferElement> m_BufferElements;
    uint32_t m_Stride;
};
class VertexBuffer {
  public:
    virtual ~VertexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetLayout(BufferLayout &layout) = 0;
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