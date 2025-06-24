#ifndef __RENDERERAPI_H__
#define __RENDERERAPI_H__

#include <glm/glm.hpp>

#include "Buffer.h"
#include "VertexArray.h"

namespace Zyklon {
class RendererAPI {
public:
	enum class API { None = 0, OpenGL = 1 };

	static void setRendererAPI(const RendererAPI::API &p_api);

	virtual void setViewport(int p_x, int p_y, int p_width, int p_height) = 0;
	virtual void setClearColor(const glm::vec4 &p_color) = 0;
	virtual void clear() = 0;

	virtual void drawIndexed(const std::shared_ptr<VertexArray> &p_vertex_array) = 0;
	virtual void drawArrays(const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t indices) = 0;

	inline static const API getAPI() { return s_api; }

private:
	static API s_api;
};

} // namespace Zyklon

#endif // __RENDERERAPI_H__