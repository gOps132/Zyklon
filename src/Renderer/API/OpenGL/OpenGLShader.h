#ifndef __OPENGLSHADER_H__
#define __OPENGLSHADER_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include "Renderer/Shader.h"

namespace Zyklon 
{
class OpenGLShader ZYKLON_OPENGL_FINAL : public Shader {
public:
	OpenGLShader(const std::string &p_filepath);
	~OpenGLShader();

	virtual void setUniform1i(const std::string &name, const int value) override;
	virtual void setUniform1f(const std::string &name, const float v0) override;
	virtual void setUniform2f(const std::string &name, const float v0, const float v1) override;
	virtual void setUniform3fv(const std::string &name, const glm::vec3 &buffer) override;
	virtual void setUniform4fv(const std::string &name, const glm::vec4 &buffer) override;
	virtual void setUniformMatrix4fv(const std::string &name, const glm::mat4 &buffer) override;

	virtual void bind() override;
	virtual void unbind() override;

private:
	// std::vector<ShaderUniform> m_shader_uniforms;
	ShaderProgramSource m_shader_source;
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __OPENGLSHADER_H__