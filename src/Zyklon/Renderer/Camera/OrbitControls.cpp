#include <Zyklon/Core/Timestep.h>
#include <Zyklon/Input/MouseButtonCodes.h>

#include "OrbitControls.h"

namespace Zyklon {
OrbitControls::OrbitControls(std::shared_ptr<Camera> p_camera)
	: m_camera(p_camera)
{
	m_distance = 3.0f;
	// m_distance = glm::length(m_target - m_camera->getPosition()); //
	// Calculate the distance between camera and target
}

void OrbitControls::update(float dx, float dy)
{
	m_yaw += dx * m_rotation_speed;
	m_pitch += dy * m_rotation_speed;

	// Constrain pitch to prevent camera flipping
	m_pitch =
		glm::clamp(m_pitch, -glm::half_pi<float>(), glm::half_pi<float>());

	// calculate rotation matrices
	glm::mat4 yaw_rotation =
		glm::rotate(glm::mat4(1.0f), m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 pitch_rotation =
		glm::rotate(glm::mat4(1.0f), m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::vec3 direction =
		glm::vec3(yaw_rotation * pitch_rotation * glm::vec4(0, 0, -1, 1));
	// Calculate the "right" vector from direction
	glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));

	// Dynamically calculate the "up" vector
	glm::vec3 up = glm::normalize(glm::cross(right, direction));

	// update the camera position
	glm::vec3 camera_pos = m_target + direction * m_distance;

	// update camera values
	m_camera->lookAt(camera_pos, m_target, up);
}

void OrbitControls::onUpdate(Timestep ts)
{
	// This can be used for things like camera smoothing, or if movement is
	// time-based. For direct mouse input, the main `update` function is called
	// from `onEvent`. If you want inertia/damping, implement it here.

	update();
}

void OrbitControls::onEvent(Event &event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseMovedEvent>(
		BIND_EVENT_FN(OrbitControls::onMouseMoved));
	dispatcher.Dispatch<MouseScrolledEvent>(
		BIND_EVENT_FN(OrbitControls::onMouseScrolled));
	dispatcher.Dispatch<MouseButtonPressedEvent>(
		BIND_EVENT_FN(OrbitControls::onMouseButtonPressed));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(
		BIND_EVENT_FN(OrbitControls::onMouseButtonReleased));
}

bool OrbitControls::onMouseMoved(MouseMovedEvent &e)
{
	m_mouse_current = {e.getX(), e.getY()};
	if (m_is_mouse_down) {
		glm::vec2 delta = m_mouse_current - m_mouse_previous;
		update(delta.x, -delta.y); // Negative dy because screen Y is inverted
	}
	m_mouse_previous = m_mouse_current;
	return m_is_mouse_down; // Event is handled if mouse is down and moving
}

bool OrbitControls::onMouseScrolled(MouseScrolledEvent &e)
{
	float scroll_delta = e.getYOffset();
	m_distance -= scroll_delta * m_zoom_speed;
	m_distance =
		glm::max(m_distance, 1.0f); // Prevent zooming inside the target
	update();						// Update camera after zoom
	return true;					// Event handled
}

bool OrbitControls::onMouseButtonPressed(MouseButtonPressedEvent &e)
{
	if (e.getMouseButton() ==
		ZYKLON_MOUSE_BUTTON_LEFT) { // Assuming left click for rotation
		m_is_mouse_down = true;
		m_mouse_previous = m_mouse_current; // Capture current mouse position
		return true;						// Event handled
	}
	return false;
}

bool OrbitControls::onMouseButtonReleased(MouseButtonReleasedEvent &e)
{
	if (e.getMouseButton() == ZYKLON_MOUSE_BUTTON_LEFT) {
		m_is_mouse_down = false;
		return true; // Event handled
	}
	return false;
}

void OrbitControls::reset()
{
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	// m_distance = 200.0f;		   // Reset to default distance
	m_target = {0.0f, 0.0f, 0.0f}; // Reset target
	m_is_mouse_down = false;	   // Ensure mouse state is reset
	update();					   // Update the camera position after resetting
}

} // namespace Zyklon