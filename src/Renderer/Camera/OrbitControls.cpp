#include "OrbitControls.h"

namespace Zyklon
{
	OrbitControls::OrbitControls(std::shared_ptr<Camera> p_camera) :
	m_camera(p_camera) {
		m_distance = 3.0f;
		// m_distance = glm::length(m_target - m_camera->get_position()); // Calculate the distance between camera and target
	}

	void OrbitControls::update(float dx, float dy)
	{
		m_yaw += dx * m_rotation_speed;
		m_pitch  += dy * m_rotation_speed;

		// Constrain pitch to prevent camera flipping
	    m_pitch = glm::clamp(m_pitch, -glm::half_pi<float>(), glm::half_pi<float>());

		// calculate rotation matrices
		glm::mat4 yaw_rotation = glm::rotate(glm::mat4(1.0f), m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 pitch_rotation = glm::rotate(glm::mat4(1.0f), m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));

		glm::vec3 direction = glm::vec3(yaw_rotation * pitch_rotation * glm::vec4(0,0,-1,1));

		// // calculate distance from the camera to the target
		// m_distance = glm::length(m_target - m_camera->get_position());

		// update the camera position 
		glm::vec3 camera_pos = m_target + direction * m_distance;

		// update camera values
		m_camera->look_at(camera_pos, m_target, {0.0f, 1.0f, 0.0f});
	}

/*
	glm::vec3 map_to_unit_sphere(float p_mouse_x, float p_mouse_y, float p_width, float p_height)
	{
		glm::vec3 v;
		v.x = (2.0f * p_mouse_x - p_width) / p_width;
		v.y = (p_height - 2.0f * p_mouse_y) / p_height;
		v.z = 0.0f;

		float length = v.x * v.x + v.y * v.y;

		if (length > 1.0f)
			v =  glm::normalize(v);
		else
			v.z = sqrt(1.0f - length);

		return v;
	}
*/

} // namespace Zyklon