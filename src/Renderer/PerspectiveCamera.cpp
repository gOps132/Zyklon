#include "Zyklon/zyklon_pch.h"

#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zyklon {

PerspectiveCamera::PerspectiveCamera(float p_fovy, float p_aspect_ratio, float p_near_plane, float p_far_plane)
	:	m_fovy(p_fovy),
		m_aspect_ratio(p_aspect_ratio),
		m_near_plane(p_near_plane),
		m_far_plane(p_far_plane)
{
	m_projection_matrix = glm::perspective(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane);
	m_view_matrix = glm::mat4(1.0f);
	m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void PerspectiveCamera::recalculate_view_matrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
		glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0,0,1));

	// inverse
	m_view_matrix = glm::inverse(transform);
	m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void PerspectiveCamera::recalculate_perspective_matrix(float p_fovy, float p_aspect_ratio, float p_near_plane, float p_far_plane)
{
	m_projection_matrix = glm::perspective(p_fovy, p_aspect_ratio, p_near_plane, p_far_plane);
}


} // namespace Zyklon
