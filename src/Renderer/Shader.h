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

	virtual void set_uniform_1f(const std::string &name, const float value) = 0;

	virtual void set_uniform_2f(const std::string &name, const float v0, const float v1) = 0;

	virtual void set_uniform_3fv(const std::string &name, const glm::vec3 &buffer) = 0;

	virtual void set_uniform_4fv(const std::string &name, const glm::vec4 &buffer) = 0;

	virtual void set_uniform_matrix_4fv(const std::string &name, const glm::mat4 &buffer) = 0;

	static Shader *create(const std::string &p_filepath);

	static ShaderProgramSource parse_shader(const std::string &p_filePath);
private:
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __SHADER_H__