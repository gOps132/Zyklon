#ifndef __ORBITCONTROLS_H__
#define __ORBITCONTROLS_H__

#include <zyklon_pch.h>
#include <Zyklon/Events/Event.h>

#include <Zyklon/Events/Event.h>
#include <Zyklon/Events/MouseEvent.h>
#include <Zyklon/Input/Input.h>

#include <glm/glm.hpp>

#include "Camera.h"

namespace Zyklon {
/**
 * Arc ball camera
 */
class OrbitControls {
public:
	OrbitControls(std::shared_ptr<Camera> p_camera);

	void set_target(glm::vec3 p_target) { m_target = p_target; }
	void set_camera(std::shared_ptr<Camera> p_camera) { m_camera = p_camera; }
	void set_rotation_speed(float rotation_speed)
	{
		m_rotation_speed = rotation_speed;
	}
	void update(float dx = 0.0f,
				float dy = 0.0f); // for explicit calls
	void onUpdate(Timestep ts);	  // For frame-based updates if needed (e.g.,
								  // inertia, smoothing
	void onEvent(Event &event);
	float &get_distance() { return m_distance; }
	void reset();

private:
	bool onMouseMoved(MouseMovedEvent &e);
	bool onMouseScrolled(MouseScrolledEvent &e);
	bool onMouseButtonPressed(MouseButtonPressedEvent &e);
	bool onMouseButtonReleased(MouseButtonReleasedEvent &e);

private:
	std::shared_ptr<Camera> m_camera;
	glm::vec3 m_target;
	float m_yaw = 0.0f;
	float m_pitch = 0.0f;
	float m_rotation_speed = 0.05f;
	float m_zoom_speed = 0.1f; // Speed for mouse scroll zoom
	float m_distance;

	glm::vec2 m_mouse_current = {0.0f, 0.0f};
	glm::vec2 m_mouse_previous = {0.0f, 0.0f};
	bool m_is_mouse_down = false;
};
} // namespace Zyklon

#endif // __ORBIT_CONTROLS_H__