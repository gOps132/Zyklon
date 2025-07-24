#include "BasicLitMaterial.h"

namespace Zyklon {

BasicLitMaterial::BasicLitMaterial(const Ref<Shader> &p_shader,
								   const Ref<Texture2D> &p_texture)
	: Material(p_shader), m_texture(p_texture)
{
	if (m_shader) {
		m_shader->bind();
		m_shader->setUniform1f("u_Texture", m_texture_slot);
		// set initial lighting conditions here too
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

} // namespace Zyklon
