#include "Zyklon/zyklon_pch.h"

#include <glad/glad.h>

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

namespace Zyklon
{
    OpenGLVertexArray::OpenGLVertexArray() 
    {
        glGenVertexArrays(1, &m_RendererId);
    }

    void OpenGLVertexArray::bind() 
    {
        glBindVertexArray(m_RendererId);
    }
    
    void OpenGLVertexArray::unbind() 
    {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::add_vertex_bfr(const std::shared_ptr<VertexBuffer> p_vertex_bfr) 
    {
        ZYKLON_CORE_ASSERT(p_vertex_bfr->get_layout().get_elements().size(), "VertexBuffer has no layout!");

        glBindVertexArray(m_RendererId);
        p_vertex_bfr->bind();

        uint32_t index = 0;
        const auto &layout = p_vertex_bfr->get_layout();
        for (const auto &element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, element.get_component_count(),
                OpenGLHelperFunc::shader_type_to_opengl_typedef(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                element.size, (const void *)element.offset);
            index++;
        }

        m_VertexBuffers.push_back(p_vertex_bfr);
    }
    
    void OpenGLVertexArray::add_index_bfr(const std::shared_ptr<IndexBuffer> p_index_bfr) 
    {
        glBindVertexArray(m_RendererId);
        p_index_bfr->bind();

        m_IndexBuffers = p_index_bfr;
    }    
} // namespace Zyklon
