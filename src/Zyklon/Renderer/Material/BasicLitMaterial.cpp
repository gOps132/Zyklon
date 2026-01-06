#include "BasicLitMaterial.h"

#include <imgui-test/imgui.h>

namespace Zyklon {

BasicLitMaterial::BasicLitMaterial(const Ref<Shader> &p_shader,
								   const Ref<Texture2D> &p_texture)
	: Material(p_shader), m_texture(p_texture), m_texture_slot(0)
{
	if (m_shader) {
		m_shader->bind();
		m_shader->setUniform1i("u_Texture", m_texture_slot);
		// Set default lighting uniforms
		m_shader->setUniform3fv("u_DirectionalLightDirection", m_directional_light_direction);
		m_shader->setUniform3fv("u_DirectionalLightColor", m_directional_light_color);
		m_shader->setUniform3fv("u_AmbientLightColor", m_ambient_light_color);
		m_shader->setUniform1f("u_AmbientLightIntensity", m_ambient_light_intensity);
		m_shader->unbind();
	}
}

void BasicLitMaterial::bind() const
{
	if (m_shader) {
		m_shader->bind();
		m_shader->setUniform3fv("u_Color", m_color);
		if (m_texture) {
			m_texture->bind(m_texture_slot);
			m_shader->setUniform1i("u_Texture", m_texture_slot);
		}
		else {
			// optional, bind default texture or set a flag in shader
		}

		// Set lighting uniforms (pulled from UVSphere)
		m_shader->setUniform3fv("u_DirectionalLightDirection",
								m_directional_light_direction);
		m_shader->setUniform3fv("u_DirectionalLightColor",
								m_directional_light_color);
		m_shader->setUniform3fv("u_AmbientLightColor", m_ambient_light_color);
		m_shader->setUniform1f("u_AmbientLightIntensity",
							   m_ambient_light_intensity);
	}
}

void BasicLitMaterial::unbind() const
{
	if (m_shader) {
		m_shader->unbind();
		if (m_texture) {
			m_texture->unbind(m_texture_slot);
		}
	}
}

void BasicLitMaterial::renderGUI()
{
	if (ImGui::CollapsingHeader("Basic Lit Material")) {
		ImGui::ColorPicker3("Color", glm::value_ptr(m_color));
		ImGui::ColorPicker3("Ambient Light Color",
							glm::value_ptr(m_ambient_light_color));
		ImGui::SliderFloat("Ambient Light Intensity",
						   &m_ambient_light_intensity, 0.0f,
						   10.0f); // Adjust max as needed
		ImGui::ColorPicker3("Directional Light Color",
							glm::value_ptr(m_directional_light_color));
		ImGui::DragFloat3("Directional Light Direction",
						  glm::value_ptr(m_directional_light_direction), 0.01f,
						  -1.0f,
						  1.0f); // Or use sliders for x,y,z individually
	}
}

} // namespace Zyklon
