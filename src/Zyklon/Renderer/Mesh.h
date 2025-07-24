#ifndef __MESH_H__
#define __MESH_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include "VertexArray.h"
#include "Buffer.h"

namespace Zyklon {

class Mesh {
public:
	Mesh(const std::vector<VertexBuffer> &vertices,
		 const std::vector<uint32_t> &indices, const BufferLayout &layout);
	~Mesh() = default;

	void bind() const;
	void unbind() const;

	Ref<VertexArray> getVertexArray() const { return m_vertex_array; }
	uint32_t getIndexCount() const { return m_index_buffer->getCount(); }

protected:
	Ref<VertexBuffer> m_vertex_buffer;
	Ref<IndexBuffer> m_index_buffer;
	Ref<VertexArray> m_vertex_array;
};

} // namespace Zyklon

#endif // __MESH_H__