#ifndef __OPENGLVERTEXARRAY_H__
#define __OPENGLVERTEXARRAY_H__

#include "Renderer/VertexArray.h"

namespace Zyklon
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() override;
    };
    
} // namespace Zyklon

#endif // __OPENGLVERTEXARRAY_H__