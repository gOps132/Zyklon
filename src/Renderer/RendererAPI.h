#ifndef __RENDERERAPI_H__
#define __RENDERERAPI_H__

#include <glm/glm.hpp>

#include "Buffer.h"
#include "VertexArray.h"

namespace Zyklon {
class RendererAPI {
public:
	enum class API { None = 0, OpenGL = 1 };

	static void set_renderer_api(const RendererAPI::API &p_api);

	virtual void set_clear_color(const glm::vec4 &p_color) = 0;
	virtual void clear() = 0;

	virtual void draw_indexed(const std::shared_ptr<VertexArray> &p_vertex_array) = 0;
	virtual void draw_arrays(const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t indices) = 0;

	inline static const API get_api() { return s_api; }

private:
	static API s_api;
};

} // namespace Zyklon

#endif // __RENDERERAPI_H__