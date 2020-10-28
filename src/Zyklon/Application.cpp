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

Application *Application::s_Instance = nullptr;

Application::Application()
{
    ZYKLON_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::create());
    m_Window->set_event_callback(BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer;
    PushOverlay(m_ImGuiLayer);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    float vertices[3 * 3] = {0.5f, -0.5f, 0.0f, -0.5f, -0.5f,
                             0.0f, 0.0f,  0.5f, 0.0f};

    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout({
        {ShaderDataType::Float3, "a_Position"}
    });

    m_VertexBuffer->SetLayout(layout);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (const void *)12);

    unsigned int indices[3] = {0, 1, 2};
    m_IndexBuffer.reset(
        IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    // FIXME: platform agonostic relative working directory
    m_Shader.reset(Shader::Create(
        "/home/gian/dev/engine/Zyklon/src/Shaders/BasicShader.shader"));
}

Application::~Application() {}

void Application::PushLayer(Layer *layer) { m_LayerStack.ls_push_layer(layer); }

void Application::PushOverlay(Layer *layer) {
    m_LayerStack.ls_push_overlay(layer); }

void Application::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(
        BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.ls_begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
}

void Application::Run()
{
    while (m_Running) {
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->bind();

        // m_VertexArray->bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT,
                       nullptr);

        for (Layer *layer : m_LayerStack)
            layer->OnUpdate();

        // TODO: Putting this on a seperate render thread
        m_ImGuiLayer->Begin();
        for (Layer *layer : m_LayerStack)
            layer->OnImGuiRender();
        m_ImGuiLayer->End();

        m_Window->on_update();
    }
}

bool Application::OnWindowClose(WindowCloseEvent &e)
{
    m_Running = false;
    return true;
}
} // namespace Zyklon