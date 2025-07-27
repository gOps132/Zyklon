#include "UVSphere.h"

// No longer needs Renderer.h or imgui.h here as it's not directly rendering or
// having its own GUI
#define _USE_MATH_DEFINES
#include <math.h>

#include <Zyklon/Core/Log.h>

UVSphere::UVSphere(std::string name, float radius, float mass,
				   glm::vec3 position, glm::vec3 velocity)
	: PObject(mass, radius, position, velocity), m_name(name)
{
	reset();
	generate(radius, m_stacks, m_slices); // Generate initial mesh data
}

void UVSphere::reset()
{
	PObject::reset(); // Call base class reset
					  // No rendering specific members to reset here
}

void UVSphere::generate(const float radius, const int stacks, const int slices)
{
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

			// ZYKLON_INFO("VERTICE: {0}, STACK: {1}, SLICE: {2}, x: {3:.2f}, y:
			// {4:.2f}, z: {5:.2f}", 	i*stacks + j, i, j, x,y,z);

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
		// m_indices.push_back(j + 2);                // Next vertex on the next
		// ring m_indices.push_back(j == slices - 1 ? 1 : j + 2);
		m_indices.push_back((j + 1) % slices + 1);
	}

	// Middle stacks
	for (int i = 0; i < stacks - 2; ++i) {
		for (int j = 0; j < slices; ++j) {
			int first = i * (slices + 1) + (j + 1);
			int second = first + slices + 1;

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
	int start = (stacks - 2) * (slices + 1) +
				1; // First vertex of the bottom-most stack

	for (int j = 0; j < slices; ++j) {
		m_indices.push_back(bottomVertexIndex);			 // Bottom pole
		m_indices.push_back(start + j);					 // Current slice
		m_indices.push_back(start + ((j + 1) % slices)); // Wrap to first slice
	}

	ZYKLON_INFO("Index: {0}, Vertex: {1}, Normal: ({2}, {3}, {4})",
				m_indices.size(), m_vertices.size() / 8, normals.x, normals.y,
				normals.z);
}