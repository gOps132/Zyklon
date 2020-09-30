#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "zyklon_exports.h"

#include "Window.h"
#include "LayerStack.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Imgui/ImguiLayer.h"

#include "Renderer/API/OpenGL/Shader.h"

namespace Zyklon
{

    /* The Central application of the Game or the client */
    class ZYKLON_EXPORT Application
    {
    public:
        Application(/* args */);
        virtual ~Application();

        /* Main Run Loop */
        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }

        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;

        bool m_Running = true;
        LayerStack m_LayerStack;

        unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

        std::unique_ptr<Shader> m_Shader;
    private:
        static Application* s_Instance;
    };

    Application *CreateApplication();
} // namespace Zyklon

#endif // __APPLICATION_H__