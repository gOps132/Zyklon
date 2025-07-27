#ifndef __PHYSICSCOMPONENT_H__
#define __PHYSICSCOMPONENT_H__

#include <zyklon_pch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

namespace Zyklon {

class PhysicsComponent : public Component {
public:
	PhysicsComponent(float p_mass = 1.0f, glm::vec3 &p_position,
					 glm::vec3 &p_velocity);
	virtual ~PhysicsComponent() = default;

private:
	float m_mass = 1.0f;
	glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_velocity = {0.0f, 0.0f, 0.0f};
};

} // namespace Zyklon

#endif // __PHYSICSCOMPONENT_H__