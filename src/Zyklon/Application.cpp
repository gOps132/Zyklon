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

	// triangle
	// m_triangle_vertex_array.reset(VertexArray::create());

	// float triangle_vertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	// 							 0.5f,	-0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	// 							 0.0f,	0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

	// m_triangle_vertex_bfr.reset(
	// 	VertexBuffer::create(triangle_vertices, sizeof(triangle_vertices)));
	// m_triangle_vertex_bfr->set_layout(
	// 	{{ShaderDataType::Float3, "a_Position", false},
	// 	 {ShaderDataType::Float4, "a_Color", false}});
	// m_triangle_vertex_array->add_vertex_bfr(m_triangle_vertex_bfr);

	// unsigned int triangle_indices[3] = {0, 1, 2};

	// m_triangle_index_bfr.reset(IndexBuffer::create(
	// 	triangle_indices, sizeof(triangle_indices) / sizeof(uint32_t)));
	// m_triangle_vertex_array->set_index_bfr(m_triangle_index_bfr);

	// // square
	// m_square_vertex_array.reset(VertexArray::create());

	// float square_vertices[4 * 3] = {-0.75f, -0.75f, 0.0f, 0.75f,  -0.75f, 0.0f,
	// 								0.75f,	0.75f,	0.0f, -0.75f, 0.75f,  0.0f};

	// m_square_vertex_bfr.reset(
	// 	VertexBuffer::create(square_vertices, sizeof(square_vertices)));
	// m_square_vertex_bfr->set_layout(
	// 	{{ShaderDataType::Float3, "a_Position", false}});
	// m_square_vertex_array->add_vertex_bfr(m_square_vertex_bfr);

	// unsigned int square_indices[6] = {0, 1, 2, 2, 3, 0};

	// m_square_index_bfr.reset(IndexBuffer::create(
	// 	square_indices, sizeof(square_indices) / sizeof(uint32_t)));
	// m_square_vertex_array->set_index_bfr(m_square_index_bfr);

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
	// 	20, 21, 22, 22, 23, 20  // Left face
	// };

	// 1080x720p aspect ratio:
	float aspectRatio = 1280.0f / 720.0f; // 1.5

	// Recommended defaults based on common usage:
	float fovY = glm::radians(45.0f); // Field of view in the vertical direction
	float nearPlane = 0.1f;          // Near clipping plane distance
	float farPlane = 100.0f;         // Far clipping plane distance

	m_cube_shader.reset(Shader::create("src/Shaders/Cube.shader"));

	// TODO: Find a way to accept uniforms
	// Define model matrix (initially identity)
	glm::mat4 model;
	model = glm::rotate(model, -55.0f, glm::vec3(1.0f,0.5f,0.0f));
	// Next we need to create a view matrix. We want to move slightly backwards in the scene so
	// the object becomes visible
	// Set up view and projection matrices (adjust based on your camera/viewport)
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));
	glm::mat4 projection = glm::perspective(fovY, aspectRatio, nearPlane, farPlane);

	m_cube_vertex_bfr.reset(
		VertexBuffer::create(cube_vertices, sizeof(cube_vertices)));
	m_cube_vertex_bfr->set_layout({
		{ShaderDataType::Float3, "a_Position", false},
		{ShaderDataType::Float2, "a_Normal", false}
	});
	m_cube_vertex_array->add_vertex_bfr(m_cube_vertex_bfr);

	// m_cube_index_bfr.reset(IndexBuffer::create(cube_indices, sizeof(cube_indices) / sizeof(uint32_t)));
	// m_cube_vertex_array->set_index_bfr(m_cube_index_bfr);

	m_cube_shader->set_uniform_vec_3("light_color", glm::vec3(0.5,1.0,1.0));

	m_cube_shader->set_uniform_matrix_4fv("model", model);
	m_cube_shader->set_uniform_matrix_4fv("view", view);
	m_cube_shader->set_uniform_matrix_4fv("model", projection);

	// m_square_shader.reset(Shader::create("src/Shaders/Square.shader"));
	// m_triangle_shader.reset(Shader::create("src/Shaders/Triangle.shader"));
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

		// m_square_shader->bind();
		// Renderer::submit(m_square_vertex_array);

		// m_triangle_shader->bind();
		// Renderer::submit(m_triangle_vertex_array);

		m_cube_shader->bind();
		Renderer::submit_vertex(m_cube_vertex_array);

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