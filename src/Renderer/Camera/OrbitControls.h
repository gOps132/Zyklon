#ifndef __ORBITCONTROLS_H__
#define __ORBITCONTROLS_H__

#include <zyklon_pch.h>
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

		void set_target(glm::vec3 p_target) { m_target = p_target; }
		void set_camera(std::shared_ptr<Camera> p_camera) { m_camera = p_camera; }
		void set_rotation_speed(float rotation_speed) { m_rotation_speed = rotation_speed; }
		void update(float dx = 0.0f, float dy = 0.0f);
		float& get_distance() { return m_distance; }
	private:
		std::shared_ptr<Camera> m_camera;
		glm::vec3 m_target;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
		float m_rotation_speed = 0.05f;
		float m_distance;
	};
}

#endif // __ORBIT_CONTROLS_H__