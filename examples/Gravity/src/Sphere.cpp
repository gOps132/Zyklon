//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "Sphere.h"

#include <Renderer/Renderer.h>
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

Sphere::Sphere(
		std::string p_name, 
		glm::vec3 p_model_position,
		std::string p_shader_path)
	: 	m_name(p_name), m_model_position_og(p_model_position), m_shader_path(p_shader_path)
{
	reset();
}

/*
void ExampleLayer::generate_circle(	
	const int p_segments,
	const float p_radius,
	const float p_center_x,
	const float p_center_y
){
	// BUG TOO MANY LOGS CAUSE PROGRAM TO CRASH
	// ZYKLON_INFO("GENERATING CIRCLE");

	m_vertices.clear();
	m_vertices.shrink_to_fit();
	m_indices.clear();
	m_indices.shrink_to_fit();

// default
	m_vertices.push_back(p_center_x);
	m_vertices.push_back(p_center_y);
	m_vertices.push_back(0.0);
	
	// calculate angle between each segment
	float angle_increment = 2.0f * M_PI / p_segments;

	for(int i = 0; i < p_segments; i++)
	{
		float angle = i * angle_increment;
		float x = p_center_x + p_radius * std::cos(angle);
		float y = p_center_y + p_radius * std::sin(angle);
		float z = 0.0f;
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
	}

	for (int i = 0; i <= p_segments; ++i) {
		m_indices.push_back(0);		 					// Center vertex
		m_indices.push_back(i);  						// Current vertex on the circumference
		m_indices.push_back(i % p_segments + 1);  	// Next vertex on the circumference
	}

	m_indices.push_back(0);
	m_indices.push_back(p_segments);
	m_indices.push_back(1);

	// std::vector<float> vertices = {
	// 	// X, Y, Z  (in NDC space)
	// 	0.0f,  0.5f, 0.0f,  // Top vertex
	// 	-0.5f, -0.5f, 0.0f,  // Bottom left vertex
	// 	0.5f, -0.5f, 0.0f   // Bottom right vertex
	// };

	// std::vector<uint32_t> indices = { 0,1,2 };

	m_vertex_buffer.reset(
		Zyklon::VertexBuffer::create(m_vertices.data(), m_vertices.size() * sizeofstatic_cast<float>());
	m_vertex_buffer->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_position", false},
	});
	m_vertex_array->add_vertex_bfr(m_vertex_buffer);

	m_index_buffer.reset(Zyklon::IndexBuffer::create(m_indices.data(), m_indices.size() * sizeof(uint32_t)));
	m_vertex_array->set_index_bfr(m_index_buffer);
}
*/

void Sphere::generate_uv_sphere(
		const float p_radius,
		const int p_stacks,
		const int p_slices)
{
	m_vertices.clear();
	m_vertices.shrink_to_fit();
	m_indices.clear();
	m_indices.shrink_to_fit();

	// ZYKLON_INFO("GENERATING SPHERE");

	m_vertices.push_back(0.0f);
	m_vertices.push_back(p_radius);
	m_vertices.push_back(0.0f);
//  top normals
	m_vertices.push_back(0.0f);
	m_vertices.push_back(1.0f);
	m_vertices.push_back(0.0f);
// top uv
	m_vertices.push_back(0.5f);
	m_vertices.push_back(1.0f);

// middle vertices
	for(int i = 1; i < p_stacks; ++i)
	{
		// latitude angle
		float phi = static_cast<float>(i * glm::pi<float>()) / static_cast<float>(p_stacks);
		float v = static_cast<float>(i / p_stacks);

		for(int j = 0; j <= p_slices; ++j)
		{
			// longhitude angle 
			float theta = j * glm::two_pi<float>() / static_cast<float>(p_slices);
			float u = static_cast<float>(j) / static_cast<float>(p_slices);

			float x = p_radius * std::sin(phi) * std::cos(theta);
			float y = p_radius * std::cos(phi);
			float z = p_radius * std::sin(phi) * std::sin(theta);

			// ZYKLON_INFO("VERTICE: {0}, STACK: {1}, SLICE: {2}, x: {3:.2f}, y: {4:.2f}, z: {5:.2f}",
			// 	i*p_stacks + j, i, j, x,y,z);

			// positions
			m_vertices.push_back(x);
			m_vertices.push_back(y);
			m_vertices.push_back(z);

			// normals
			glm::vec3 normals = glm::normalize(glm::vec3(x,y,z));
			m_vertices.push_back(normals.x);
			m_vertices.push_back(normals.y);
			m_vertices.push_back(normals.z);

			// uv coordinates
			m_vertices.push_back(u);
			m_vertices.push_back(v);
 		}
	}

	// Add the bottom vertex (south pole)
	m_vertices.push_back(0.0f);               // x = 0 (centered)
	m_vertices.push_back(-p_radius);           // y = -radius (bottom pole)
	m_vertices.push_back(0.0f);               // z = 0 (centered)

	// Bottom pole normal (pointing down)
	m_vertices.push_back(0.0f);               // Normal x
	m_vertices.push_back(-1.0f);              // Normal y
	m_vertices.push_back(0.0f);               // Normal z

	// Bottom UV coordinates (center of texture at bottom pole)
	m_vertices.push_back(0.5f);               // u = 0.5 (center)
	m_vertices.push_back(0.0f);               // v = 0 (bottom of texture)

	// top stacks indices
	for (int j = 0; j < p_slices; ++j) {
		// Top stack (triangles connecting the top vertex)
		m_indices.push_back(0);                    // Top vertex
		m_indices.push_back(j + 1);                // First vertex on the next ring
		// m_indices.push_back(j + 2);                // Next vertex on the next ring
		m_indices.push_back(j == p_slices - 1 ? 1 : j + 2);
	}

	// Middle stacks
	for (int i = 0; i < p_stacks - 2; ++i) {
		for (int j = 0; j < p_slices; ++j) {
			int first = i * (p_slices + 1) + (j + 1);
			int second = first + p_slices + 1;

			// First triangle of the quad
			m_indices.push_back(first);
			m_indices.push_back(second);
			m_indices.push_back(first + 1);

			// Second triangle of the quad
			m_indices.push_back(second);
			m_indices.push_back(second + 1);
			m_indices.push_back(first + 1);
		}
	}

	// Bottom stack (triangles connecting the bottom vertex)
	int bottomVertexIndex = static_cast<int>(m_vertices.size() / 8) - 1;
	int start = (p_stacks - 2) * (p_slices + 1) + 1;
	for (int j = 0; j < p_slices; ++j) {
		m_indices.push_back(bottomVertexIndex);
		m_indices.push_back(start + ((j + 1) % p_slices));              // Wrap around for last slice
		m_indices.push_back(start + j);
	}
	
	m_vertex_buffer.reset(
		Zyklon::VertexBuffer::create(m_vertices.data(), m_vertices.size() * sizeof(float)));
	m_vertex_buffer->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_position", false},
		{Zyklon::ShaderDataType::Float3, "a_normal", false},
		{Zyklon::ShaderDataType::Float2, "a_uv", false}
	});
	m_vertex_array->add_vertex_bfr(m_vertex_buffer);

	m_index_buffer.reset(Zyklon::IndexBuffer::create(m_indices.data(), m_indices.size()));
	m_vertex_array->set_index_bfr(m_index_buffer);
}

void Sphere::reset()
{
	m_model_position = m_model_position_og;

	m_stretch[0] = 1.0f;
	m_stretch[1] = 1.0f;
	m_stretch[2] = 1.0f;

	m_vertex_array.reset(Zyklon::VertexArray::create());

	m_shader.reset(Zyklon::Shader::create(m_shader_path));

	// generate_circle(m_segments, m_radius, m_center_x, m_center_y);
	generate_uv_sphere(m_radius, m_stacks, m_slices);
}

void Sphere::set_shader(std::string p_shader_path)
{
	m_shader_path = p_shader_path;
	m_shader.reset(Zyklon::Shader::create(m_shader_path));
}

void Sphere::update_shader(float p_time)
{
	m_shader->set_uniform_1f("u_time", p_time);

	m_shader->set_uniform_3fv("u_color", {m_color[0], m_color[1], m_color[2]});
	m_shader->set_uniform_3fv("u_ambient_light_color", {m_ambient_light_color[0], m_ambient_light_color[1], m_ambient_light_color[2]});
	m_shader->set_uniform_1f("u_ambient_light_intensity", m_ambient_light_intensity);
	m_shader->set_uniform_3fv("u_directional_light_color", {m_directional_light_color[0], m_directional_light_color[1], m_directional_light_color[2]});

	m_shader->set_uniform_3fv("u_stretch", {m_stretch[0], m_stretch[1], m_stretch[2]});
}

void Sphere::render(glm::mat4 p_transform)
{
	Zyklon::Renderer::submit(m_shader, m_vertex_array, p_transform);
}

void Sphere::render_gui()
{
	ImGui::Begin("Sphere Uniforms");
		ImGui::ColorPicker3("sphere color", m_color, 0);
		ImGui::ColorPicker3("directional light color", m_directional_light_color, 0);
		ImGui::ColorPicker3("ambient light color", m_ambient_light_color, 0);
		ImGui::SliderFloat("ambient light intensity", &m_ambient_light_intensity, 0.0f, 1.0f, "%.3f");
		ImGui::SliderFloat("scale", &m_scale, 0.0f, 100.0f, "%.2f", 1.0f);
		ImGui::SliderFloat("rotation speed", &m_model_rotation_speed, 0.0f, 5.0f, "%.2f");
		if (ImGui::SliderFloat("radius", &m_radius, 1.0f, 100.0f, "%.2f"))
			generate_uv_sphere(m_radius, m_stacks, m_slices);

		if (ImGui::SliderInt("stacks", &m_stacks, 0, 100, "%d"))
			generate_uv_sphere(m_radius, m_stacks, m_slices);

		if (ImGui::SliderInt("slices", &m_slices, 0, 100, "%d"))
			generate_uv_sphere(m_radius, m_stacks, m_slices);
			// generate_circle(m_segments, m_radius, m_center_x, m_center_y);
	
		ImGui::Text("Fun transformations!");
		ImGui::SliderFloat3("stretching", m_stretch, 0.0f, 10.0f, "%.3f", 1.0f);
		if (ImGui::Button("reset sphere"))
			reset();
	ImGui::End();
}
