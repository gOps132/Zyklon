#ifndef __OPENGLVERTEXARRAY_H__
#define __OPENGLVERTEXARRAY_H__

#include "Renderer/VertexArray.h"

namespace Zyklon {
class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() override;
    virtual void unbind() override;

    virtual void add_vertex_bfr(const std::shared_ptr<VertexBuffer> p_vertex_bfr) override;
    virtual void add_index_bfr(const std::shared_ptr<IndexBuffer> p_index_bfr) override;

  private:
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_bfr;
    std::shared_ptr<IndexBuffer> m_index_bfr;

    unsigned int m_renderer_id;
};

} // namespace Zyklon

#endif // __OPENGLVERTEXARRAY_H__