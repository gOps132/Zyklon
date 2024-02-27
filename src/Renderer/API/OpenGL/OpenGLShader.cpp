#include "Zyklon/zyklon_pch.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

#include "Zyklon/Core.h"
#include <glad/glad.h>

#include "OpenGLErrorManager.h"
#include "OpenGLShader.h"

namespace Zyklon {

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

// Utilize an enum of types
void OpenGLShader::set_uniform() { };
} // namespace Zyklon
