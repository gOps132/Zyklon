#ifndef __WINDOWSWINDOW_H__
#define __WINDOWSWINDOW_H__

#include "Zyklon/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Zyklon
{

	class WindowsWindow : public Window
	{
	public:
		/* Initialize glfw glad etc. */
		WindowsWindow(const WindowProps &props);
		virtual ~WindowsWindow();

		virtual void on_update() override;

		inline virtual unsigned int get_width() const override { return m_Data.Width; }
		inline virtual unsigned int get_height() const override { return m_Data.Height; }

		// Window attributes
		inline virtual void
                set_event_callback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
		virtual void set_vsync(bool enabled) override;
		virtual bool is_vsync() const override;

		/* Returns the GLFW window pointer */
		inline virtual void *get_native_window() const { return m_Window; }

	private:
		GLFWwindow *m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

} // namespace Zyklon
#endif // __WINDOWSWINDOW_H__