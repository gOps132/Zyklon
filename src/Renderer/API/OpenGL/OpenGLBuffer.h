#ifndef __OPENGLVERTEXBUFFER_H__
#define __OPENGLVERTEXBUFFER_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include <glad/glad.h>

#include <Renderer/Buffer.h>



namespace Zyklon {

union OpenGLHelperFunc {
public:
	static GLenum shaderTypeToOpenGLTypedef(ShaderDataType p_type);
};

class OpenGLVertexBuffer ZYKLON_OPENGL_FINAL : public VertexBuffer {
public:
	OpenGLVertexBuffer(float *p_vertices, size_t p_size);
	virtual ~OpenGLVertexBuffer();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual void setLayout(const BufferLayout &p_layout) override
	{
		m_layout = p_layout;
	}
	virtual const BufferLayout &getLayout() const override { return m_layout; }

private:
	uint32_t m_renderer_id;
	BufferLayout m_layout;
};

class OpenGLIndexBuffer ZYKLON_OPENGL_FINAL : public IndexBuffer {
public:
	OpenGLIndexBuffer(uint32_t *p_indices, uint32_t p_size);
	virtual ~OpenGLIndexBuffer();

	virtual void bind() const override;
	virtual void unbind() const override;
	inline virtual uint32_t getCount() const override { return m_count; }

private:
	uint32_t m_renderer_id;
	uint32_t m_count;
};
} // namespace Zyklon

#endif // __OPENGLVERTEXBUFFER_H__