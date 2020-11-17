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
        return m_Data.width;
    }
    inline virtual unsigned int get_height() const override
    {
        return m_Data.height;
    }

    // Window attributes
    inline virtual void
    set_event_callback(const EventCallbackFn &callback) override
    {
        m_Data.EventCallback = callback;
    }
    virtual void set_vsync(bool enabled) override;
    virtual bool is_vsync() const override;

    /* Returns the GLFW window pointer */
    inline virtual void *get_native_window() const override { return m_window; }

  private:  
    GLFWwindow *m_window;
    GraphicsContext *m_Context;

    struct WindowData {
        std::string title;
        unsigned int width, height;
        bool vsync;

        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

} // namespace Zyklon
#endif // __LINUXWINDOW_H__