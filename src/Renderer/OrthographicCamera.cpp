#include "Zyklon/zyklon_pch.h"

#include  "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zyklon {

OrthographicCamera::OrthographicCamera(float p_left, float p_right, float p_bottom, float p_top)
{
	m_projection_matrix = glm::ortho(p_left, p_right, p_bottom, p_top, -1.0f, 1.0f);
	m_view_matrix = glm::mat4(1.0f);
	m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void OrthographicCamera::recalculate_view_matrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
		glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0,0,1));

	// inverse
	m_view_matrix = glm::inverse(transform);
	m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}


} // namespace Zyklon
