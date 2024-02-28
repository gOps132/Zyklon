/*
 * Actual application instances
 */

#include "zyklon_pch.h"

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Input/Input.h"
#include "Window.h"

#include "Application.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Zyklon {

Application *Application::s_instance = nullptr;

Application::Application()
{
	ZYKLON_CORE_ASSERT(!s_instance, "Application already exists!");
	s_instance = this;

	m_window = std::unique_ptr<Window>(Window::create());

	m_window->set_event_callback(BIND_EVENT_FN(Application::on_event));

	m_imgui_layer = new ImGuiLayer;
	push_overlay(m_imgui_layer);

	m_cube_vertex_array.reset(VertexArray::create());

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

	m_cube_shader.reset(Shader::create("src/Shaders/Cube.shader"));


	m_cube_vertex_bfr.reset(
		VertexBuffer::create(cube_vertices, sizeof(cube_vertices)));
	m_cube_vertex_bfr->set_layout({
		{ShaderDataType::Float3, "a_Position", false},
		{ShaderDataType::Float2, "a_Normal", false}
	});
	m_cube_vertex_array->add_vertex_bfr(m_cube_vertex_bfr);

	// m_cube_index_bfr.reset(IndexBuffer::create(cube_indices, sizeof(cube_indices) / sizeof(uint32_t)));
	// m_cube_vertex_array->set_index_bfr(m_cube_index_bfr);
}

void Application::push_layer(Layer *layer) { m_layer_stack.push_layer(layer); }

void Application::push_overlay(Layer *layer)
{
	m_layer_stack.push_overlay(layer);
}

void Application::on_event(Event &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(
		BIND_EVENT_FN(Application::on_window_close));

	for (auto it = m_layer_stack.end(); it != m_layer_stack.begin();) {
		(*--it)->on_event(e);
		if (e.handled)
			break;
	}
}

void Application::run()
{
	while (m_running) {
		RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1});
		RenderCommand::clear();

		Renderer::begin_scene();

// FIXME: find out why, cube wont render after multiplying the MVP uniforms
		// 1080x720p aspect ratio:
		float aspectRatio = (float)m_window->get_width() / (float)m_window->get_height(); // 1.5

		// Recommended defaults based on common usage:
		float fovY = glm::radians(45.0f); // Field of view in the vertical direction
		float nearPlane = 0.1f;          // Near clipping plane distance
		float farPlane = 100.0f;         // Far clipping plane distance

		model = glm::rotate(model, m_window->get_time(), glm::vec3(0.5f, 1.0f, 0.0f));
		view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(fovY, aspectRatio, nearPlane, farPlane);

		m_cube_shader->set_uniform_vec_3("light_color", glm::vec3(0.5,1.0,1.0));

		m_cube_shader->set_uniform_matrix_4fv("model", model);
		m_cube_shader->set_uniform_matrix_4fv("view", view);
		m_cube_shader->set_uniform_matrix_4fv("model", projection);

		m_cube_shader->bind();
		Renderer::submit_vertex(m_cube_vertex_array, 36);

		Renderer::end_scene();

		for (Layer *layer : m_layer_stack)
			layer->on_update();

		// TODO: Putting this on a seperate render thread
		m_imgui_layer->begin();
		for (Layer *layer : m_layer_stack)
			layer->on_imgui_render();
		m_imgui_layer->end();

		m_window->on_update();
	}
}

bool Application::on_window_close(WindowCloseEvent &e)
{
	m_running = false;
	return true;
}

} // namespace Zyklon