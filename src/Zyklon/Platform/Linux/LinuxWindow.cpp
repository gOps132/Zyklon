#include "Zyklon/zyklon_pch.h"

#include "Zyklon/Events/ApplicationEvent.h"
#include "Zyklon/Events/KeyEvent.h"
#include "Zyklon/Events/MouseEvent.h"

#include "LinuxWindow.h"

#include "Renderer/API/OpenGL/OpenGLContext.h"

namespace Zyklon {

//  Initialized GLFW once, but we might initialize more than one window
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description)
{
    ZYKLON_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window *Window::create(const WindowProps &props)
{
    return new LinuxWindow(props);
}

LinuxWindow::LinuxWindow(const WindowProps &props)
{
    m_Data.Title = props.title;
    m_Data.Width = props.width;
    m_Data.Height = props.height;

    ZYKLON_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width,
                     props.height);
    if (!s_GLFWInitialized) {
        // TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwSetErrorCallback(GLFWErrorCallback);

        ZYKLON_CORE_ASSERT(success, "Could not intialize GLFW!");

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.width, (int)props.height,
                                m_Data.Title.c_str(), nullptr, nullptr);

    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    set_vsync(true);

    // Set GLFW callback
    glfwSetWindowSizeCallback(
        m_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                    int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(
        m_Window, [](GLFWwindow *window, int button, int action, int mode) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });

    glfwSetScrollCallback(
        m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
}

void LinuxWindow::set_vsync(bool enabled)
{
    glfwSwapInterval(enabled);
    m_Data.VSync = enabled;
}

bool LinuxWindow::is_vsync() const { return m_Data.VSync; }

LinuxWindow::~LinuxWindow() { glfwDestroyWindow(m_Window); }

void LinuxWindow::on_update()
{
    glfwPollEvents();
    m_Context->SwapBuffers();
}
} // namespace Zyklon