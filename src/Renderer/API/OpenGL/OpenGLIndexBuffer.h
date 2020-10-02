#ifndef __OPENGLINDEXBUFFER_H__
#define __OPENGLINDEXBUFFER_H__

#include "Renderer/IndexBuffer.h"

namespace Zyklon
{ 
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, size_t size);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override; 
        virtual void Unbind() const override;
    };
    
} // namespace Zyklon

#endif // __OPENGLINDEXBUFFER_H__