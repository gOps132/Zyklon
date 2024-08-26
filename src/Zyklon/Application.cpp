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

namespace Zyklon {

Application *Application::s_instance = nullptr;

Application::Application()
{
	ZYKLON_CORE_ASSERT(!s_instance, "Application already exists!");

	s_instance = this;
	m_window = std::unique_ptr<Window>(Window::create());

	m_window->set_event_callback(BIND_EVENT_FN(Application::on_event));
	m_window->set_vsync(false);

	m_imgui_layer = new ImGuiLayer;
	push_overlay(m_imgui_layer);
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
		float time = m_window->get_time();
		// calculate delta Time
		Timestep m_timestep = time - m_last_frame_time;
		m_last_frame_time = time;

		for (Layer *layer : m_layer_stack)
			layer->on_update(m_timestep);

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