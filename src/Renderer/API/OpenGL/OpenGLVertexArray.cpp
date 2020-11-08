#include "Zyklon/zyklon_pch.h"

#include <glad/glad.h>

#include "OpenGLVertexArray.h"

namespace Zyklon
{
    OpenGLVertexArray::OpenGLVertexArray() 
    {
        glGenVertexArrays(1, &m_RendererId);
    }

    void OpenGLVertexArray::Bind() 
    {
        glBindVertexArray(m_RendererId);
    }
    
    void OpenGLVertexArray::Unbind() 
    {
        glGenVertexArrays(0, &m_RendererId);        
    }
    
    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> p_vertex_bfr) 
    {
                
    }
    
    void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer> p_index_ptr) 
    {
        
    }    
} // namespace Zyklon
