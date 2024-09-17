#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include "OpenGLBuffer.h"
#include "OpenGLErrorManager.h"

namespace Zyklon {

GLenum OpenGLHelperFunc::shader_type_to_opengl_typedef(ShaderDataType p_type)
{
	switch (p_type) {
	case ShaderDataType::Float:
		return GL_FLOAT;
	case ShaderDataType::Float2:
		return GL_FLOAT;
	case ShaderDataType::Float3:
		return GL_FLOAT;
	case ShaderDataType::Float4:
		return GL_FLOAT;
	case ShaderDataType::Mat3:
		return GL_FLOAT;
	case ShaderDataType::Mat4:
		return GL_FLOAT;
	case ShaderDataType::Int:
		return GL_INT;
	case ShaderDataType::Int2:
		return GL_INT;
	case ShaderDataType::Int3:
		return GL_INT;
	case ShaderDataType::Int4:
		return GL_INT;
	case ShaderDataType::Bool:
		return GL_BOOL;
	}

	ZYKLON_CORE_ASSERT(false, "Unkown Shader type");
	return 0;
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float *p_vertices, size_t p_size)
{
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

	GLCall(glGenBuffers(1, &m_renderer_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, p_size, p_vertices, GL_STATIC_DRAW));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void OpenGLVertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void OpenGLVertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *p_indices, uint32_t p_count)
	: m_count(p_count)
{
	GLCall(glGenBuffers(1, &m_renderer_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_count * sizeof(uint32_t),
						p_indices, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void OpenGLIndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void OpenGLIndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace Zyklon
