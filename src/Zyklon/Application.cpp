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

    Application* Application::s_Instance = nullptr;

    Application::Application(/* args */)
    {
        ZYKLON_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer;
        PushOverlay(m_ImGuiLayer);
        
//      TEMP
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	    float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

        // VertexBuffer buffer = VertexBuffer::Create(sizeof(vertices), vertices);
        
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main() 
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }            
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            in vec3 v_Position;   

            layout(location = 0) out vec4 color;

            void main() 
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }            
        )";

        m_Shader = std::make_unique<OpenGLShader>(vertexSrc, fragmentSrc);
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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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