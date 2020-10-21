#ifndef __OPENGLINDEXBUFFER_H__
#define __OPENGLINDEXBUFFER_H__

#include "Renderer/IndexBuffer.h"

namespace Zyklon {
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

#endif // __OPENGLINDEXBUFFER_H__