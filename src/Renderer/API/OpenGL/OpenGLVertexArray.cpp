#include "Zyklon/zyklon_pch.h"

#include <glad/glad.h>

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

namespace Zyklon
{
    OpenGLVertexArray::OpenGLVertexArray() 
    {
        glGenVertexArrays(1, &m_renderer_id);
    }
    
    OpenGLVertexArray::~OpenGLVertexArray() 
    {
        glDeleteVertexArrays(1, &m_renderer_id);
    }

    void OpenGLVertexArray::bind() 
    {
        glBindVertexArray(m_renderer_id);
    }
    
    void OpenGLVertexArray::unbind() 
    {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::add_vertex_bfr(const std::shared_ptr<VertexBuffer> p_vertex_bfr) 
    {
        ZYKLON_CORE_ASSERT(p_vertex_bfr->get_layout().get_elements().size(), "VertexBuffer has no layout!");

        glBindVertexArray(m_renderer_id);
        p_vertex_bfr->bind();

        uint32_t index = 0;
        const BufferLayout &layout = p_vertex_bfr->get_layout();
        for (const BufferElement &element : layout.get_elements()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, element.get_component_count(),
                OpenGLHelperFunc::shader_type_to_opengl_typedef(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                element.size, (const void *)element.offset);
            index++;
        }

        m_vertex_bfr.push_back(p_vertex_bfr);
    }
    
    void OpenGLVertexArray::set_index_bfr(const std::shared_ptr<IndexBuffer> p_index_bfr) 
    {
        glBindVertexArray(m_renderer_id);
        p_index_bfr->bind();

        m_index_bfr = p_index_bfr;
    }    
} // namespace Zyklon
