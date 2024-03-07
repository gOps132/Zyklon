#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__

#include <glm/glm.hpp>

namespace Zyklon {

class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	const glm::vec3& get_position() { return m_position; }
	void set_position(const glm::vec3& p_position) 
	{ 
		m_position = p_position;
		recalculate_view_matrix();
	}

	float get_rotation() const { return m_rotation; }
	void set_rotation(const float p_rotation) {
		m_rotation = p_rotation;
		recalculate_view_matrix();
	}

	const glm::mat4& get_projection_matrix() { return m_projection_matrix; }
	const glm::mat4& get_view_matrix() { return m_view_matrix; }
	const glm::mat4& get_view_projection_matrix() { return m_view_projection_matrix; }

private:

	// This happens when setting the transform, either by setting the position or rotation
	// not optimal if doing every single transform but were going to do it anyway
	void recalculate_view_matrix();

private:
	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_matrix;
	glm::mat4 m_view_projection_matrix;

	glm::vec3 m_position;
	float m_rotation = 0.0f;
};

};

#endif // __ORTHOGRAPHICCAMERA_H__