#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Zyklon {

void OpenGLRendererAPI::set_clear_color(const glm::vec4 &p_color)
{
	glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);
}

void OpenGLRendererAPI::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::draw_indexed(
	const std::shared_ptr<VertexArray> &p_vertex_array)
{
	glDrawElements(GL_TRIANGLES, p_vertex_array->get_index_bfr()->get_count(),
				   GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::draw_arrays(const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices)
{
	glDrawArrays(GL_TRIANGLES, 0, p_indices);
}

} // namespace Zyklon