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

	virtual void bind() override;
	virtual void unbind() override;

	virtual void set_uniform() override;
private:
	ShaderProgramSource m_shader_source;
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __OPENGLSHADER_H__