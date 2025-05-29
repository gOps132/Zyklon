//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "Grid.h"
#include <imgui-test/imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Zyklon::Application *Zyklon::Application::createApplication()
{
	return new Grid();
}

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_camera(new Zyklon::PerspectiveCamera(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane))
{
	resetState();
}

void ExampleLayer::resetState()
{
	m_camera_rotation = 0.0f;
	m_camera_position =  glm::vec3(0.0f,0.0f,1.0f);
	m_model_position = glm::vec3(0.0f,0.0f,0.0f);

	m_grid_vertex_arr.reset(Zyklon::VertexArray::create());

	// TODO: include issues may arrive later
	m_grid_shader.reset(Zyklon::Shader::create("examples/Grid/src/Shaders/Grid.shader"));

	float grid_vertices[5 * 4] = {
		// Position             // Texture coordinates
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f,   // Top-left
		0.5f,  0.5f, 0.0f,     1.0f, 1.0f,   // Top-right
		0.5f, -0.5f, 0.0f,     1.0f, 0.0f,   // Bottom-right
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f    // Bottom-left
	};

	uint32_t grid_indices[3 * 2] = {
		0, 1, 2,   // First triangle
		0, 2, 3    // Second triangle
	};

	m_grid_vertex_bfr.reset(
		Zyklon::VertexBuffer::create(grid_vertices, sizeof(grid_vertices)));
	m_grid_vertex_bfr->setLayout({
		{Zyklon::ShaderDataType::Float3, "a_Position", false},
		{Zyklon::ShaderDataType::Float2, "a_Tex", false}
	});
	m_grid_vertex_arr->addVertexBfr(m_grid_vertex_bfr);

	m_grid_shader->setUniform3fv("light_color", glm::vec3(0.5,1.0,1.0));

	m_camera->setPosition(m_camera_position);

	m_grid_index_bfr.reset(Zyklon::IndexBuffer::create(grid_indices, sizeof(grid_indices) / sizeof(uint32_t)));
	m_grid_vertex_arr->setIndexBfr(m_grid_index_bfr);
}

// GAMELOOP
void ExampleLayer::onUpdate(Zyklon::Timestep ts)
{
	// ZYKLON_TRACE("DELTA TIME, {0}, {1}ms", ts.getSeconds(), ts.getMilliseconds());
	// if (Zyklon::Input::keyPressed(ZYKLON_KEY_TAB))
	// 	ZYKLON_INFO("Tab Key is Pressed");

	// ZYKLON_INFO("ts: {0}, value: {1}",
	// 	ts.getSeconds(),
	// 	(cos(frequency * Zyklon::Application::get().getWindow().getTime())));

	// ZYKLON_TRACE("Timestep: {0}", (float)ts);
	
	float camera_speed = 10.0f;
	float camera_rotation_speed = 1.5f;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_W))
		m_camera_position.y -= camera_speed * ts;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_S))
		m_camera_position.y += camera_speed * ts;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_A))
		m_camera_position.x -= camera_speed * ts;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_D))
		m_camera_position.x += camera_speed * ts;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_UP))
		m_camera_position.z -= camera_speed * ts;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_DOWN))
		m_camera_position.z += camera_speed * ts;
	
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_LEFT))
		m_camera_rotation -= camera_rotation_speed * ts;
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_RIGHT))
		m_camera_rotation += camera_rotation_speed * ts;

	m_camera->setPosition(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	m_grid_shader->setUniform1f("u_time", Zyklon::Application::get().getWindow().getTime());
	m_grid_shader->setUniform2f("u_params", uniform_float_parameters[0], uniform_float_parameters[1]);

	Zyklon::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	Zyklon::Renderer::beginScene(*m_camera);
	Zyklon::Renderer::submit(m_grid_shader, m_grid_vertex_arr, m_model);
		// ZYKLON_TRACE("camera {0},{1},{2}", 
		// 	m_camera->getPosition().x,
		// 	m_camera->getPosition().y,
		// 	m_camera->getPosition().z
		// );
	Zyklon::Renderer::endScene();
}

void ExampleLayer::onEvent(Zyklon::Event &event)
{
	// if(event.getEventType() == Zyklon::EventType::WindowResize)
	// {
	// }
	// ZYKLON_TRACE("{0}", event);
}

void ExampleLayer::onImguiRender()
{
	ImGui::Begin("Shader Uniforms");
	if (ImGui::Button("reset"))
		resetState();
	ImGui::SliderFloat("Grid Scale", &uniform_float_parameters[0], 0.0f, 100.0f);
	ImGui::SliderFloat("Grid Resolution", &uniform_float_parameters[1], 0.0f, 1.0f);
	ImGui::End();
}