#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include <Zyklon/Renderer/Texture.h>
#include <Zyklon/Renderer/Shader.h>

// TODO: shader handling, texture handling, uniform handling etc.
namespace Zyklon {

class Material {
public:
	Material(const Ref<Shader> &p_shader =
				 nullptr); // material is defined by its shader
	virtual ~Material() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	Ref<Shader> getShader() const { return m_shader; }
	virtual void setShader(const Ref<Shader> &p_shader) { m_shader = p_shader; }

	virtual void setFloat(const std::string &p_name, float p_value);
	virtual void setVec3(const std::string &p_name, const glm::vec3 &p_value);
	virtual void setMat4(const std::string &p_name, const glm::mat4 &p_value);

	virtual void renderGUI() {}

protected:
	Ref<Shader> m_shader;
	// store common texture here or specific ones for albedo classes
	// Ref<Texture2D> m_texture;

	// e.g., std::unordered_map<std::string, SomeUniformValueStruct> m_uniforms;

	// TODO: prefetch uniform location for performance
};

} // namespace Zyklon

#endif // __MATERIAL_H__