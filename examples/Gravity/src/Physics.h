#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "PhysicsConstants.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <memory>

class PObject
{
public:
    PObject(float mass, glm::vec3& position, glm::vec3& velocity)
        : m_mass(mass), m_initial_position(position), m_initial_velocity(velocity) { reset(); }

	void set_mass(float mass) { m_mass = mass; }
	void set_position(const glm::vec3& position) { m_position = position; }
	void set_velocity(const glm::vec3& velocity) { m_velocity = velocity; }
	void set_initial_position(const glm::vec3& position) { m_initial_position = position; }
	void set_initial_velocity(const glm::vec3& velocity) { m_initial_velocity = velocity; }

	float get_mass() const { return m_mass; }
 	const glm::vec3& get_velocity() { return m_velocity; }
	const glm::vec3& get_position() { return m_position; }

	void reset()
	{
		m_position = m_initial_position;
		m_velocity = m_initial_velocity;
	}
protected:
	float m_mass;
	glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_velocity = {0.0f, 0.0f, 0.0f};

	glm::vec3 m_initial_position = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_initial_velocity = {0.0f, 0.0f, 0.0f};
};

class SystemState
{
public:
	SystemState() {};
	// integrates and updates values of physical objects
	void update_system_state(float ts);
	void ode_solve_euler(float ts);
	void add_physical_object(const std::shared_ptr<PObject>& p_object);
	void set_fixed_timestep(float ts) { m_fixed_timestep = ts; }
	std::vector<std::shared_ptr<PObject>>& get_physical_objects() { return m_physical_objects; }
private:
	std::vector<std::shared_ptr<PObject>> m_physical_objects;
	float m_fixed_timestep = 0.001f;
	float m_accumulated_time = 0.0f;
};


#endif // __PHYSICS_H__