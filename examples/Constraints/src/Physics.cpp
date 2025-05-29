#include "Physics.h"

#include <memory>

void SystemState::update_system_state(float ts)
{
	m_accumulated_time += ts;
	while (m_accumulated_time > m_fixed_timestep) {
		// ode_solve_euler(m_fixed_timestep);
		// ode_solve_rk2(m_fixed_timestep);
		ode_solve_rk4(m_fixed_timestep);
		m_accumulated_time -= m_fixed_timestep;
	}
}

bool SystemState::check_collision(const std::shared_ptr<PObject> &obj1,
								  const std::shared_ptr<PObject> &obj2)
{
	float distance = glm::length(obj1->getPosition() - obj2->getPosition());
	float radius_sum = obj1->getRadius() + obj2->getRadius();
	return distance < radius_sum;
}

void SystemState::resolve_collision(const std::shared_ptr<PObject> &obj1,
									const std::shared_ptr<PObject> &obj2)
{
	glm::vec3 direction = obj2->getPosition() - obj1->getPosition();
	float distance = glm::length(direction);
	glm::vec3 unit_direction = glm::normalize(direction);

	// Calculate the overlap
	float overlap = (obj1->getRadius() + obj2->getRadius()) - distance;

	// Separate the spheres
	obj1->setPosition(obj1->getPosition() -
					   unit_direction * (overlap / 2.0f));
	obj2->setPosition(obj2->getPosition() +
					   unit_direction * (overlap / 2.0f));

	// Calculate relative velocity
	glm::vec3 relative_velocity = obj2->getVelocity() - obj1->getVelocity();
	float velocity_along_normal = glm::dot(relative_velocity, unit_direction);

	// Calculate restitution (elasticity)
	float restitution = 1.0f; // Adjust as needed

	// Calculate impulse scalar
	float impulse_scalar = -(1.0f + restitution) * velocity_along_normal;
	impulse_scalar /= (1.0f / obj1->getMass() + 1.0f / obj2->getMass());

	// Apply impulse
	glm::vec3 impulse = impulse_scalar * unit_direction;
	obj1->setVelocity(obj1->getVelocity() - impulse / obj1->getMass());
	obj2->setVelocity(obj2->getVelocity() + impulse / obj2->getMass());
}

void SystemState::ode_solve_euler(float ts)
{
	// Calculate forces between each pair of objects
	std::vector<glm::vec3> forces(m_physical_objects.size(), glm::vec3(0.0f));

	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		for (size_t j = i + 1; j < m_physical_objects.size(); ++j) {
			PObject *obj1 = m_physical_objects[i].get();
			PObject *obj2 = m_physical_objects[j].get();

			glm::vec3 direction = obj2->getPosition() - obj1->getPosition();
			float distance = glm::length(direction);
			if (distance == 0)
				continue; // Prevent division by zero

			glm::vec3 unit_direction = glm::normalize(direction);

			// USING GRAVITATIONAL CONSTANT!!! NOT VIABLE FOR MEAGER EULER
			// INTEGRATION float force_magnitude = (G * obj1->getMass() *
			// obj2->getMass()) / (distance * distance);
			float force_magnitude = (1 * obj1->getMass() * obj2->getMass()) /
									(distance * distance);

			glm::vec3 force = force_magnitude * unit_direction;

			// Newton's Third Law: obj1 exerts a force on obj2 and vice versa
			forces[i] += force;
			forces[j] -= force;
		}
	}

	// Update each object's velocity and position
	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		PObject *obj = m_physical_objects[i].get();
		glm::vec3 acceleration = forces[i] / obj->getMass();

		// Update velocity: v_new = v_current + a * ts
		glm::vec3 new_velocity = obj->getVelocity() + acceleration * ts;
		obj->setVelocity(new_velocity);

		// Update position: x_new = x_current + v_new * ts
		glm::vec3 new_position = obj->getPosition() + new_velocity * ts;
		obj->setPosition(new_position);
	}
}

void SystemState::ode_solve_rk2(float ts)
{
	// Calculate forces between each pair of objects
	std::vector<glm::vec3> forces(m_physical_objects.size(), glm::vec3(0.0f));

	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		for (size_t j = i + 1; j < m_physical_objects.size(); ++j) {
			PObject *obj1 = m_physical_objects[i].get();
			PObject *obj2 = m_physical_objects[j].get();

			glm::vec3 direction = obj2->getPosition() - obj1->getPosition();
			float distance = glm::length(direction);
			if (distance == 0)
				continue; // Prevent division by zero

			glm::vec3 unit_direction = glm::normalize(direction);

			// USING GRAVITATIONAL CONSTANT!!! NOT VIABLE FOR MEAGER EULER
			// INTEGRATION float force_magnitude = (G * obj1->getMass() *
			// obj2->getMass()) / (distance * distance);
			float force_magnitude = (1 * obj1->getMass() * obj2->getMass()) /
									(distance * distance);

			glm::vec3 force = force_magnitude * unit_direction;

			// Newton's Third Law: obj1 exerts a force on obj2 and vice versa
			forces[i] += force;
			forces[j] -= force;
		}
	}

	// 2nd order formula  new_velocity = current_velocity + ts * full_step((full
	// step) /  2, ts), ts);
	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		PObject *obj = m_physical_objects[i].get();
		glm::vec3 acceleration = forces[i] / obj->getMass();

		glm::vec3 vf1 = obj->getVelocity() + acceleration * ts;
		glm::vec3 vf2 = vf1 / 2.0f;

		glm::vec3 new_velocity = obj->getVelocity() + (vf2 - vf1) * ts;

		glm::vec3 pf1 = obj->getPosition() + new_velocity * ts;
		glm::vec3 pf2 = pf1 / 2.0f;

		glm::vec3 new_position = obj->getPosition() + (pf2 - pf1) * ts;

		obj->setVelocity(new_velocity);
		obj->setPosition(new_position);
	}
}

void SystemState::ode_solve_rk4(float ts)
{
	// Calculate forces between each pair of objects
	std::vector<glm::vec3> forces(m_physical_objects.size(), glm::vec3(0.0f));

	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		for (size_t j = i + 1; j < m_physical_objects.size(); ++j) {
			PObject *obj1 = m_physical_objects[i].get();
			PObject *obj2 = m_physical_objects[j].get();

			glm::vec3 direction = obj2->getPosition() - obj1->getPosition();
			float distance = glm::length(direction);
			if (distance == 0)
				continue; // Prevent division by zero

			glm::vec3 unit_direction = glm::normalize(direction);

			// USING GRAVITATIONAL CONSTANT!!! NOT VIABLE FOR MEAGER EULER
			// INTEGRATION float force_magnitude = (G * obj1->getMass() *
			// obj2->getMass()) / (distance * distance);
			float force_magnitude = (1 * obj1->getMass() * obj2->getMass()) /
									(distance * distance);

			glm::vec3 force = force_magnitude * unit_direction;

			// Newton's Third Law: obj1 exerts a force on obj2 and vice versa
			forces[i] += force;
			forces[j] -= force;

			// Check and resolve collision
			if (check_collision(m_physical_objects[i], m_physical_objects[j])) {
				resolve_collision(m_physical_objects[i], m_physical_objects[j]);
			}
		}
	}

	// rk4 integration
	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		PObject *obj = m_physical_objects[i].get();

		glm::vec3 k1_v = forces[i] / obj->getMass() * ts;
		glm::vec3 k1_p = obj->getVelocity() * ts;

		glm::vec3 k2_v = (forces[i] / obj->getMass() + k1_v / 2.0f) * ts;
		glm::vec3 k2_p = (obj->getVelocity() + k1_v / 2.0f) * ts;

		glm::vec3 k3_v = (forces[i] / obj->getMass() + k2_v / 2.0f) * ts;
		glm::vec3 k3_p = (obj->getVelocity() + k2_v / 2.0f) * ts;

		glm::vec3 k4_v = (forces[i] / obj->getMass() + k3_v) * ts;
		glm::vec3 k4_p = (obj->getVelocity() + k3_v) * ts;

		glm::vec3 new_velocity =
			obj->getVelocity() +
			(k1_v + 2.0f * k2_v + 2.0f * k3_v + k4_v) / 6.0f;
		glm::vec3 new_position =
			obj->getPosition() +
			(k1_p + 2.0f * k2_p + 2.0f * k3_p + k4_p) / 6.0f;

		obj->setVelocity(new_velocity);
		obj->setPosition(new_position);
	}
}

void SystemState::add_physical_object(const std::shared_ptr<PObject> &p_object)
{
	m_physical_objects.push_back(p_object);
}
