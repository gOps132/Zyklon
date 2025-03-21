#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "Buffer.h"

namespace Zyklon {
class VertexArray {
  public:
	virtual ~VertexArray() {}

	virtual void bind() = 0;
	virtual void unbind() = 0;

	virtual void add_vertex_bfr(const std::shared_ptr<VertexBuffer> &p_vertex_bfr) = 0;
	virtual void set_index_bfr(const std::shared_ptr<IndexBuffer> &p_index_ptr) = 0;

	virtual const std::vector<std::shared_ptr<VertexBuffer>> &get_vertex_bfr() const = 0;
	virtual const std::shared_ptr<IndexBuffer> &get_index_bfr() const = 0;

	static VertexArray *create();
};

} // namespace Zyklon

#endif // __VERTEXARRAY_H__