#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon {
class IndexBuffer {
  public:
    virtual ~IndexBuffer(){};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    inline virtual uint32_t GetCount() const = 0;

    static IndexBuffer *Create(uint32_t *indices, size_t size);
};

} // namespace Zyklon

#endif // __INDEXBUFFER_H__