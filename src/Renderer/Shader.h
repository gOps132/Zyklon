#ifndef __SHADER_H__
#define __SHADER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon {

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
public:
	virtual ~Shader() {}

	virtual void bind() = 0;
	virtual void unbind() = 0;

	static Shader *create(const std::string &p_filepath);

	static ShaderProgramSource parse_shader(const std::string &p_filePath);

	// UNIFORMS

private:
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __SHADER_H__