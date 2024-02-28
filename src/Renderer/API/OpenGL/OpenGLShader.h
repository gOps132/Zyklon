#ifndef __OPENGLSHADER_H__
#define __OPENGLSHADER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Shader.h"
#include "Zyklon/Core.h"

namespace Zyklon {
class OpenGLShader ZYKLON_OPENGL_FINAL : public Shader {
public:
	OpenGLShader(const std::string &p_filepath);
	~OpenGLShader();

// TODO: Add more definitions
	virtual void set_uniform_vec_3(const std::string &name, const glm::vec3 &buffer) override;
	virtual void set_uniform_matrix_4fv(const std::string &name, const glm::mat4 &buffer) override;

	virtual void bind() override;
	virtual void unbind() override;

private:
	// std::vector<ShaderUniform> m_shader_uniforms;
	ShaderProgramSource m_shader_source;
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __OPENGLSHADER_H__