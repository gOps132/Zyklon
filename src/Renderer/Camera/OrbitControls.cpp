#include "OrbitControls.h"

namespace Zyklon
{
	OrbitControls::OrbitControls(std::shared_ptr<Camera> p_camera) :
	m_camera(p_camera) {
		m_distance = 3.0f;
		// m_distance = glm::length(m_target - m_camera->getPosition()); // Calculate the distance between camera and target
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
		// Calculate the "right" vector from direction
		glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));

		// Dynamically calculate the "up" vector
		glm::vec3 up = glm::normalize(glm::cross(right, direction));

		// update the camera position 
		glm::vec3 camera_pos = m_target + direction * m_distance;

		// update camera values
		m_camera->look_at(camera_pos, m_target, up);
	}

} // namespace Zyklon