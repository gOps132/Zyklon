#include <Zyklon/Core/zyklon_pch.h>

#include <Zyklon/Events/ApplicationEvent.h>
#include <Zyklon/Events/KeyEvent.h>
#include <Zyklon/Events/MouseEvent.h>

#include "LinuxWindow.h"

#include <Renderer/API/OpenGL/OpenGLContext.h>

namespace Zyklon {

//  Initialized GLFW once, but we might initialize more than one window
static bool s_glfw_initialized = false;

static void glfw_error_callback(int p_error, const char *p_description)
{
	ZYKLON_CORE_ERROR("GLFW Error ({0}): {1}", p_error, p_description);
}

Window *Window::create(const WindowProps &p_props)
{
	return new LinuxWindow(p_props);
}

LinuxWindow::LinuxWindow(const WindowProps &p_props)
{
	m_data.title = p_props.title;
	m_data.width = p_props.width;
	m_data.height = p_props.height;

	ZYKLON_CORE_INFO("Creating window {0} ({1}, {2})", p_props.title,
					 p_props.width, p_props.height);
	if (!s_glfw_initialized) {
		// TODO: glfwTerminate on system shutdown
		int success = glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetErrorCallback(glfw_error_callback);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		ZYKLON_CORE_ASSERT(success, "Could not intialize GLFW!");

		s_glfw_initialized = true;
	}

	m_window = glfwCreateWindow((int)p_props.width, (int)p_props.height,
								m_data.title.c_str(), nullptr, nullptr);

	m_context = GraphicsContext::create(m_window);
	m_context->init();

	glfwSetWindowUserPointer(m_window, &m_data);
	set_vsync(true);

	// Set GLFW callback
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow *p_window, int p_width,
										   int p_height) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);
		data.width = p_width;
		data.height = p_height;

		WindowResizeEvent event(p_width, p_height);
		data.event_callback(event);
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow *p_window) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);
		WindowCloseEvent event;
		data.event_callback(event);
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow *p_window, int p_key,
									int p_scancode, int p_action, int p_mods) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);
		switch (p_action) {
		case GLFW_PRESS: {
			KeyPressedEvent event(p_key, 0);
			data.event_callback(event);
			break;
		}
		case GLFW_RELEASE: {
			KeyReleasedEvent event(p_key);
			data.event_callback(event);
			break;
		}
		case GLFW_REPEAT: {
			KeyPressedEvent event(p_key, 1);
			data.event_callback(event);
			break;
		}
		}
	});

	glfwSetCharCallback(m_window, [](GLFWwindow *p_window,
									 unsigned int p_keycode) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);
		KeyTypedEvent event(p_keycode);
		data.event_callback(event);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow *p_window, int p_button,
											int p_action, int p_mode) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);
		switch (p_action) {
		case GLFW_PRESS: {
			MouseButtonPressedEvent event(p_button);
			data.event_callback(event);
			break;
		}
		case GLFW_RELEASE: {
			MouseButtonReleasedEvent event(p_button);
			data.event_callback(event);
			break;
		}
		}
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow *p_window, double p_x_offset,
									   double p_y_offset) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);

		MouseScrolledEvent event((float)p_x_offset, (float)p_y_offset);
		data.event_callback(event);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow *p_window, double p_x_pos,
										  double p_y_pos) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(p_window);

		MouseMovedEvent event((float)p_x_pos, (float)p_y_pos);
		data.event_callback(event);
	});
}

void LinuxWindow::set_vsync(bool p_enabled)
{
	glfwSwapInterval(p_enabled);
	m_data.vsync = p_enabled;
}

bool LinuxWindow::vsync() const { return m_data.vsync; }

LinuxWindow::~LinuxWindow() { glfwDestroyWindow(m_window); }

void LinuxWindow::on_update()
{
	glfwPollEvents();
	m_context->swap_buffers();
}

float LinuxWindow::get_time() 
{
	return glfwGetTime();
}
} // namespace Zyklon