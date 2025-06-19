#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Zyklon/zyklon_exports.h>

#include <Zyklon/Events/ApplicationEvent.h>
#include <Zyklon/Events/Event.h>

#include <Zyklon/Imgui/ImguiLayer.h>

#include <Zyklon/Renderer/Buffer.h>
#include <Zyklon/Renderer/Shader.h>
#include <Zyklon/Renderer/VertexArray.h>

#include "LayerStack.h"
#include "Window.h"

#include "Timestep.h"

namespace Zyklon {

/* Single Application class */
class ZYKLON_EXPORT Application {
public:
	Application();
	virtual ~Application() {}

	static Application *createApplication();

	/* Main run Loop */
	void run();

	void onEvent(Event &e);

	void pushLayer(Layer *p_layer);
	void pushOverlay(Layer *p_layer);

	inline Window &getWindow() { return *m_window; }

	inline static Application &get() { return *s_instance; }

private:
	bool onWindowClose(WindowCloseEvent &e);
private:
	std::unique_ptr<Window> m_window;
	ImGuiLayer *m_imgui_layer;
	bool m_running = true;
	LayerStack m_layer_stack;
	
	Timestep m_timestep;
	float m_last_frame_time = 0.0f;
private:
	static Application *s_instance;
};

} // namespace Zyklon

#endif // __APPLICATION_H__