/*
 * Actual application instances
*/

#include "zyklon_pch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Core.h"
#include "Input/Input.h"

#include <glad/glad.h>

namespace Zyklon {

    /* singleton instance */
    Application* Application::s_Instance = nullptr;

    Application::Application(/* args */)
    {
        /* assert to see if you only have one application */
        ZYKLON_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        unsigned int id;
        glGenVertexArrays(1, &id);

        m_ImGuiLayer = new ImGuiLayer;
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
    }

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
	}

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
      	{
      		(*--it)->OnEvent(e);
      		if (e.Handled)
      			break;
      	}
    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
				        layer->OnUpdate();

            // TODO: Putting this on a seperate render thread
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
