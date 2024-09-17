#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Zyklon
{

class Camera
{
public:
	virtual ~Camera() {}

	const glm::vec3& get_position() { return m_position; }
	void set_position(const glm::vec3& p_position) 
	{ 
		m_position = p_position;
		recalculate_view_matrix();
	}

	float get_rotation() const { return m_rotation; }
	void set_rotation(const float p_rotation) 
	{
		m_rotation = p_rotation;
		recalculate_view_matrix();
	}
	void look_at(glm::vec3 direction, glm::vec3 up)
	{
		m_view_matrix = glm::lookAt(m_position, direction, up);
	}

	const glm::mat4& get_projection_matrix() { return m_projection_matrix; }
	const glm::mat4& get_view_matrix() { return m_view_matrix; }
	const glm::mat4& get_view_projection_matrix() { return m_view_projection_matrix; }

	// This happens when setting the transform, either by setting the position or rotation
	// not optimal if doing every single transform but were going to do it anyway
	virtual void recalculate_view_matrix() = 0;

public:
	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_matrix;
	glm::mat4 m_view_projection_matrix;

	glm::vec3 m_position;
	float m_rotation = 0.0f;
 };

} // namespace Zyklon

#endif // __CAMERA_H__