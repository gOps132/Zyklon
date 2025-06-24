#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <zyklon_pch.h>

#include <glm/glm.hpp>

#include "RendererAPI.h"
#include "Shader.h"

#include "Camera/Camera.h"

namespace Zyklon {

class Renderer {
public:
	static void beginScene(Camera& p_camera);
	static void endScene();

	static void submit(const std::shared_ptr<Shader> &p_shader, const std::shared_ptr<VertexArray> &p_vertex_array, const glm::mat4& p_transform = glm::mat4(1.0f));
	static void submitVertex(const std::shared_ptr<Shader> &p_shader, const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices, const glm::mat4& p_transform = glm::mat4(1.0f));

	/* Wrapper for definitions */
	inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

private:
	struct SceneData {
		glm::mat4 m_view_projection_matrix;
	};

	static SceneData* m_scene_data;
};

} // namespace Zyklon

#endif // __RENDERER_H__