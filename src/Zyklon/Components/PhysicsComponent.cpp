#include "PhysicsComponent.h"

namespace Zyklon {

PhysicsComponent::PhysicsComponent(float p_mass, glm::vec3 &p_position,
								   glm::vec3 &p_velocity)
	: Component("Physics Component"), m_mass(p_mass), m_velocity(p_velocity)
{
}
} // namespace Zyklon