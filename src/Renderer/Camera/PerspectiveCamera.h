#ifndef __PERSPECTIVECAMERA_H__
#define __PERSPECTIVECAMERA_H__

#include "Camera.h"
#include <glm/glm.hpp>

namespace Zyklon {

/**
 * 
 * 	// Recommended defaults based on common usage:
	float fovY = glm::radians(45.0f); // Field of view in the vertical direction
	float nearPlane = 0.1f;          // Near clipping plane distance
	float farPlane = 100.0f;         // Far clipping plane distance

	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projection = glm::perspective(fovY, aspectRatio, nearPlane, farPlane);
*/

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float p_fovy, float p_aspect_ratio, float p_near_plane, float p_far_plane);

	// This happens when setting the transform, either by setting the position or rotation
	// not optimal if doing every single transform but were going to do it anyway
	virtual void recalculate_view_matrix() override;
	virtual void recalculate_perspective_matrix(float p_fovy, float p_aspect_ratio, float p_near_plane, float p_far_plane) override;
private:
	float m_fovy;
	float m_aspect_ratio;
	float m_near_plane;
	float m_far_plane;
};

};


#endif // __PERSPECTIVECAMERA_H__