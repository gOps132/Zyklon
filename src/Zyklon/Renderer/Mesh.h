#ifndef __MESH_H__
#define __MESH_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include "VertexArray.h"
#include "Buffer.h"

namespace Zyklon {

class Mesh {
public:
	Mesh(const std::vector<VertexBuffer>& vertices, const std::vector<uint32_t>& indices);
	~Mesh() = default;

	void bind();
	void unbind();
	
protected:
	uint32_t m_indices = 0;

	
	Ref<VertexBuffer> m_vertex_buffer;
	Ref<IndexBuffer> m_index_buffer;
	Ref<VertexArray> m_vertex_array;
};

} // namespace Zyklon

#endif // __MESH_H__