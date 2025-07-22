#include "Mesh.h"

#include "RenderCommand.h"

namespace Zyklon {

Mesh::Mesh(const std::vector<VertexBuffer>& vertices, const std::vector<uint32_t>& indices)
{
	m_vertex_buffer = createRef<VertexBuffer>(vertices);
	m_index_buffer = createRef<IndexBuffer>(indices);
	m_vertex_array = createRef<VertexArray>();

	m_vertex_array->addVertexBuffer(m_vertex_buffer);
	m_vertex_array->setIndexBuffer(m_index_buffer);
}

void Mesh::bind()
{

}

void Mesh::unbind()
{
	
}

} // namespace Zyklon