#include <zyklon_pch.h>

#include "Zyklon/Core/Application.h"

#include <GLFW/glfw3.h>

#include "LinuxInput.h"


namespace Zyklon {
Input *Input::s_instance = new LinuxInput();

bool LinuxInput::keyPressedImpl(int keycode)
{
	auto window = static_cast<GLFWwindow *>(
		Application::get().getWindow().getNativeWindow());
	auto state = glfwGetKey(window, keycode);

	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::mouseBtnPressedImpl(int button)
{
	auto window = static_cast<GLFWwindow *>(
		Application::get().getWindow().getNativeWindow());
	auto state = glfwGetMouseButton(window, button);

	return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::getMousePosImpl()
{
	auto window = static_cast<GLFWwindow *>(
		Application::get().getWindow().getNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return {(float)xPos, (float)yPos};
}

float LinuxInput::getMouseXImpl()
{
	auto [x, y] = getMousePosImpl();
	return x;
}

float LinuxInput::getMouseYImpl()
{
	auto [x, y] = getMousePosImpl();
	return y;
}

} // namespace Zyklon