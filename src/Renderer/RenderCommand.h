#ifndef __RENDERCOMMAND_H__
#define __RENDERCOMMAND_H__

#include "RendererAPI.h"

namespace Zyklon {
class RenderCommand {
public:
	inline static void set_clear_color(const glm::vec4 &color)
	{
		s_renderer_api->set_clear_color(color);
	}

	inline static void clear() { s_renderer_api->clear(); }

	inline static void draw_indexed(const std::shared_ptr<VertexArray> &vertexArray)
	{
		s_renderer_api->draw_indexed(vertexArray);
	}
private:
	static RendererAPI *s_renderer_api;
};

} // namespace Zyklon

#endif // __RENDERCOMMAND_H__