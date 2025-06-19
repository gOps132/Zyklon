#include <zyklon_pch.h>

#include "Shader.h"

#include "Renderer.h"
#include "RenderCommand.h"

namespace Zyklon {

Renderer::SceneData* Renderer::m_scene_data = new Renderer::SceneData();

void Renderer::beginScene(Camera& p_camera) 
{
	m_scene_data->m_view_projection_matrix = p_camera.get_view_projection_matrix();
}

void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<Shader> &p_shader, const std::shared_ptr<VertexArray> &p_vertex_array, const glm::mat4& p_transform)
{
	p_shader->bind();
	p_shader->setUniformMatrix4fv("u_view_projection", m_scene_data->m_view_projection_matrix);
	p_shader->setUniformMatrix4fv("u_transform", p_transform);

	p_vertex_array->bind();
	RenderCommand::drawIndexed(p_vertex_array);
}

void Renderer::submitVertex(const std::shared_ptr<Shader> &p_shader, const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices, const glm::mat4& p_transform)
{
	p_shader->bind();
	p_shader->setUniformMatrix4fv("u_view_projection", m_scene_data->m_view_projection_matrix);
	p_shader->setUniformMatrix4fv("u_transform", p_transform);

	p_vertex_array->bind();
	RenderCommand::drawArrays(p_vertex_array, p_indices);
}

} // namespace Zyklon
