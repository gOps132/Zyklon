#ifndef __SHADER_H__
#define __SHADER_H__

#include "Zyklon/zyklon_pch.h"

#include "Buffer.h"
#include "glm/gtc/type_ptr.hpp"

namespace Zyklon {

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

// struct ShaderUniform {
// 	ShaderDataType type;
// 	std::string name;
// 	// ptr to glm value
// 	float buffer;

// 	ShaderUniform(ShaderDataType p_type, const std::string &p_name, const float &buffer);
// };

class Shader {
public:
	virtual ~Shader() {}

	virtual void bind() = 0;
	virtual void unbind() = 0;

	virtual void set_uniform_1f(const std::string &name, const float value) = 0;

	virtual void set_uniform_2f(const std::string &name, const float v0, const float v1) = 0;

	virtual void set_uniform_3fv(const std::string &name, const glm::vec3 &buffer) = 0;
	
	virtual void set_uniform_matrix_4fv(const std::string &name, const glm::mat4 &buffer) = 0;

	static Shader *create(const std::string &p_filepath);

	static ShaderProgramSource parse_shader(const std::string &p_filePath);
private:
	uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __SHADER_H__