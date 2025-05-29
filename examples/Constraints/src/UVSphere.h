#ifndef __UVSPHERE_H__
#define __UVSPHERE_H__

#include "Physics.h"

// TODO: Make prototyping objects easier
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <vector>
#include <memory>

class UVSphere : public PObject {
public:
	UVSphere(std::string name, float radius, float mass, glm::vec3 position,
		   glm::vec3 velocity, std::string shader_path);
	void reset();
	void generate(const float radius, const int stacks,
							const int slices);
	void setShader(std::string shader_path);
	void setTexture(const std::string& p_path, int p_slot) 
	{
		m_slot = p_slot;
		m_texture = Zyklon::Texture2D::create(p_path); 
	}

	void updateShader(float time);
	void render(glm::mat4 transform);
	void renderGUI();
	void setResolution(int stacks, int slices)
	{
		m_stacks = stacks;
		m_slices = slices;
	}
	void setModelMatrix(const glm::mat4 &model_matrix)
	{
		m_model_matrix = model_matrix;
	}
	const glm::mat4 &getModelMatrix() const { return m_model_matrix; }
    const Zyklon::Shader& getShader() const { return *m_shader; }
private:
	std::string m_name;
	std::string m_shader_path;

	glm::mat4 m_model_matrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	// sphere resolution
	std::vector<float> m_vertices;
	std::vector<uint32_t> m_indices;

	int m_stacks = 50;
	int m_slices = 50;

	int m_slot = 0;

	//	sphere shader uniforms
	glm::vec3 m_color = {1.0f, 1.0f, 1.0f};
	glm::vec3 m_directional_light_color = {1.0f, 1.0f, 1.0f};
	glm::vec3 m_ambient_light_color = {1.0f, 1.0f, 1.0f};
	float m_ambient_light_intensity = 0.3f;
	glm::vec3 m_stretch = {1.0f, 1.0f, 1.0f};

	std::shared_ptr<Zyklon::Texture2D> m_texture;
	std::shared_ptr<Zyklon::Shader> m_shader;
	std::shared_ptr<Zyklon::VertexBuffer> m_vertex_buffer;
	std::shared_ptr<Zyklon::IndexBuffer> m_index_buffer;
	std::shared_ptr<Zyklon::VertexArray> m_vertex_array;
};

#endif // __UVSPHERE_H__