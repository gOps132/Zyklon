// ./Renderer/Camera/PerspectiveCamera.cpp

#include <zyklon_pch.h>

#include <glm/gtc/matrix_transform.hpp>

#include "PerspectiveCamera.h"

namespace Zyklon {

PerspectiveCamera::PerspectiveCamera(float p_fovy, float p_aspect_ratio,
									 float p_near_plane, float p_far_plane)
	: m_fovy(p_fovy), m_aspect_ratio(p_aspect_ratio),
	  m_near_plane(p_near_plane), m_far_plane(p_far_plane)
{
	m_projection_matrix =
		glm::perspective(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane);
	// Initializing view matrix to identity is fine, it will be updated by
	// lookAt
	m_view_matrix = glm::mat4(1.0f);
	m_view_projection_matrix = m_projection_matrix * m_view_matrix;

	// Initialize direction vectors to something sensible if not using lookAt
	// immediately Or, ensure lookAt is called right after construction with an
	// initial position and target. For orbit camera, the OrbitControls
	// constructor will call lookAt during its update.
	m_front_direction = glm::vec3(0.0f, 0.0f, -1.0f); // Default forward
	m_up_direction = glm::vec3(0.0f, 1.0f, 0.0f);	  // Default up
}

void PerspectiveCamera::recalculateViewMatrix()
{
	// Use glm::lookAt to construct the view matrix from position, target
	// (position + front), and up vector.
	m_view_matrix =
		glm::lookAt(m_position, m_position + m_front_direction, m_up_direction);
	m_view_projection_matrix = m_projection_matrix * m_view_matrix;
	m_needs_update = false; // Reset update flag after recalculating
}

void PerspectiveCamera::recalculatePerspectiveMatrix(float p_fovy,
													 float p_aspect_ratio,
													 float p_near_plane,
													 float p_far_plane)
{
	m_projection_matrix =
		glm::perspective(p_fovy, p_aspect_ratio, p_near_plane, p_far_plane);
	// Update view-projection matrix too, as projection changed
	m_view_projection_matrix =
		m_projection_matrix * m_view_matrix; // <--- ADDED
}

} // namespace Zyklon