#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon {

enum class ShaderDataType : uint8_t {

};

struct BufferElements {
    BufferElements(const std::string& name, ShaderDataType type)
        : m_name(name), m_type(type), m_offset(0), m_size(0);

    std::string m_name;
    ShaderDataType m_type;
    uint32_t m_offset;
    uint32_t m_size;

};

class BufferLayout {
  public:
    inline const std::vector<BufferElements> &getBufferElements() const
    {
        return m_BufferElements;
    }

  private:
    std::vector<BufferElements> m_BufferElements;
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