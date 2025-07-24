#include "Mesh.h"

#include "RenderCommand.h"

namespace Zyklon {
Mesh::Mesh(const std::vector<VertexBuffer> &vertices,
		   const std::vector<uint32_t> &indices, const BufferLayout &layout)
{
	m_vertex_array = createRef<VertexArray>();
	m_vertex_array->bind(); // bind to VAO first

	m_vertex_buffer = createRef<VertexBuffer>(vertices.data(),
											  vertices.size() * sizeof(float));
	m_vertex_buffer->setLayout(layout);
	m_vertex_array->addVertexBuffer(m_vertex_buffer);

	m_index_buffer = createRef<IndexBuffer>(indices.data(), indices.size());
	m_vertex_array->setIndexBuffer(m_index_buffer);

	m_vertex_array->unbind(); // unbind after setup
}

void Mesh::bind() const { m_vertex_array->bind(); }

void Mesh::unbind() const { m_vertex_array->unbind(); }

} // namespace Zyklon