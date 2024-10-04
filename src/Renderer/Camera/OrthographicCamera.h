#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__

#include "Camera.h"

#include <glm/glm.hpp>

namespace Zyklon {

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	// This happens when setting the transform, either by setting the position or rotation
	// not optimal if doing every single transform but were going to do it anyway
	virtual void recalculate_view_matrix() override;
};

};

#endif // __ORTHOGRAPHICCAMERA_H__