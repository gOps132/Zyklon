#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "zyklon_exports.h"

#include <Zyklon/Events/ApplicationEvent.h>
#include <Zyklon/Events/Event.h>

#include <Imgui/ImguiLayer.h>

#include <Renderer/Buffer.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>

#include "LayerStack.h"
#include "Window.h"

#include "Timestep.h"

namespace Zyklon {

/* Single Application class */
class ZYKLON_EXPORT Application {
public:
	Application();
	virtual ~Application() {}

	static Application *create_application();

	/* Main run Loop */
	void run();

	void on_event(Event &e);

	void push_layer(Layer *p_layer);
	void push_overlay(Layer *p_layer);

	inline Window &get_window() { return *m_window; }

	inline static Application &get() { return *s_instance; }

private:
	bool on_window_close(WindowCloseEvent &e);
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