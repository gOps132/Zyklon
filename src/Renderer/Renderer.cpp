#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include "Renderer.h"
#include "RenderCommand.h"

namespace Zyklon {

void Renderer::begin_scene() {}

void Renderer::end_scene() {}

void Renderer::submit(const std::shared_ptr<VertexArray> &p_vertex_array)
{
	p_vertex_array->bind();

	RenderCommand::draw_indexed(p_vertex_array);
}

void Renderer::submit_vertex(const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices)
{
	p_vertex_array->bind();
	RenderCommand::draw_arrays(p_vertex_array, p_indices);
}

} // namespace Zyklon
