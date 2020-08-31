#ifndef __LINUXWINDOW_H__
#define __LINUXWINDOW_H__

#include "Zyklon/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Zyklon
{

	class LinuxWindow : public Window
	{
	public:
		/* Initialize glfw glad etc. */
		LinuxWindow(const WindowProps &props);
		virtual ~LinuxWindow();

		virtual void OnUpdate() override;

		inline virtual unsigned int GetWidth() const override { return m_Data.Width; }
		inline virtual unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline virtual void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
		virtual void SetVsync(bool enabled) override;
		virtual bool IsVsync() const override;

		/* Returns the GLFW window pointer */
		inline virtual void *GetNativeWindow() const override { return m_Window; }

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
#endif // __LINUXWINDOW_H__