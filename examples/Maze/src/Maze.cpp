//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "Maze.h"
#include <imgui-test/imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Maze();
}

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_camera(new Zyklon::PerspectiveCamera(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane))
{
	reset_state();
}

void ExampleLayer::reset_state()
{
	m_square_vertex_array.reset(Zyklon::VertexArray::create());

	// TODO: include issues may arrive later
	m_square_shader.reset(Zyklon::Shader::create("examples/Maze/src/Shaders/Square.shader"));

	float square_vertices[5 * 4] = {
		// Position             // Texture coordinates
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f,   // Top-left
		0.5f,  0.5f, 0.0f,     1.0f, 1.0f,   // Top-right
		0.5f, -0.5f, 0.0f,     1.0f, 0.0f,   // Bottom-right
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f    // Bottom-left
	};

	uint32_t square_indices[3 * 2] = {
		0, 1, 2,   // First triangle
		0, 2, 3    // Second triangle
	};

	m_square_vertex_buffer.reset(
		Zyklon::VertexBuffer::create(square_vertices, sizeof(square_vertices)));
	m_square_vertex_buffer->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_Position", false},
		{Zyklon::ShaderDataType::Float2, "a_Tex", false}
	});
	m_square_vertex_array->add_vertex_bfr(m_square_vertex_buffer);

	m_square_shader->set_uniform_3fv("light_color", glm::vec3(0.5,1.0,1.0));

	m_model_position = glm::vec3(0.0f,0.0f,0.0f);
	m_camera_position = glm::vec3(0.0f,0.0f,1.0f);
	m_camera_rotation = 0.0f;

	m_camera->set_position(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	m_square_index_buffer.reset(Zyklon::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
	m_square_vertex_array->set_index_bfr(m_square_index_buffer);
}

// GAMELOOP
void ExampleLayer::on_update(Zyklon::Timestep ts)
{
	float time = Zyklon::Application::get().get_window().get_time();
	float frequency = 1.0f; // Adjust for desired oscillation speed (higher = faster)
    float amplitude = 0.2f; // Adjust for desired oscillation range

	float model_rotation_speed = 15.0f;

	// m_model_position.y =
	// 	amplitude *
	// 	cos(frequency * time);

	// ZYKLON_INFO("ts: {0}, value: {1}",
	// 	ts.get_seconds(),
	// 	(cos(frequency * Zyklon::Application::get().get_window().get_time())));

	m_model = glm::translate(glm::mat4(1.0f), m_model_position);
	// m_model = glm::rotate(
	// 	m_model, (glm::radians(model_rotation_speed * sin(ts))),
	// 	glm::vec3(0.1f, 0.1f, 0.1f)
	// );

	float camera_speed = 10.0f;
	float camera_rotation_speed = 1.5f;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_W))
		m_model_position.y -= m_camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_S))
		m_model_position.y += m_camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_A))
		m_model_position.x -= m_camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_D))
		m_model_position.x += m_camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_UP))
		m_camera_position.z += m_camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_DOWN))
		m_camera_position.z -= m_camera_speed * ts;

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_LEFT))
		m_camera_rotation -= m_camera_rotation_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_RIGHT))
		m_camera_rotation += m_camera_rotation_speed * ts;

	m_camera->set_position(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	m_square_shader->set_uniform_1f("u_time", time);
	m_square_shader->set_uniform_3fv("u_color", {m_color[0], m_color[1], m_color[2]});

	Zyklon::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	Zyklon::Renderer::begin_scene(*m_camera);
		// for (int i = 0; i < 5; i++)
		// {
		// 	for (int y = 0; y < 5; y++)
		// 	{
		// 		glm::vec3 offset(i * 0.11f, y * 0.11f, 0.0f);
		// 		glm::mat4 transform = glm::translate(m_model, offset) * scale;
				glm::mat4 transform = glm::translate(m_model, glm::vec3(0.0f)) * scale;
				Zyklon::Renderer::submit(m_square_shader, m_square_vertex_array, transform);
		// 	}
		// }
	Zyklon::Renderer::end_scene();
	// m_square_shader->bind();
}

void ExampleLayer::on_event(Zyklon::Event &event)
{
	// if(event.get_event_type() == Zyklon::EventType::WindowResize)
	// {
	// }
	// ZYKLON_TRACE("{0}", event);
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Shader Uniforms");
	ImGui::ColorPicker3("color", m_color, 0);
	if (ImGui::Button("reset"))
		reset_state();
	ImGui::End();
}