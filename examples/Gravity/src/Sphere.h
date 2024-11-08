#ifndef __SPHERE_H__
#define __SPHERE_H__

// TODO: Make prototyping objects easier
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>
#include <Renderer/Shader.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <vector>
#include <memory>

class Sphere {
public:
	Sphere(
		std::string p_name, 
		glm::vec3 p_model_position,
		std::string p_shader_path
	);
	void reset();
	void generate_uv_sphere(
		const float p_radius,
		const int p_stacks,
		const int p_slices
	);
	void set_shader(std::string p_shader_path);
	void update_shader(float p_time);
	void render(glm::mat4 p_transform);
	void render_gui();
	glm::mat4 get_model_matrix() const { return m_model; }
private:
	std::string m_name;
	std::string m_shader_path;

	glm::mat4 m_model         	= glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::vec3 m_model_position;
	glm::vec3 m_model_position_og;

	std::vector<float> m_vertices;
	std::vector<uint32_t> m_indices;
	
	float m_radius			=1.0f;
	int m_stacks			= 50;
	int m_slices 			= 50;

	float m_color[3];
	float m_directional_light_color[3];
	float m_ambient_light_color[3];
	float m_ambient_light_intensity = 0.01f;
	float m_stretch[3] = {1.0f, 1.0f, 1.0f};

	std::shared_ptr<Zyklon::Shader> m_shader;
	std::shared_ptr<Zyklon::VertexBuffer> m_vertex_buffer;
	std::shared_ptr<Zyklon::IndexBuffer> m_index_buffer;
	std::shared_ptr<Zyklon::VertexArray> m_vertex_array;

	float m_scale = 0.5f;
	float m_model_rotation_speed = 0.5f;
};

#endif // __SPHERE_H__