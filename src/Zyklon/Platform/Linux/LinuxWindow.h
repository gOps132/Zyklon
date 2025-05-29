#ifndef __LINUXWINDOW_H__
#define __LINUXWINDOW_H__

#include <Zyklon/Core/Window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Renderer/API/OpenGL/OpenGLContext.h>

namespace Zyklon {

class LinuxWindow : public Window {
  public:
	/* Initialize glfw glad etc. */
	LinuxWindow(const WindowProps &props);
	virtual ~LinuxWindow();

	virtual void onUpdate() override;

	inline virtual unsigned int getWidth() const override
	{
		return m_data.width;
	}
	inline virtual unsigned int getHeight() const override
	{
		return m_data.height;
	}
	virtual float getTime() override;

	// Window attributes
	inline virtual void
	setEventCallback(const EventCallbackFn &p_callback) override
	{
		m_data.event_callback = p_callback;
	}
	virtual void setVsync(bool p_enabled) override;
	virtual bool vsync() const override;

	/* Returns the GLFW window pointer */
	inline virtual void *getNativeWindow() const override { return m_window; }

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