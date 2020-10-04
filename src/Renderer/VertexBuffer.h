#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon
{
    class VertexBuffer
    { 
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0; 
        virtual void Unbind() const = 0;

        static VertexBuffer* Create(float* vertices, size_t size);
    };

} // namespace Zyklon

#endif // __VERTEXBUFFER_H__