#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include <Renderer/Renderer.h>
#include <Renderer/Shader.h>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "OpenGLErrorManager.h"
#include "OpenGLShader.h"


namespace Zyklon {

void OpenGLShader::set_uniform_1f(const std::string &name, const float value)
{
	GLCall(glUseProgram(m_renderer_id));
	GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location != -1)
		GLCall(glUniform1f(location, value));
}

void OpenGLShader::set_uniform_2f(const std::string &name, const float v0, const float v1)
{
	GLCall(glUseProgram(m_renderer_id));
	GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location != -1)
		GLCall(glUniform2f(location, v0, v1));
}


void OpenGLShader::set_uniform_3fv(const std::string &name, const glm::vec3 &buffer)
{
	GLCall(glUseProgram(m_renderer_id));
	GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location != -1)
		GLCall(glUniform3f(location, buffer.x, buffer.y, buffer.z));
}

void OpenGLShader::set_uniform_4fv(const std::string &name, const glm::vec4 &buffer)
{
	GLCall(glUseProgram(m_renderer_id));
	GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location != -1)
		GLCall(glUniform4f(location, buffer.x, buffer.y, buffer.z, buffer.w));
}

void OpenGLShader::set_uniform_matrix_4fv(const std::string &name, const glm::mat4 &buffer)
{
	GLCall(glUseProgram(m_renderer_id));
	GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location != -1)
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(buffer)));
}

OpenGLShader::OpenGLShader(const std::string &p_filepath)
{
	m_shader_source = parse_shader(p_filepath);

	// create an empty vertex shader handle
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const char *source = m_shader_source.vertexSource.c_str();
	GLCall(glShaderSource(vertexShader, 1, &source, 0));

	// Compile the vertex shader
	GLCall(glCompileShader(vertexShader));
 
	int isCompiled = 0;
	GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE) {
		int maxLength = 0;
		GLCall(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		GLCall(glGetShaderInfoLog(vertexShader, maxLength, &maxLength,
								  &infoLog[0]));

		// We don't need the shader anymore.
		GLCall(glDeleteShader(vertexShader));

		ZYKLON_CORE_ERROR("{0}", infoLog.data());
		ZYKLON_CORE_ASSERT(false, "Vertex Shader Compilation Error")

		return;
	}

	// create an empty fragment shader handle
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = m_shader_source.fragmentSource.c_str();
	GLCall(glShaderSource(fragmentShader, 1, &source, 0));

	// Compile the fragment shader
	GLCall(glCompileShader(fragmentShader));

	GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE) {
		int maxLength = 0;
		GLCall(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		GLCall(glGetShaderInfoLog(fragmentShader, maxLength, &maxLength,
								  &infoLog[0]));

		// We don't need the shader anymore.
		GLCall(glDeleteShader(fragmentShader));
		// Either of them. Don't leak shaders.
		GLCall(glDeleteShader(vertexShader));

		ZYKLON_CORE_ERROR("{0}", infoLog.data());
		ZYKLON_CORE_ASSERT(false, "Fragment Shader Compilation Error")

		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// get a program object.
	m_renderer_id = glCreateProgram();

	// Attach our shaders to our program
	GLCall(glAttachShader(m_renderer_id, vertexShader));
	GLCall(glAttachShader(m_renderer_id, fragmentShader));

	// Link our program
	GLCall(glLinkProgram(m_renderer_id));

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	int isLinked = 0;
	GLCall(glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int *)&isLinked));
	if (isLinked == GL_FALSE) {
		int maxLength = 0;
		GLCall(glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		GLCall(glGetProgramInfoLog(m_renderer_id, maxLength, &maxLength,
								   &infoLog[0]));

		// We don't need the program anymore.
		GLCall(glDeleteProgram(m_renderer_id));
		// Don't leak shaders either.
		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));

		ZYKLON_CORE_ERROR("{0}", infoLog.data());
		ZYKLON_CORE_ASSERT(false, "Shader Compilation Error")

		return;
	}

	// Always detach shaders after a successful link.
	GLCall(glDetachShader(m_renderer_id, vertexShader));
	GLCall(glDetachShader(m_renderer_id, fragmentShader));
}

OpenGLShader::~OpenGLShader() { GLCall(glDeleteProgram(m_renderer_id)); }

void OpenGLShader::bind() { GLCall(glUseProgram(m_renderer_id)); }

void OpenGLShader::unbind() { GLCall(glUseProgram(0)); }

} // namespace Zyklon
