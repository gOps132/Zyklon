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
	: Layer("Example")
{
	m_cube_vertex_array.reset(Zyklon::VertexArray::create());

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

// TODO: include issues may arrive later
	m_cube_shader.reset(Zyklon::Shader::create("examples/Sandbox/src/Shaders/Cube.shader"));

	m_cube_vertex_bfr.reset(
		Zyklon::VertexBuffer::create(cube_vertices, sizeof(cube_vertices)));
	m_cube_vertex_bfr->set_layout({
		{Zyklon::ShaderDataType::Float3, "a_Position", false},
		{Zyklon::ShaderDataType::Float2, "a_Normal", false}
	});
	m_cube_vertex_array->add_vertex_bfr(m_cube_vertex_bfr);

	float aspectRatio = 
		Zyklon::Application::get().get_window().get_width() / 
		Zyklon::Application::get().get_window().get_height(); // 1.5

	// Recommended defaults based on common usage:
	float fovY = glm::radians(45.0f); // Field of view in the vertical direction
	float nearPlane = 0.1f;          // Near clipping plane distance
	float farPlane = 100.0f;         // Far clipping plane distance

	view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projection = glm::perspective(fovY, aspectRatio, nearPlane, farPlane);
	m_cube_shader->set_uniform_vec_3("light_color", glm::vec3(0.5,1.0,1.0));

	m_cube_shader->set_uniform_matrix_4fv("view", view);
	m_cube_shader->set_uniform_matrix_4fv("projection", projection);

	// m_cube_index_bfr.reset(IndexBuffer::create(cube_indices, sizeof(cube_indices) / sizeof(uint32_t)));
	// m_cube_vertex_array->set_index_bfr(m_cube_index_bfr);	
}

// GAMELOOP
void ExampleLayer::on_update()
{
	// if (Zyklon::Input::key_pressed(ZYKLON_KEY_TAB))
	// 	ZYKLON_INFO("Tab Key is Pressed");

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_DOWN))
	{
		model = glm::rotate(
			model, (glm::radians(-10.0f)),
			glm::vec3(0.5f, 0.0f, 0.0f)
		);
	}

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_UP))
	{
		model = glm::rotate(
			model, (glm::radians(10.0f)),
			glm::vec3(0.5f, 0.0f, 0.0f)
		);
	}

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_LEFT))
	{
		model = glm::rotate(
			model, (glm::radians(-10.0f)),
			glm::vec3(0.0f, -0.5f, 0.0f)
		);
	}

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_RIGHT))
	{
		model = glm::rotate(
			model, (glm::radians(-10.0f)),
			glm::vec3(0.0f, 0.5f, 0.0f)
		);
	}


	m_cube_shader->set_uniform_matrix_4fv("model", model);
	m_cube_shader->set_uniform_1f("deltaTime", Zyklon::Application::get().get_window().get_time());

	m_cube_shader->bind();
	Zyklon::Renderer::submit_vertex(m_cube_vertex_array, 36);
}

void ExampleLayer::on_event(Zyklon::Event &event)
{
	// ZYKLON_TRACE("{0}", event);
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello World!");
	ImGui::End();
}