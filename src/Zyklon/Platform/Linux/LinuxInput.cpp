#include "Zyklon/zyklon_pch.h"

#include "Zyklon/Application.h"

#include "LinuxInput.h"

#include <GLFW/glfw3.h>

namespace Zyklon {
Input *Input::s_instance = new LinuxInput();

bool LinuxInput::key_pressed_impl(int keycode)
{
	auto window = static_cast<GLFWwindow *>(
		Application::get().get_window().get_native_window());
	auto state = glfwGetKey(window, keycode);

	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::mouse_btn_pressed_impl(int button)
{
	auto window = static_cast<GLFWwindow *>(
		Application::get().get_window().get_native_window());
	auto state = glfwGetMouseButton(window, button);

	return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::get_mouse_pos_impl()
{
	auto window = static_cast<GLFWwindow *>(
		Application::get().get_window().get_native_window());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return {(float)xPos, (float)yPos};
}

float LinuxInput::get_mouse_x_impl()
{
	auto [x, y] = get_mouse_pos_impl();
	return x;
}

float LinuxInput::get_mouse_y_impl()
{
	auto [x, y] = get_mouse_pos_impl();
	return y;
}

} // namespace Zyklon