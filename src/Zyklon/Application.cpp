/*
 * Actual application instances
 */

#include "zyklon_pch.h"

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Input/Input.h"
#include "Window.h"

#include <glad/glad.h>

#include "Application.h"

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

    m_vertex_array.reset(VertexArray::create());

    float vertices[] = {
        0.5f,  -0.5f, 0.0f,  0.8f, 0.2f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.0f,
        0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f, 1.0f
    };

    m_vertex_bfr.reset(VertexBuffer::create(vertices, sizeof(vertices)));
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" }
    };

    m_vertex_bfr->set_layout(layout);
    m_vertex_array->add_vertex_bfr(m_vertex_bfr);

    unsigned int indices[] = {0, 1, 2};
    m_index_bfr.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_vertex_array->add_index_bfr(m_index_bfr);

    m_shader.reset(Shader::create("src/Shaders/BasicShader.shader"));
}

Application::~Application() {}

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
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_shader->bind();
        m_vertex_array->bind();

        glDrawElements(GL_TRIANGLES, m_index_bfr->get_count(), GL_UNSIGNED_INT,
                       nullptr);

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