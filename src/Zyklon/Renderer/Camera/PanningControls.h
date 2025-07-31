#ifndef __PANNINGCONTROLS_H__
#define __PANNINGCONTROLS_H__

#include <zyklon_pch.h>

#include <Zyklon/Core/Core.h>
#include <Zyklon/Core/Timestep.h>

#include <Zyklon/Events/MouseEvent.h>

#include "Camera.h"

namespace Zyklon {

class PanningControls {
public:
	PanningControls(Ref<Camera> p_camera);

	void onUpdate(Timestep ts);
	void onEvent(Event &e);

	Ref<Camera> getCamera() { return m_camera; }

	void reset();

	void setPanSpeed(float speed) { m_pan_speed = speed; }
	float getPanSpeed() const { return m_pan_speed; }

private:
	Ref<Camera> m_camera;
	float m_pan_speed = 0.005f; // Base panning speed (can be adjusted)

	bool m_is_panning = false;
	glm::vec2 m_last_mouse_pos; // for delta calculations

	bool onMouseMoved(MouseMovedEvent &e);
	bool onMouseButtonPressed(MouseButtonPressedEvent &e);
	bool onMouseButtonReleased(MouseButtonReleasedEvent &e);
};

} // namespace Zyklon

#endif // __PANNINGCONTROLS_H__