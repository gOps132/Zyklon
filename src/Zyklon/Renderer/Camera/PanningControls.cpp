// ./Renderer/Camera/PanningControls.cpp

#include "PanningControls.h"

#include <Zyklon/Input/MouseButtonCodes.h>
#include <Zyklon/Input/KeyCodes.h>
#include <Zyklon/Input/Input.h>

namespace Zyklon {

PanningControls::PanningControls(Ref<Camera> p_camera)
	: m_camera(p_camera), m_is_panning(false)
{
	m_pan_speed = 0.1f;
}

void PanningControls::onUpdate(Timestep ts)
{
	// No specific logic needed here for direct panning.
	// The camera's view matrix update is handled by ExampleLayer::onUpdate
	// via m_camera->update().
}

void PanningControls::onEvent(Event &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseMovedEvent>(
		BIND_EVENT_FN(PanningControls::onMouseMoved));
	dispatcher.Dispatch<MouseButtonPressedEvent>(
		BIND_EVENT_FN(PanningControls::onMouseButtonPressed));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(
		BIND_EVENT_FN(PanningControls::onMouseButtonReleased));
}

bool PanningControls::onMouseMoved(MouseMovedEvent &e)
{
	if (m_is_panning) {
		glm::vec2 current_mouse_pos = {e.getX(), e.getY()};
		if (m_last_mouse_pos.x == 0.0f && m_last_mouse_pos.y == 0.0f) {
			m_last_mouse_pos = current_mouse_pos;
			return false;
		}

		glm::vec2 delta = current_mouse_pos - m_last_mouse_pos;
		// ZYKLON_INFO("Moused moved x:{0}, y: {1}", delta.x, delta.y);
		// NEW: Apply trackpad sensitivity factor
		float current_pan_speed = m_pan_speed;

		glm::vec3 camera_right = m_camera->getRight();
		glm::vec3 camera_up = m_camera->getUp();

		glm::vec3 translation = glm::vec3(0.0f);
		translation += -camera_right * delta.x *
					   current_pan_speed; // Use current_pan_speed
		translation +=
			camera_up * delta.y * current_pan_speed; // Use current_pan_speed

		m_camera->setPosition(m_camera->getPosition() + translation);

		m_last_mouse_pos = current_mouse_pos;
		return true;
	}
	return false;
}

bool PanningControls::onMouseButtonPressed(MouseButtonPressedEvent &e)
{
	// ZYKLON_CORE_INFO("Mouse button: {0}", e.getMouseButton());
	if (e.getMouseButton() == ZYKLON_MOUSE_BUTTON_LEFT) {
		m_is_panning = true;
		m_last_mouse_pos = {Input::getMouseX(), Input::getMouseY()};
		return true;
	}
	return false;
}

bool PanningControls::onMouseButtonReleased(MouseButtonReleasedEvent &e)
{
	// weird interaction here but somehow it works :D
	if (m_is_panning) {
		m_is_panning = false;
		m_last_mouse_pos = {0.0f, 0.0f};
		return true;
	}
	return false;
}

void PanningControls::reset()
{
	m_is_panning = false;
	m_last_mouse_pos = {0.0f, 0.0f};
}

} // namespace Zyklon