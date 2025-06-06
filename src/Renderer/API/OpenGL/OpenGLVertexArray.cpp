#include <zyklon_pch.h>

#include <glad/glad.h>

#include "OpenGLVertexArray.h"
#include "OpenGLErrorManager.h"
#include "OpenGLBuffer.h"

namespace Zyklon {
OpenGLVertexArray::OpenGLVertexArray()
{
	GLCall(glGenVertexArrays(1, &m_renderer_id));
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_renderer_id));
}

void OpenGLVertexArray::bind() { GLCall(glBindVertexArray(m_renderer_id)); }

void OpenGLVertexArray::unbind() { GLCall(glBindVertexArray(0)); }

void OpenGLVertexArray::addVertexBfr(
	const std::shared_ptr<VertexBuffer> &p_vertex_bfr)
{
	ZYKLON_CORE_ASSERT(p_vertex_bfr->getLayout().getElements().size(),
					   "VertexBuffer has no layout!");

	GLCall(glBindVertexArray(m_renderer_id));
	p_vertex_bfr->bind();

	uint32_t index = 0;
	const BufferLayout &layout = p_vertex_bfr->getLayout();
	for (const BufferElement &element : layout) {
		GLCall(glEnableVertexAttribArray(index));
		GLCall(glVertexAttribPointer(
			index, element.getComponentCount(),
			OpenGLHelperFunc::shaderTypeToOpenGLTypedef(element.type),
			element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(),
			(const void *)element.offset));
		index++;
	}

	m_vertex_bfr.push_back(p_vertex_bfr);
}

void OpenGLVertexArray::setIndexBfr(
	const std::shared_ptr<IndexBuffer> &p_index_bfr)
{
	GLCall(glBindVertexArray(m_renderer_id));
	p_index_bfr->bind();

	m_index_bfr = p_index_bfr;
}
} // namespace Zyklon
