#ifndef __RENDERCOMMAND_H__
#define __RENDERCOMMAND_H__

#include "RendererAPI.h"

namespace Zyklon {
class RenderCommand {
public:
	inline static void setViewport(int p_x, int p_y, int p_width, int p_height)
	{
		s_renderer_api->setViewport(p_x, p_y, p_width, p_height);
	}

	inline static void setClearColor(const glm::vec4 &color)
	{
		s_renderer_api->setClearColor(color);
	}

	inline static void clear() { s_renderer_api->clear(); }

	inline static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
	{
		s_renderer_api->drawIndexed(vertexArray);
	}

	inline static void drawArrays(const std::shared_ptr<VertexArray> &vertexArray, uint32_t indices)
	{
		s_renderer_api->drawArrays(vertexArray, indices);
	}
private:
	static RendererAPI *s_renderer_api;
};

} // namespace Zyklon

#endif // __RENDERCOMMAND_H__