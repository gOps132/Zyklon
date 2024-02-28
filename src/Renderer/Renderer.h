#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Zyklon/zyklon_pch.h"

#include "RendererAPI.h"

namespace Zyklon {

class Renderer {
public:
	static void begin_scene();
	static void end_scene();

	static void submit(const std::shared_ptr<VertexArray> &p_vertex_array);
	static void submit_vertex(const std::shared_ptr<VertexArray> &p_vertex_array);

	/* Wrapper for definitions */
	inline static RendererAPI::API get_api() { return RendererAPI::get_api(); }
};

} // namespace Zyklon

#endif // __RENDERER_H__