#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Zyklon {

class Camera {
public:
	Camera(const std::string p_name = "Camera")
		: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f), m_needs_update(true),
		  m_name(p_name)
	{
	}
	virtual ~Camera() {}

	std::string &getName() { return m_name; }
	void setName(const std::string &p_name) { m_name = p_name; }

	void update()
	{
		// DEBUG
		// ZYKLON_INFO("camera position: {0},{1},{2}", m_position.x,
		// m_position.y, 			m_position.z);
		if (m_needs_update)
			recalculateViewMatrix();
	}
	const glm::vec3 &getPosition() { return m_position; }
	void setPosition(const glm::vec3 &p_position)
	{
		m_needs_update = true;
		m_position = p_position;
	}

	const glm::vec3 &getFront() const { return m_front_direction; }
	const glm::vec3 &getUp() const { return m_up_direction; }

	const glm::vec3 getRight() const
	{
		return glm::normalize(glm::cross(m_front_direction, m_up_direction));
	}

	const glm::vec3 getLeft() const { return -getRight(); }

	float getRotation() const { return m_rotation; }
	void setRotation(const float p_rotation)
	{
		m_needs_update = true;
		m_rotation = p_rotation;
	}
	void lookAt(glm::vec3 p_eye_pos, glm::vec3 p_target_pos,
				glm::vec3 p_world_up)
	{
		m_position = p_eye_pos;

		m_front_direction = glm::normalize(p_target_pos - p_eye_pos);

		// calculate the right vector first then recalculate the up vector
		// to ensure its perfectly orthogonal to the front and right
		glm::vec3 calculated_right =
			glm::normalize(glm::cross(m_front_direction, p_world_up));
		m_up_direction =
			glm::normalize(glm::cross(calculated_right, m_front_direction));

		recalculateViewMatrix();

		// Set the update flag if needed
		m_needs_update = false;
	}

	const glm::mat4 &getProjectionMatrix() { return m_projection_matrix; }
	const glm::mat4 &getViewMatrix() { return m_view_matrix; }
	const glm::mat4 &getViewProjectionMatrix()
	{
		return m_view_projection_matrix;
	}

	// TRACK ORIENTATION

	// This happens when setting the transform, either by setting the position
	// or rotation not optimal if doing every single transform but were going to
	// do it anyway
	virtual void recalculateViewMatrix() = 0;
	virtual void recalculatePerspectiveMatrix(float p_fovy,
											  float p_aspect_ratio,
											  float p_near_plane,
											  float p_far_plane) = 0;

public:
	std::string m_name;

protected:
	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_matrix;
	glm::mat4 m_view_projection_matrix;

	glm::vec3 m_position;
	glm::vec3 m_front_direction;
	glm::vec3 m_up_direction;

	float m_rotation = 0.0f;
	bool m_needs_update = true;
};

} // namespace Zyklon

#endif // __CAMERA_H__