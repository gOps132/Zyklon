#ifndef __OPENGLVERTEXBUFFER_H__
#define __OPENGLVERTEXBUFFER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Buffer.h"

#include <glad/glad.h>

namespace Zyklon {

// Temporary helper function 
GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(float *vertices, size_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetLayout(BufferLayout& layout) override;
    virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; }

  private:
    uint32_t m_RendererID;
    BufferLayout m_BufferLayout;
};

class OpenGLIndexBuffer : public IndexBuffer {
  public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t size);
    virtual ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
    inline virtual uint32_t GetCount() const override;

  private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};
} // namespace Zyklon

#endif // __OPENGLVERTEXBUFFER_H__