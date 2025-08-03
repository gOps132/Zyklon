#ifndef __BASICLITMATERIAL_H__
#define __BASICLITMATERIAL_H__

#include "Material.h"

namespace Zyklon {

class BasicLitMaterial : public Material {
public:
	BasicLitMaterial(const Ref<Shader> &p_shader,
					 const Ref<Texture2D> &p_texture = nullptr);

	virtual void bind() const override;
	virtual void unbind() const override;

	// Specific setters for this material's common properties
	void setColor(glm::vec3 &p_color) { m_color = p_color; }
	const glm::vec3 &getColor() { return m_color; }

	Ref<Texture2D> getTexture() const { return m_texture; }
	void setTexture(const Ref<Texture2D> &p_texture, uint32_t p_slot)
	{
		m_texture = p_texture;
		m_texture_slot = p_slot;
	}

	void setDirectionalLightDirection(glm::vec3 &p_direction)
	{
		m_directional_light_direction = p_direction;
	}
	void setDirectionalLightColor(glm::vec3 &p_color)
	{
		m_directional_light_color = p_color;
	}
	void setAmbientLightItensity(float p_intensity)
	{
		m_ambient_light_intensity = p_intensity;
	}
	void setAmbientLightColor(glm::vec3 &p_color)
	{
		m_ambient_light_color = p_color;
	}

	virtual void renderGUI() override;

private:
	glm::vec3 m_color = {1.0f, 1.0f, 1.0f}; // default color
	Ref<Texture2D> m_texture;
	uint32_t m_texture_slot;

	// lighting properties
	glm::vec3 m_directional_light_direction = {0.0f, -1.0f, 0.0f}; // from above
	glm::vec3 m_directional_light_color = {1.0f, 1.0f, 1.0f};
	glm::vec3 m_ambient_light_color = {1.0f, 1.0f, 1.0f};
	float m_ambient_light_intensity = 1.0f;
};

} // namespace Zyklon

#endif // __BASICLITMATERIAL_H__