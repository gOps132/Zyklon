//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "Sphere.h"
#include <imgui-test/imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <math.h>

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Sphere();
}

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_camera(new Zyklon::PerspectiveCamera(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane))
{
	reset_state();
}

void ExampleLayer::reset_state()
{
	m_vertex_array.reset(Zyklon::VertexArray::create());

	// TODO: include issues may arrive later
	m_shader.reset(Zyklon::Shader::create("examples/Sphere/src/Shaders/Triangle.shader"));

// sample pentagon
	const float PI = 3.14159265358979323846f;
	const int numVertices = 5; // Pentagon has 5 vertices

	// Center coordinates for the pentagon
	float cx = 0.0f;
	float cy = 0.0f;
	float radius = 0.5f; // Radius of the circle that the pentagon is inscribed in

	// Vertex buffer for the pentagon
	float vertices[numVertices * 3]; // 3 coordinates (x, y, z) per vertex

	// float vertices[numVertices * 3];

	// Vertex data for a pentagon (triangle fan)
	// float vertices[15 * 3] = {
	// 	// Triangle 1
	// 	0.0f, 0.0f, 0.0f,    // Center vertex
	// 	0.0f,  0.5f, 0.0f,   // Top vertex
	// 	0.4755f,  0.1545f, 0.0f,  // Top-right vertex

	// 	// Triangle 2
	// 	0.0f, 0.0f, 0.0f,    // Center vertex
	// 	0.4755f,  0.1545f, 0.0f,  // Top-right vertex
	// 	0.2939f, -0.4045f, 0.0f,  // Bottom-right vertex

	// 	// Triangle 3
	// 	0.0f, 0.0f, 0.0f,    // Center vertex
	// 	0.2939f, -0.4045f, 0.0f,  // Bottom-right vertex
	// 	-0.2939f, -0.4045f, 0.0f, // Bottom-left vertex

	// 	// Triangle 4
	// 	0.0f, 0.0f, 0.0f,    // Center vertex
	// 	-0.2939f, -0.4045f, 0.0f, // Bottom-left vertex
	// 	-0.4755f,  0.1545f, 0.0f,  // Top-left vertex

	// 	// Triangle 5
	// 	0.0f, 0.0f, 0.0f,    // Center vertex
	// 	-0.4755f,  0.1545f, 0.0f,  // Top-left vertex
	// 	0.0f,  0.5f, 0.0f   // Top vertex
	// };


	// float _vertices[6 * 3] = {
	// 	// First triangle (Top-left, Bottom-left, Bottom-right)
	// 	-0.5f,  0.5f, 0.0f,  // Top-left
	// 	-0.5f, -0.5f, 0.0f,  // Bottom-left
	// 	0.5f, -0.5f, 0.0f,  // Bottom-right

	// 	// Second triangle (Top-left, Bottom-right, Top-right)
	// 	-0.5f,  0.5f, 0.0f,  // Top-left
	// 	0.5f, -0.5f, 0.0f,  // Bottom-right
	// 	0.5f,  0.5f, 0.0f   // Top-right
	// };

	for (int i = 0; i < numVertices; ++i) {
		float angle = 2.0f * PI * float(i) / float(numVertices);
		vertices[i * 3] = cx + radius * cos(angle);   // x-coordinate
		vertices[i * 3 + 1] = cy + radius * sin(angle); // y-coordinate
		vertices[i * 3 + 2] = 0.0f;                     // z-coordinate (in 2D, z is 0)
	}

	// float vertices[3*3] = {
	// 	// X, Y, Z  (in NDC space)
	// 	0.0f,  0.5f, 0.0f,  // Top vertex
	// 	-0.5f, -0.5f, 0.0f,  // Bottom left vertex
	// 	0.5f, -0.5f, 0.0f   // Bottom right vertex
	// };

	m_vertex_buffer.reset(
		Zyklon::VertexBuffer::create(vertices, sizeof(vertices)));
	m_vertex_buffer->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_position", false},
	});
	m_vertex_array->add_vertex_bfr(m_vertex_buffer);

	m_camera_position = glm::vec3(0.0f,0.0f,5.0f);
	m_camera_rotation = 0.0f;

	m_camera->set_position(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	// m_cube_index_bfr.reset(IndexBuffer::create(cube_indices, sizeof(cube_indices) / sizeof(uint32_t)));
	// m_vertex_array->set_index_bfr(m_cube_index_bfr);	
}

// GAMELOOP
void ExampleLayer::on_update(Zyklon::Timestep ts)
{
	// ZYKLON_TRACE("DELTA TIME, {0}, {1}ms", ts.get_seconds(), ts.get_milliseconds());
	// if (Zyklon::Input::key_pressed(ZYKLON_KEY_TAB))
	// 	ZYKLON_INFO("Tab Key is Pressed");

	float frequency = 1.0f; // Adjust for desired oscillation speed (higher = faster)
    float amplitude = 0.2f; // Adjust for desired oscillation range

	float model_rotation_speed = 15.0f;

	m_model_position = glm::vec3(m_model_pos[0], m_model_pos[1], m_model_pos[2]);

	m_model_position.y =
		amplitude *
		cos(frequency * Zyklon::Application::get().get_window().get_time());

	// ZYKLON_INFO("ts: {0}, value: {1}",
	// 	ts.get_seconds(),
	// 	(cos(frequency * Zyklon::Application::get().get_window().get_time())));

	m_model = glm::translate(glm::mat4(1.0f), m_model_position);
	m_model = glm::rotate(
		m_model, (glm::radians(model_rotation_speed * sin(ts))),
		glm::vec3(0.1f, 0.1f, 0.1f)
	);

	float camera_speed = 10.0f;
	float camera_rotation_speed = 1.5f;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_W))
		m_camera_position.y -= camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_S))
		m_camera_position.y += camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_A))
		m_camera_position.x -= camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_D))
		m_camera_position.x += camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_UP))
		m_camera_position.z -= camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_DOWN))
		m_camera_position.z += camera_speed * ts;

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_LEFT))
		m_camera_rotation -= camera_rotation_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_RIGHT))
		m_camera_rotation += camera_rotation_speed * ts;

	m_camera->set_position(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	m_shader->set_uniform_1f("u_time", Zyklon::Application::get().get_window().get_time());
	m_shader->set_uniform_3fv("u_color", {m_color[0], m_color[1], m_color[2]});

	Zyklon::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

	Zyklon::Renderer::begin_scene(*m_camera);
		glm::mat4 transform = glm::translate(m_model, glm::vec3(1.0f)) * scale;
		Zyklon::Renderer::submit_vertex(m_shader, m_vertex_array, 15, transform);
	Zyklon::Renderer::end_scene();

	// m_shader->bind();
}

void ExampleLayer::on_event(Zyklon::Event &event)
{
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Shader Uniforms");
	ImGui::Text("Hello World!");
	ImGui::ColorPicker3("color", m_color, 0);
	ImGui::SliderFloat3("model position", m_model_pos, 0.0f, 1.0f, "%.2f", 1.0f);
	if (ImGui::Button("reset"))
		reset_state();
	ImGui::End();
}