#ifndef __SHADER_H__
#define __SHADER_H__

#include <zyklon_pch.h>

#include <glm/gtc/type_ptr.hpp>

#include "Buffer.h"

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

	virtual void setUniform1i(const std::string &name, const int value) = 0;

	virtual void setUniform1f(const std::string &name, const float value) = 0;

	virtual void setUniform2f(const std::string &name, const float v0, const float v1) = 0;

	virtual void setUniform3fv(const std::string &name, const glm::vec3 &buffer) = 0;

	virtual void setUniform4fv(const std::string &name, const glm::vec4 &buffer) = 0;

	virtual void setUniformMatrix4fv(const std::string &name, const glm::mat4 &buffer) = 0;

	static Shader *create(const std::string &p_filepath);

	static ShaderProgramSource parseShader(const std::string &p_filePath);
private:
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __SHADER_H__