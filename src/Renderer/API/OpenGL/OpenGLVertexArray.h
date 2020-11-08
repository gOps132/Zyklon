#ifndef __OPENGLVERTEXARRAY_H__
#define __OPENGLVERTEXARRAY_H__

#include "Renderer/VertexArray.h"

namespace Zyklon {
class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray() override;

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void
    AddVertexBuffer(const std::shared_ptr<VertexBuffer> p_vertex_bfr) override;
    virtual void
    AddIndexBuffer(const std::shared_ptr<IndexBuffer> p_index_ptr) override;

  private:
    unsigned int m_RendererId;
};

} // namespace Zyklon

#endif // __OPENGLVERTEXARRAY_H__