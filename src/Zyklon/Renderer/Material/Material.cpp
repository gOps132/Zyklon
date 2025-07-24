#include "Material.h"

namespace Zyklon {

Material::Material(const Ref<Shader> &p_shader) : m_shader(p_shader) {}

void Material::setFloat(const std::string &p_name, float p_value)
{
	if (m_shader) {
		m_shader->bind();
		m_shader->setUniform1f(p_name.c_str(), p_value);
		m_shader->unbind();
	}
}

void Material::setVec3(const std::string &name, const glm::vec3 &p_value)
{
	if (m_shader) {
		m_shader->bind();
		m_shader->setUniform3fv(name.c_str(), p_value);
		m_shader->unbind();
	}
}

void Material::setMat4(const std::string &p_name, const glm::mat4 &p_value)
{
	if (m_shader) {
		m_shader->bind();
		m_shader->setUniformMatrix4fv(p_name.c_str(), p_value);
		m_shader->unbind();
	}
}

} // namespace Zyklon