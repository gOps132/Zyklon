//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "HexagonalSphere.h"

#include <Renderer/Renderer.h>
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

HexagonalSphere::HexagonalSphere(std::string name, float radius, float mass, glm::vec3 position,
			   glm::vec3 velocity, std::string shader_path)
	: PObject(mass, radius, position, velocity), m_name(name),
	  m_shader_path(shader_path)
{
	reset();
}

void HexagonalSphere::generate(const float p_radius, const int p_resolution)
{
	m_vertices.clear();
	m_indices.clear();

	// make an icosahedron
	create_icosahedron(p_radius);

    // Step 2: Subdivide the icosahedron
    for (int i = 0; i < p_resolution; ++i) {
        subdivide();
    }

    // Step 3: Use Voronoi tessellation to form the hexagon
    // (This step is complex and typically requires a Voronoi library or custom implementation)
    // For simplicity, we'll skip this step in this example.

    // Create buffers
    m_vertex_buffer.reset(Zyklon::VertexBuffer::create(m_vertices.data(), m_vertices.size() * sizeof(float)));
    m_vertex_buffer->set_layout({
        {Zyklon::ShaderDataType::Float3, "a_position", false},
        {Zyklon::ShaderDataType::Float3, "a_normal", false},
        {Zyklon::ShaderDataType::Float2, "a_uv", false}
    });
    m_vertex_array->add_vertex_bfr(m_vertex_buffer);

    m_index_buffer.reset(Zyklon::IndexBuffer::create(m_indices.data(), m_indices.size()));
    m_vertex_array->set_index_bfr(m_index_buffer);
}

void HexagonalSphere::create_icosahedron(const float p_radius)
{
	const float t = (1.0 + std::sqrt(5.0)) / 2.0;

    std::vector<glm::vec3> positions = {
        {-1,  t,  0},
        { 1,  t,  0},
        {-1, -t,  0},
        { 1, -t,  0},
        { 0, -1,  t},
        { 0,  1,  t},
        { 0, -1, -t},
        { 0,  1, -t},
        { t,  0, -1},
        { t,  0,  1},
        {-t,  0, -1},
        {-t,  0,  1}
    };

    std::vector<uint32_t> indices = {
        0, 11, 5, 0, 5, 1, 0, 1, 7, 0, 7, 10, 0, 10, 11,
        1, 5, 9, 5, 11, 4, 11, 10, 2, 10, 7, 6, 7, 1, 8,
        3, 9, 4, 3, 4, 2, 3, 2, 6, 3, 6, 8, 3, 8, 9,
        4, 9, 5, 2, 4, 11, 6, 2, 10, 8, 6, 7, 9, 8, 1
    };

    for (auto& pos : positions) {
        pos = glm::normalize(pos) * p_radius;
        m_vertices.push_back(pos.x);
        m_vertices.push_back(pos.y);
        m_vertices.push_back(pos.z);
        m_vertices.push_back(pos.x);
        m_vertices.push_back(pos.y);
        m_vertices.push_back(pos.z);
        m_vertices.push_back(0.0f); // Placeholder for UV coordinates
        m_vertices.push_back(0.0f); // Placeholder for UV coordinates
    }

    m_indices = indices;
}

void HexagonalSphere::subdivide()
{
    std::unordered_map<uint64_t, uint32_t> middle_point_cache;

    auto get_middle_point = [&](uint32_t p1, uint32_t p2) -> uint32_t {
        uint64_t key = (uint64_t)p1 << 32 | p2;
        if (middle_point_cache.find(key) != middle_point_cache.end()) {
            return middle_point_cache[key];
        }

        glm::vec3 point1 = glm::vec3(m_vertices[p1 * 8], m_vertices[p1 * 8 + 1], m_vertices[p1 * 8 + 2]);
        glm::vec3 point2 = glm::vec3(m_vertices[p2 * 8], m_vertices[p2 * 8 + 1], m_vertices[p2 * 8 + 2]);
        glm::vec3 middle = glm::normalize((point1 + point2) / 2.0f) * m_radius;

        uint32_t index = m_vertices.size() / 8;
        m_vertices.push_back(middle.x);
        m_vertices.push_back(middle.y);
        m_vertices.push_back(middle.z);
        m_vertices.push_back(middle.x);
        m_vertices.push_back(middle.y);
        m_vertices.push_back(middle.z);
        m_vertices.push_back(0.0f); // Placeholder for UV coordinates
        m_vertices.push_back(0.0f); // Placeholder for UV coordinates

        middle_point_cache[key] = index;
        return index;
    };

    std::vector<uint32_t> new_indices;
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        uint32_t a = m_indices[i];
        uint32_t b = m_indices[i + 1];
        uint32_t c = m_indices[i + 2];

        uint32_t ab = get_middle_point(a, b);
        uint32_t bc = get_middle_point(b, c);
        uint32_t ca = get_middle_point(c, a);

        new_indices.push_back(a);
        new_indices.push_back(ab);
        new_indices.push_back(ca);

        new_indices.push_back(b);
        new_indices.push_back(bc);
        new_indices.push_back(ab);

        new_indices.push_back(c);
        new_indices.push_back(ca);
        new_indices.push_back(bc);

        new_indices.push_back(ab);
        new_indices.push_back(bc);
        new_indices.push_back(ca);
    }

    m_indices = new_indices;
}

void HexagonalSphere::reset()
{
	m_position = m_initial_position;
	m_velocity = m_initial_velocity;

	m_stretch = {0.0f, 0.0f, 0.0f};

	m_vertex_array.reset(Zyklon::VertexArray::create());

	m_shader.reset(Zyklon::Shader::create(m_shader_path));

	generate(m_radius, m_resolution);
}

void HexagonalSphere::set_shader(std::string shader_path)
{
	m_shader_path = shader_path;
	m_shader.reset(Zyklon::Shader::create(m_shader_path));
}

void HexagonalSphere::update_shader(float time)
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

void HexagonalSphere::render(glm::mat4 transform)
{
	Zyklon::Renderer::submit(m_shader, m_vertex_array, transform);
}

void HexagonalSphere::render_gui()
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
		generate(m_radius, m_resolution);
	}

	if (ImGui::SliderInt("resolution", &m_resolution, 1, 5, "%d")) {
		generate(m_radius, m_resolution);
	}

	// ImGui::Text("Fun transformations!");
	// ImGui::SliderFloat3("stretching", glm::value_ptr(m_stretch), 0.0f, 10.0f,
	// "%.3f", 1.0f);
	ImGui::Text("Physics");

	ImGui::SliderFloat("Mass", &m_mass, 1.0f, 100.0f, "%.2f");
	ImGui::InputFloat3("Initial Position", glm::value_ptr(m_initial_position));
	ImGui::InputFloat3("Initial Velocity", glm::value_ptr(m_initial_velocity));

	ImGui::InputFloat3("Velocity: ", glm::value_ptr(m_velocity));
	ImGui::InputFloat3("Position: ", glm::value_ptr(m_position));

	if (ImGui::Button("reset sphere"))
		reset();
	ImGui::End();
}
