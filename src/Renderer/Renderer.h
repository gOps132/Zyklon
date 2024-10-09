#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <Zyklon/Core/zyklon_pch.h>

#include <glm/glm.hpp>

#include "RendererAPI.h"
#include "Shader.h"

#include "Camera/Camera.h"

namespace Zyklon {

class Renderer {
public:
// TODO: setup basic polymorphism for both perspective and orthographic camera
	static void begin_scene(Camera& p_camera);
	static void end_scene();

	static void submit(const std::shared_ptr<Shader> &p_shader, const std::shared_ptr<VertexArray> &p_vertex_array, const glm::mat4& p_transform = glm::mat4(1.0f));
	static void submit_vertex(const std::shared_ptr<Shader> &p_shader, const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices, const glm::mat4& p_transform = glm::mat4(1.0f));

	/* Wrapper for definitions */
	inline static RendererAPI::API get_api() { return RendererAPI::get_api(); }

private:
	struct SceneData {
		glm::mat4 m_view_projection_matrix;
	};

	static SceneData* m_scene_data;
};

} // namespace Zyklon

#endif // __RENDERER_H__