#include "UVSphere.h"
#include <Zyklon/Core/Log.h>

// UVSphere no longer takes physics parameters in constructor
UVSphere::UVSphere(std::string name) : m_name(name)
{
	// No PObject::reset();
	generate(1.0f, m_stacks,
			 m_slices); // Generate initial mesh data with a default radius
}

// remove reset() as it's now physics-specific
// void UVSphere::reset() { }

void UVSphere::generate(const float radius, const int stacks, const int slices)
{
	// ... (rest of your generate function, it's correct for mesh generation)
	m_vertices.clear();
	m_indices.clear();

	// ZYKLON_INFO("GENERATING SPHERE");
	glm::vec3 normals;

	m_vertices.push_back(0.0f);
	m_vertices.push_back(radius);
	m_vertices.push_back(0.0f);
	//  top normals
	m_vertices.push_back(0.0f);
	m_vertices.push_back(1.0f);
	m_vertices.push_back(0.0f);
	// top uv
	m_vertices.push_back(0.5f);
	m_vertices.push_back(1.0f);

	// middle vertices
	for (int i = 0; i < stacks; ++i) {
		// latitude angle
		float phi = static_cast<float>(i) * glm::pi<float>() /
					static_cast<float>(stacks);
		float y = radius * std::cos(phi);
		float v = 1.0f - static_cast<float>(i) / static_cast<float>(stacks);

		for (int j = 0; j <= slices; ++j) {
			// longhitude angle
			float theta = static_cast<float>(j) * glm::two_pi<float>() /
						  static_cast<float>(slices);
			float x = radius * std::sin(phi) * std::cos(theta);
			float z = radius * std::sin(phi) * std::sin(theta);
			float u = 1.0f - static_cast<float>(j) / static_cast<float>(slices);

			// positions
			m_vertices.push_back(x);
			m_vertices.push_back(y);
			m_vertices.push_back(z);

			// normals
			normals = glm::normalize(glm::vec3(x, y, z));
			m_vertices.push_back(normals.x);
			m_vertices.push_back(normals.y);
			m_vertices.push_back(normals.z);

			// uv coordinates
			m_vertices.push_back(u);
			m_vertices.push_back(v);
		}
	}

	// Add the bottom vertex (south pole)
	m_vertices.push_back(0.0f);	   // x = 0 (centered)
	m_vertices.push_back(-radius); // y = -radius (bottom pole)
	m_vertices.push_back(0.0f);	   // z = 0 (centered)

	// Bottom pole normal (pointing down)
	m_vertices.push_back(0.0f);	 // Normal x
	m_vertices.push_back(-1.0f); // Normal y
	m_vertices.push_back(0.0f);	 // Normal z

	// Bottom UV coordinates (center of texture at bottom pole)
	m_vertices.push_back(0.5f); // u = 0.5 (center)
	m_vertices.push_back(0.0f); // v = 0 (bottom of texture)

	// top stacks indices
	for (int j = 0; j < slices; ++j) {
		// Top stack (triangles connecting the top vertex)
		m_indices.push_back(0);		// Top vertex
		m_indices.push_back(j + 1); // First vertex on the next ring
		m_indices.push_back((j + 1) % slices +
							1); // Wrap around to form a triangle fan
	}

	// Middle stacks
	for (int i = 0; i < stacks - 1;
		 ++i) { // Changed stacks - 2 to stacks - 1 to cover all quads
		for (int j = 0; j < slices; ++j) {
			int first =
				i * (slices + 1) + 1 + j; // Adjusted start index for mid-rings
			int second = first + (slices + 1);

			// First triangle of the quad
			m_indices.push_back(first);
			m_indices.push_back(second);
			m_indices.push_back(first + 1);

			// Second triangle of the quad
			m_indices.push_back(second);
			m_indices.push_back(second + 1);
			m_indices.push_back(first + 1);
		}
	}

	// Bottom stack (triangles connecting the bottom vertex)
	int bottomVertexIndex = static_cast<int>(m_vertices.size() / 8) - 1;
	int start_of_last_ring = (stacks - 1) * (slices + 1) +
							 1; // Correct index for the start of the last ring

	for (int j = 0; j < slices; ++j) {
		m_indices.push_back(bottomVertexIndex);
		m_indices.push_back(start_of_last_ring + j +
							1); // The next vertex on the ring
		m_indices.push_back(start_of_last_ring +
							j); // The current vertex on the ring
	}

	ZYKLON_INFO("Index: {0}, Vertex: {1}", m_indices.size(),
				m_vertices.size() / 8);
}