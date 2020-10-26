#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "zyklon_exports.h"

#include "LayerStack.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

#include "Imgui/ImguiLayer.h"

#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"

namespace Zyklon {

/* Single Application class */
class ZYKLON_EXPORT Application {
  public:
    Application();
    virtual ~Application();

    static Application *CreateApplication();

    /* Main Run Loop */
    void Run();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);

    inline Window &GetWindow() { return *m_Window; }

    inline static Application &Get() { return *s_Instance; }
  private:
    bool OnWindowClose(WindowCloseEvent &e);

    std::unique_ptr<Window> m_Window;
    ImGuiLayer *m_ImGuiLayer;

    bool m_Running = true;
    LayerStack m_LayerStack;

    unsigned int m_VertexArray;

    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;

  private:
    static Application *s_Instance;
};

} // namespace Zyklon

#endif // __APPLICATION_H__