#ifndef __UVSPHERE_H__
#define __UVSPHERE_H__

#include "Physics.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <memory>

class UVSphere : public PObject {
public:
	// Constructor now simplified, as it doesn't directly manage shader/texture
	// paths
	UVSphere(std::string name, float radius, float mass, glm::vec3 position,
			 glm::vec3 velocity);

	void reset();
	void generate(const float radius, const int stacks, const int slices);

	// Getters for mesh data
	const std::vector<float> &getVertices() const { return m_vertices; }
	const std::vector<uint32_t> &getIndices() const { return m_indices; }

	// Accessors for generation parameters
	int getStacks() const { return m_stacks; }
	int getSlices() const { return m_slices; }
	void setResolution(int stacks, int slices)
	{
		m_stacks = stacks;
		m_slices = slices;
	}

private:
	std::string m_name;

	// Sphere resolution
	std::vector<float> m_vertices;
	std::vector<uint32_t> m_indices;

	int m_stacks = 50;
	int m_slices = 50;
};

#endif // __UVSPHERE_H__