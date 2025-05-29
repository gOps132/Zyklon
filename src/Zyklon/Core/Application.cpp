/*
 * Actual application instances
 */

#include "zyklon_pch.h"

#include <Zyklon/Events/ApplicationEvent.h>
#include <Zyklon/Input/Input.h>

#include "Core.h"
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

	m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
	m_window->setVsync(false);

	m_imgui_layer = new ImGuiLayer;
	pushOverlay(m_imgui_layer);
}

void Application::pushLayer(Layer *layer) { m_layer_stack.pushLayer(layer); }

void Application::pushOverlay(Layer *layer)
{
	m_layer_stack.pushOverlay(layer);
}

void Application::onEvent(Event &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(
		BIND_EVENT_FN(Application::onWindowClose));

	for (auto it = m_layer_stack.end(); it != m_layer_stack.begin();) {
		(*--it)->onEvent(e);
		if (e.handled)
			break;
	}
}

void Application::run()
{
	while (m_running) {
		float time = m_window->getTime();
		// calculate delta Time
		Timestep m_timestep = time - m_last_frame_time;
		m_last_frame_time = time;

		for (Layer *layer : m_layer_stack)
			layer->onUpdate(m_timestep);

		// TODO: Putting this on a seperate render thread
		m_imgui_layer->begin();
		for (Layer *layer : m_layer_stack)
			layer->onImguiRender();
		m_imgui_layer->end();

		m_window->onUpdate();
	}
}

bool Application::onWindowClose(WindowCloseEvent &e)
{
	m_running = false;
	return true;
}

} // namespace Zyklon