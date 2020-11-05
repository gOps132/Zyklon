#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "Buffer.h"

namespace Zyklon {
class VertexArray {
  public:
    virtual ~VertexArray();
    
    virtual void AddBuffer(const VertexBuffer &vb,
                           const BufferLayout &layout) = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static VertexArray *Create();
};

} // namespace Zyklon

#endif // __VERTEXARRAY_H__