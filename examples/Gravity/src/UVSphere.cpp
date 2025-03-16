//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "UVSphere.h"

#include <Renderer/Renderer.h>
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

UVSphere::UVSphere(std::string name, float radius, float mass, glm::vec3 position,
			   glm::vec3 velocity, std::string shader_path)
	: PObject(mass, radius, position, velocity), m_name(name),
	  m_shader_path(shader_path)
{
	reset();
}

void UVSphere::generate(const float radius, const int stacks,
								const int slices)
{
	m_vertices.clear();
	m_indices.clear();

	// ZYKLON_INFO("GENERATING SPHERE");
	glm::vec3 normals;

	m_vertices.push_back(0.0f);
	m_vertices.push_back(radius);
	m_vertices.push_back(0.0f);
	//  top normals
	m_vertices.push_back(0.0f);
	m_vertices.push_back(1.0f);
	m_vertices.push_back(0.0f);
	// top uv
	m_vertices.push_back(0.5f);
	m_vertices.push_back(1.0f);

	// middle vertices
	for (int i = 0; i < stacks; ++i) {
		// latitude angle
		float phi = static_cast<float>(i) * glm::pi<float>() /
					static_cast<float>(stacks);
		float y = radius * std::cos(phi);
		float v = 1.0f - static_cast<float>(i) / static_cast<float>(stacks);

		for (int j = 0; j <= slices; ++j) {
			// longhitude angle
			float theta = static_cast<float>(j) * glm::two_pi<float>() /
						  static_cast<float>(slices);
			float x = radius * std::sin(phi) * std::cos(theta);
			float z = radius * std::sin(phi) * std::sin(theta);
			float u = 1.0f - static_cast<float>(j) / static_cast<float>(slices);

			// ZYKLON_INFO("VERTICE: {0}, STACK: {1}, SLICE: {2}, x: {3:.2f}, y:
			// {4:.2f}, z: {5:.2f}", 	i*stacks + j, i, j, x,y,z);

			// positions
			m_vertices.push_back(x);
			m_vertices.push_back(y);
			m_vertices.push_back(z);

			// normals
			normals = glm::normalize(glm::vec3(x, y, z));
			m_vertices.push_back(normals.x);
			m_vertices.push_back(normals.y);
			m_vertices.push_back(normals.z);

			// uv coordinates
			m_vertices.push_back(u);
			m_vertices.push_back(v);
		}
	}

	// Add the bottom vertex (south pole)
	m_vertices.push_back(0.0f);	   // x = 0 (centered)
	m_vertices.push_back(-radius); // y = -radius (bottom pole)
	m_vertices.push_back(0.0f);	   // z = 0 (centered)

	// Bottom pole normal (pointing down)
	m_vertices.push_back(0.0f);	 // Normal x
	m_vertices.push_back(-1.0f); // Normal y
	m_vertices.push_back(0.0f);	 // Normal z

	// Bottom UV coordinates (center of texture at bottom pole)
	m_vertices.push_back(0.5f); // u = 0.5 (center)
	m_vertices.push_back(0.0f); // v = 0 (bottom of texture)

	// top stacks indices
	for (int j = 0; j < slices; ++j) {
		// Top stack (triangles connecting the top vertex)
		m_indices.push_back(0);		// Top vertex
		m_indices.push_back(j + 1); // First vertex on the next ring
		// m_indices.push_back(j + 2);                // Next vertex on the next
		// ring m_indices.push_back(j == slices - 1 ? 1 : j + 2);
		m_indices.push_back((j + 1) % slices + 1);
	}

	// Middle stacks
	for (int i = 0; i < stacks - 2; ++i) {
		for (int j = 0; j < slices; ++j) {
			int first = i * (slices + 1) + (j + 1);
			int second = first + slices + 1;

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
	int start = (stacks - 2) * (slices + 1) + 1; // First vertex of the bottom-most stack

	for (int j = 0; j < slices; ++j) {
		m_indices.push_back(bottomVertexIndex);			 // Bottom pole
		m_indices.push_back(start + j);					 // Current slice
		m_indices.push_back(start + ((j + 1) % slices)); // Wrap to first slice
	}

	m_vertex_buffer.reset(Zyklon::VertexBuffer::create(
		m_vertices.data(), m_vertices.size() * sizeof(float)));
	m_vertex_buffer->set_layout(
		{{Zyklon::ShaderDataType::Float3, "a_position", false},
		 {Zyklon::ShaderDataType::Float3, "a_normal", false},
		 {Zyklon::ShaderDataType::Float2, "a_uv", false}});
	m_vertex_array->add_vertex_bfr(m_vertex_buffer);

	m_index_buffer.reset(
		Zyklon::IndexBuffer::create(m_indices.data(), m_indices.size()));
	m_vertex_array->set_index_bfr(m_index_buffer);

	ZYKLON_INFO("Index: {0}, Vertex: {1}, Normal: ({2}, {3}, {4})",
				m_indices.size(), m_vertices.size() / 8, normals.x, normals.y,
				normals.z);
}

void UVSphere::reset()
{
	m_position = m_initial_position;
	m_velocity = m_initial_velocity;

	m_stretch = {0.0f, 0.0f, 0.0f};

	m_vertex_array.reset(Zyklon::VertexArray::create());

	m_shader.reset(Zyklon::Shader::create(m_shader_path));

	// generate_circle(m_segments, m_radius, m_center_x, m_center_y);
	generate(m_radius, m_stacks, m_slices);
}

void UVSphere::set_shader(std::string shader_path)
{
	m_shader_path = shader_path;
	m_shader.reset(Zyklon::Shader::create(m_shader_path));
}

void UVSphere::update_shader(float time)
{
	m_texture->bind(m_slot);
	m_shader->set_uniform_1i("u_Texture", m_slot);

	m_shader->set_uniform_1f("u_time", time);

	m_shader->set_uniform_3fv("u_color", m_color);
	m_shader->set_uniform_3fv("u_ambient_light_color", m_ambient_light_color);
	m_shader->set_uniform_1f("u_ambient_light_intensity",
							 m_ambient_light_intensity);
	m_shader->set_uniform_3fv("u_directional_light_color",
							  m_directional_light_color);

	m_shader->set_uniform_3fv("u_stretch", m_stretch);
}

void UVSphere::render(glm::mat4 transform)
{
	Zyklon::Renderer::submit(m_shader, m_vertex_array, transform);
}

void UVSphere::render_gui()
{
	ImGui::Begin(m_name.c_str());
	ImGui::ColorPicker3("sphere color", glm::value_ptr(m_color), 0);
	ImGui::ColorPicker3("directional light color",
						glm::value_ptr(m_directional_light_color), 0);
	ImGui::ColorPicker3("ambient light color",
						glm::value_ptr(m_ambient_light_color), 0);
	ImGui::SliderFloat("ambient light intensity", &m_ambient_light_intensity,
					   0.0f, 1.0f, "%.3f");
	if (ImGui::SliderFloat("radius", &m_radius, 1.0f, 100.0f, "%.2f")) {
		generate(m_radius, m_stacks, m_slices);
	}

	if (ImGui::SliderInt("stacks", &m_stacks, 0, 100, "%d")) {
		generate(m_radius, m_stacks, m_slices);
	}

	if (ImGui::SliderInt("slices", &m_slices, 0, 100, "%d")) {
		generate(m_radius, m_stacks, m_slices);
	}
	// ImGui::Text("Fun transformations!");
	// ImGui::SliderFloat3("stretching", glm::value_ptr(m_stretch), 0.0f, 10.0f,
	// "%.3f", 1.0f);
	ImGui::Text("Physics");

	ImGui::SliderFloat("Mass", &m_mass, 1.0f, 100.0f, "%.2f");

	// ImGui::SliderFloat3("Initial Position",
	// glm::value_ptr(m_initial_position), -10.0f, 10.0f, "%.3f", 1.0f);
	// ImGui::SliderFloat3("Initial Velocity",
	// glm::value_ptr(m_initial_velocity), -10.0f, 10.0f, "%.3f", 1.0f);

	ImGui::InputFloat3("Initial Position", glm::value_ptr(m_initial_position));
	ImGui::InputFloat3("Initial Velocity", glm::value_ptr(m_initial_velocity));

	ImGui::InputFloat3("Velocity: ", glm::value_ptr(m_velocity));
	ImGui::InputFloat3("Position: ", glm::value_ptr(m_position));
	// ImGui::SliderFloat3("velocity", glm::value_ptr(m_velocity),
	// -10.0f, 10.0f, "%.3f", 1.0f);

	if (ImGui::Button("reset sphere"))
		reset();
	ImGui::End();
}
