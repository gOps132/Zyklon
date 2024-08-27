//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include "Sphere.h"
#include <imgui-test/imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Sphere();
}

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
	reset_state();
}

// reset the vertex array
void ExampleLayer::generate_circle(	
	const int p_num_segments,
	const float p_radius,
	const float p_center_x,
	const float p_center_y
){
	ZYKLON_INFO("GENERATING CIRCLE");

	m_vertices.clear();
	m_vertices.shrink_to_fit();
	m_indices.clear();
	m_indices.shrink_to_fit();

// default
	m_vertices.push_back(p_center_x); 
	m_vertices.push_back(p_center_y);
	m_vertices.push_back(0.0);
	
	// calculate angle between each segment
	float angle_increment = 2.0f * M_PI / p_num_segments;

	for(int i = 0; i < p_num_segments; i++)
	{
		float angle = i * angle_increment;
		float x = p_center_x + p_radius * std::cos(angle);
		float y = p_center_y + p_radius * std::sin(angle);
		float z = 0.0f;
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
	}

	for (int i = 0; i <= p_num_segments; ++i) {
		m_indices.push_back(0);		 					// Center vertex
		m_indices.push_back(i);  						// Current vertex on the circumference
		m_indices.push_back(i % p_num_segments + 1);  	// Next vertex on the circumference
	}

	m_indices.push_back(0);
	m_indices.push_back(p_num_segments);
	m_indices.push_back(1);

	// std::vector<float> vertices = {
	// 	// X, Y, Z  (in NDC space)
	// 	0.0f,  0.5f, 0.0f,  // Top vertex
	// 	-0.5f, -0.5f, 0.0f,  // Bottom left vertex
	// 	0.5f, -0.5f, 0.0f   // Bottom right vertex
	// };

	// std::vector<uint32_t> indices = { 0,1,2 };

	m_vertex_buffer.reset(
		Zyklon::VertexBuffer::create(m_vertices.data(), m_vertices.size() * sizeof(float)));
	m_vertex_buffer->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_position", false},
	});
	m_vertex_array->add_vertex_bfr(m_vertex_buffer);

	m_index_buffer.reset(Zyklon::IndexBuffer::create(m_indices.data(), m_indices.size() * sizeof(uint32_t)));
	m_vertex_array->set_index_bfr(m_index_buffer);
}

void ExampleLayer::reset_state()
{
	m_camera = std::make_unique<Zyklon::PerspectiveCamera>(glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);

	m_vertex_array.reset(Zyklon::VertexArray::create());

	// TODO: include issues may arrive later
	m_shader.reset(Zyklon::Shader::create("examples/Sphere/src/Shaders/Polygon.shader"));

	m_camera_position = glm::vec3(0.0f,0.0f,10.0f);
	m_camera_rotation = 0.0f;

	m_camera->set_position(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	generate_circle(m_segments, m_radius, m_center_x, m_center_y);
}

void ExampleLayer::on_update(Zyklon::Timestep ts)
{
	float frequency = 1.0f; // Adjust for desired oscillation speed (higher = faster)
    float amplitude = 0.2f; // Adjust for desired oscillation range

	float model_rotation_speed = 15.0f;

	m_model_position = glm::vec3(m_model_pos[0], m_model_pos[1], m_model_pos[2]);

	m_model_position.y =
		amplitude *
		cos(frequency * Zyklon::Application::get().get_window().get_time());

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

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));

	Zyklon::Renderer::begin_scene(*m_camera);
		// translate object into world space
		glm::mat4 transform = glm::translate(m_model, glm::vec3(1.0f)) * scale;

		// Zyklon::Renderer::submit_vertex(m_shader, m_vertex_array, 3, transform);
		Zyklon::Renderer::submit(m_shader, m_vertex_array, transform);
	Zyklon::Renderer::end_scene();

	// m_shader->bind();
}

void ExampleLayer::on_event(Zyklon::Event &event)
{
	if(event.get_event_type() == Zyklon::EventType::WindowResize)
	{
		m_aspect_ratio =	Zyklon::Application::get().get_window().get_width() / 
						Zyklon::Application::get().get_window().get_height(); // 1.5
	}
	// ZYKLON_TRACE("{0}", event);
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Shader Uniforms");
		ImGui::ColorPicker3("color", m_color, 0);
		ImGui::SliderFloat3("model position", m_model_pos, 0.0f, 1.0f, "%.2f", 1.0f);
		ImGui::SliderFloat("scale", &m_scale, 0.0f, 100.0f, "%.2f", 1.0f);
		if (ImGui::SliderInt("segments", &m_segments, 3, 40, "%d"))
			generate_circle(m_segments, m_radius, m_center_x, m_center_y);
		ImGui::Text("Camera options!");
		ImGui::SliderFloat("fov", &m_fovy, 20.0f, 120.0f, "%.2f", 5.0f);
		if (ImGui::Button("reset"))
			reset_state();
	ImGui::End();
}