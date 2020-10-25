#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "API/OpenGL/OpenGLVertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray* Create();

    virtual void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
};


#endif // __VERTEXARRAY_H__