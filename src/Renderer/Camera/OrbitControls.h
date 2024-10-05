#ifndef __ORBITCONTROLS_H__
#define __ORBITCONTROLS_H__

#include <Zyklon/zyklon_pch.h>
#include <Zyklon/Events/Event.h>

#include <glm/glm.hpp>

#include "Camera.h"

namespace Zyklon
{
	/**
	 * Arc ball camera
	*/
	class OrbitControls
	{
	public:
		OrbitControls(std::shared_ptr<Camera> p_camera);

		void set_target(glm::vec3 *p_target) { m_target = p_target; }
		void set_camera(std::shared_ptr<Camera> p_camera) { m_camera = p_camera; }
		// convert the 2d screen coordinates into 3d movement
		glm::vec3 map_to_unit_sphere(float p_mouse_x, float p_mouse_y, float p_width, float p_height);
		/**
		 * vary distance using the scroll wheel events
		 * vary XY and XZ rotation matrices or quaternions using mouse move events
		 * TODO: track the current and previous position of the mouse events
		*/
		void orbit_events(Event p_event);
	private:
		std::shared_ptr<Camera> m_camera;
		glm::vec3 *m_target;
		glm::vec3 m_up_normal;
		glm::mat4 m_yaw;
		glm::mat4 m_pitch;
		float	m_distance;
		// get the pivot point by getting the normal of the camera and the target
	};
}

#endif // __ORBIT_CONTROLS_H__