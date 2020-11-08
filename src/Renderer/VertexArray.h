#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "Buffer.h"

namespace Zyklon {
class VertexArray {
  public:
    virtual ~VertexArray();

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    
    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> p_vertex_bfr) = 0;
    virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer> p_index_ptr) = 0;

    static VertexArray *Create();
};

} // namespace Zyklon

#endif // __VERTEXARRAY_H__