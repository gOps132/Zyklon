#include "OrbitControls.h"

namespace Zyklon
{
	OrbitControls::OrbitControls(std::shared_ptr<Camera> p_camera) :
	m_camera(p_camera) {}

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

	
} // namespace Zyklon