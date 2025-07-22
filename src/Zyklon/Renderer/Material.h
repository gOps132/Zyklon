#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include "Texture.h"
#include "Shader.h"

namespace Zyklon {

	// TODO: shader handling, texture handling, uniform handling etc.
class Material {
public:
	Material(const Ref<Shader>& shader = nullptr, const Ref<Texture2D>& texture = nullptr)
		: m_shader(shader), m_texture(texture) {}
	Material() = default;
	virtual ~Material() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	Ref<Shader> get_shader() const { return m_shader; }
	virtual void set_shader(const Ref<Shader>& shader) {
		m_shader = shader;
	}

	Ref<Texture2D> get_texture() const { return m_texture; }
	virtual void set_texture(const Ref<Texture2D>& texture, int slot = 0) {
		m_texture = texture;
		m_texture->bind(slot);
		if (m_shader) {
			m_shader->setUniform1i("u_Texture", slot);
		}
	}

	void setFloat(const std::string& name, float value);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setMat4(const std::string& name, const glm::mat4& value);

private:
	Ref<Texture2D> m_texture;
	Ref<Shader> m_shader;

	std::unordered_map<std::string, float> m_float_uniforms;
	std::unordered_map<std::string, glm::vec3> m_vec3_uniforms;
	std::unordered_map<std::string, glm::mat4> m_mat4_uniforms;
	std::unordered_map<std::string, std::pair<Ref<Texture2D>, uint32_t>> m_texture_uniforms;

	// TODO: prefetch uniform location for performance
};

} // namespace Zyklon

#endif // __MATERIAL_H__