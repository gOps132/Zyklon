#ifndef __OPENGLVERTEXBUFFER_H__
#define __OPENGLVERTEXBUFFER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/VertexBuffer.h"

namespace Zyklon
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, size_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override; 
        virtual void Unbind() const override;

    private:
        uint32_t m_RendererID;
    };
    
} // namespace Zyklon

#endif // __OPENGLVERTEXBUFFER_H__