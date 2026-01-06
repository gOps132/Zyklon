#ifndef __OPENGLVERTEXARRAY_H__
#define __OPENGLVERTEXARRAY_H__

#include <Zyklon/Core/Core.h>

#include <Zyklon/Renderer/VertexArray.h>

namespace Zyklon {
class OpenGLVertexArray ZYKLON_OPENGL_FINAL : public VertexArray {
public:
	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();

	virtual void bind() override;
	virtual void unbind() override;

	virtual void
	addVertexBuffer(const std::shared_ptr<VertexBuffer> &p_vertex_bfr) override;
	virtual void
	setIndexBuffer(const std::shared_ptr<IndexBuffer> &p_index_bfr) override;

	virtual const std::vector<std::shared_ptr<VertexBuffer>> &
	getVertexBuffer() const override
	{
		return m_vertex_bfr;
	}
	virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const override
	{
		return m_index_bfr;
	}

private:
	std::vector<std::shared_ptr<VertexBuffer>> m_vertex_bfr;
	std::shared_ptr<IndexBuffer> m_index_bfr;

	unsigned int m_renderer_id;
};

} // namespace Zyklon

#endif // __OPENGLVERTEXARRAY_H__