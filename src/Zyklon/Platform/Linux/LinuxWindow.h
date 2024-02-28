#ifndef __LINUXWINDOW_H__
#define __LINUXWINDOW_H__

#include "Zyklon/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/API/OpenGL/OpenGLContext.h"
namespace Zyklon {

class LinuxWindow : public Window {
  public:
	/* Initialize glfw glad etc. */
	LinuxWindow(const WindowProps &props);
	virtual ~LinuxWindow();

	virtual void on_update() override;

	inline virtual unsigned int get_width() const override
	{
		return m_data.width;
	}
	inline virtual unsigned int get_height() const override
	{
		return m_data.height;
	}
	virtual const float get_time() const override;

	// Window attributes
	inline virtual void
	set_event_callback(const EventCallbackFn &p_callback) override
	{
		m_data.event_callback = p_callback;
	}
	virtual void set_vsync(bool p_enabled) override;
	virtual bool vsync() const override;

	/* Returns the GLFW window pointer */
	inline virtual void *get_native_window() const override { return m_window; }

  private:  
	GLFWwindow *m_window;
	GraphicsContext *m_context;

	struct WindowData {
		std::string title;
		unsigned int width, height;
		bool vsync;

		EventCallbackFn event_callback;
	};

	WindowData m_data;
};

} // namespace Zyklon
#endif // __LINUXWINDOW_H__