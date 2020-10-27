#ifndef __OPENGLVERTEXBUFFER_H__
#define __OPENGLVERTEXBUFFER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Buffer.h"

namespace Zyklon {
class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(float *vertices, size_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

  private:
    uint32_t m_RendererID;
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