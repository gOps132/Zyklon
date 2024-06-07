//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "Sandbox.h"
#include <imgui-test/imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Sandbox();
}

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_camera(new Zyklon::PerspectiveCamera(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane))
{
	reset_state();
}

void ExampleLayer::reset_state()
{
	m_cube_vertex_array.reset(Zyklon::VertexArray::create());

	// TODO: include issues may arrive later
	m_cube_shader.reset(Zyklon::Shader::create("examples/Sandbox/src/Shaders/Cube.shader"));

	// vertices 3, normals 3
	float cube_vertices[36 * 5] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// uint32_t cube_indices[6 * 6] = {
	// 	0, 1, 2, 2, 3, 0, // Front face
	// 	4, 5, 6, 6, 7, 4, // Back face
	// 	8, 9, 10, 10, 11, 8, // Top face
	// 	12, 13, 14, 14, 15, 12, // Bottom face
	// 	16, 17, 18, 18, 19, 16, // Right face
	// 	20, 21, 22, 22, 23, 20   // Left face
	// };

	m_cube_vertex_bfr.reset(
		Zyklon::VertexBuffer::create(cube_vertices, sizeof(cube_vertices)));
	m_cube_vertex_bfr->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_Position", false},
		{Zyklon::ShaderDataType::Float2, "a_Normal", false}
	});
	m_cube_vertex_array->add_vertex_bfr(m_cube_vertex_bfr);

	m_cube_shader->set_uniform_3fv("light_color", glm::vec3(0.5,1.0,1.0));

	m_model_position = glm::vec3(0.0f,0.0f,0.0f);
	m_camera_position = glm::vec3(0.0f,0.0f,1.0f);

	m_camera->set_position(m_camera_position);

	// m_cube_index_bfr.reset(IndexBuffer::create(cube_indices, sizeof(cube_indices) / sizeof(uint32_t)));
	// m_cube_vertex_array->set_index_bfr(m_cube_index_bfr);	
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

	m_cube_shader->set_uniform_1f("u_time", Zyklon::Application::get().get_window().get_time());

	Zyklon::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	Zyklon::Renderer::begin_scene(*m_camera);
		for (int i = 0; i < 5; i++)
		{
			for (int y = 0; y < 5; y++)
			{
				glm::vec3 offset(i * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(m_model, offset) * scale;
				Zyklon::Renderer::submit_vertex(m_cube_shader, m_cube_vertex_array, 36, transform);
			}
		}
		// ZYKLON_TRACE("camera {0},{1},{2}", 
		// 	m_camera->get_position().x,
		// 	m_camera->get_position().y,
		// 	m_camera->get_position().z
		// );
	Zyklon::Renderer::end_scene();

	// m_cube_shader->bind();
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
	ImGui::Text("Hello World!");
	if (ImGui::Button("reset"))
		reset_state();
	ImGui::End();
}