#include "Mesh.h"

#include "RenderCommand.h"
#include <Zyklon/Renderer/VertexArray.h> // Ensure this header is included for VertexArray::create()

namespace Zyklon {
Mesh::Mesh(const std::vector<float> &vertices, // Changed from VertexBuffer
											   // to float for direct data
		   const std::vector<uint32_t> &indices, const BufferLayout &layout)
{
	m_vertex_array = Ref<VertexArray>(VertexArray::create());
	m_vertex_array->bind(); // bind to VAO first

	m_vertex_buffer = Ref<VertexBuffer>(
		VertexBuffer::create(vertices.data(), vertices.size() * sizeof(float)));
	m_vertex_buffer->setLayout(layout);
	m_vertex_array->addVertexBuffer(m_vertex_buffer);

	m_index_buffer =
		Ref<IndexBuffer>(IndexBuffer::create(indices.data(), indices.size()));
	m_vertex_array->setIndexBuffer(m_index_buffer);

	m_vertex_array->unbind(); // unbind after setup
}

void Mesh::bind() const { m_vertex_array->bind(); }

void Mesh::unbind() const { m_vertex_array->unbind(); }

} // namespace Zyklon