#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Zyklon
{

class Camera
{
public:
	virtual ~Camera() {}

	void update() {
		if (m_needs_update)
			recalculate_view_matrix();
	}
	const glm::vec3& getPosition() { return m_position; }
	void setPosition(const glm::vec3& p_position) 
	{ 
		m_needs_update = true;
		m_position = p_position;
	}

	float get_rotation() const { return m_rotation; }
	void set_rotation(const float p_rotation) 
	{
		m_needs_update = true;
		m_rotation = p_rotation;
	}
	void look_at(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
	{
		m_view_matrix = glm::lookAt(position, direction, up);
		m_view_projection_matrix = m_projection_matrix * m_view_matrix;
		
		// Set the update flag if needed
		m_needs_update = false;
	}

	const glm::mat4& get_projection_matrix() { return m_projection_matrix; }
	const glm::mat4& get_view_matrix() { return m_view_matrix; }
	const glm::mat4& get_view_projection_matrix() { return m_view_projection_matrix; }

	// This happens when setting the transform, either by setting the position or rotation
	// not optimal if doing every single transform but were going to do it anyway
	virtual void recalculate_view_matrix() = 0;
	virtual void recalculate_perspective_matrix(float p_fovy, float p_aspect_ratio, float p_near_plane, float p_far_plane) = 0;
public:
	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_matrix;
	glm::mat4 m_view_projection_matrix;

	glm::vec3 m_position;
	float m_rotation = 0.0f;
	bool m_needs_update = true;
};

} // namespace Zyklon

#endif // __CAMERA_H__