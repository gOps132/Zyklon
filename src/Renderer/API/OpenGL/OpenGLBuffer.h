#ifndef __OPENGLVERTEXBUFFER_H__
#define __OPENGLVERTEXBUFFER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Buffer.h"

#include <glad/glad.h>

namespace Zyklon {

union OpenGLHelperFunc {
public:
	static GLenum shader_type_to_opengl_typedef(ShaderDataType p_type);
};

class OpenGLVertexBuffer : public VertexBuffer {
public:
	OpenGLVertexBuffer(float *p_vertices, size_t p_size);
	virtual ~OpenGLVertexBuffer();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual void set_layout(const BufferLayout &p_layout) override
	{
		m_layout = p_layout;
	}
	virtual const BufferLayout &get_layout() const override { return m_layout; }

private:
	uint32_t m_renderer_id;
	BufferLayout m_layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
	OpenGLIndexBuffer(uint32_t *p_indices, uint32_t p_size);
	virtual ~OpenGLIndexBuffer();

	virtual void bind() const override;
	virtual void unbind() const override;
	inline virtual uint32_t get_count() const override { return m_count; }

private:
	uint32_t m_renderer_id;
	uint32_t m_count;
};
} // namespace Zyklon

#endif // __OPENGLVERTEXBUFFER_H__