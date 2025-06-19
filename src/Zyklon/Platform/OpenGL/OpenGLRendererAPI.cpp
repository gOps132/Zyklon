#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Zyklon {

void OpenGLRendererAPI::setViewport(int p_x, int p_y, int p_width, int p_height)
{
	glViewport(p_x, p_y, p_width, p_height);		
}

void OpenGLRendererAPI::setClearColor(const glm::vec4 &p_color)
{
	glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);
}

void OpenGLRendererAPI::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(
	const std::shared_ptr<VertexArray> &p_vertex_array)
{
	glDrawElements(GL_TRIANGLES, p_vertex_array->getIndexBfr()->getCount(),
				   GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::drawArrays(const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices)
{
	glDrawArrays(GL_TRIANGLES, 0, p_indices);
}

} // namespace Zyklon