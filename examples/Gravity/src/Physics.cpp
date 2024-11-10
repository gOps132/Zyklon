#include "Physics.h"

void SystemState::ode_solve_euler(float ts)
{
	// Calculate forces between each pair of objects
	std::vector<glm::vec3> forces(m_physical_objects.size(), glm::vec3(0.0f));

	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		for (size_t j = i + 1; j < m_physical_objects.size(); ++j) {
			PObject* obj1 = m_physical_objects[i].get();
			PObject* obj2 = m_physical_objects[j].get();

			glm::vec3 direction = obj2->get_position() - obj1->get_position();
			float distance = glm::length(direction);
			if (distance == 0) continue; // Prevent division by zero

			glm::vec3 unit_direction = glm::normalize(direction);

			// USING GRAVITATIONAL CONSTANT!!! NOT VIABLE FOR MEAGER EULER INTEGRATION
			// float force_magnitude = (G * obj1->get_mass() * obj2->get_mass()) / (distance * distance);
			float force_magnitude = (1 * obj1->get_mass() * obj2->get_mass()) / (distance * distance);

			glm::vec3 force = force_magnitude * unit_direction;

			// Newton's Third Law: obj1 exerts a force on obj2 and vice versa
			forces[i] += force;
			forces[j] -= force;
		}
	}

	// Update each object's velocity and position
	for (size_t i = 0; i < m_physical_objects.size(); ++i) {
		PObject* obj = m_physical_objects[i].get();
		glm::vec3 acceleration = forces[i] / obj->get_mass();

		// Update velocity: v_new = v_current + a * ts
		glm::vec3 new_velocity = obj->get_velocity() + acceleration * ts;
		obj->set_velocity(new_velocity);

		// Update position: x_new = x_current + v_new * ts
		glm::vec3 new_position = obj->get_position() + new_velocity * ts;
		obj->set_position(new_position);
	}
}

void SystemState::add_physical_object(const std::shared_ptr<PObject>& p_object)
{
	m_physical_objects.push_back(p_object); 
}
