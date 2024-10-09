#include <Zyklon/Core/zyklon_pch.h>

#include <glad/glad.h>

#include "OpenGLErrorManager.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
		;
}

int GLLogCall(const char *p_function, const char *p_file, int p_line)
{
	if (GLenum error = glGetError()) {

		ZYKLON_CORE_ERROR("OPENGL ERROR: ");
		ZYKLON_CORE_ERROR("     FUNCTION: {0}", p_function);
		ZYKLON_CORE_ERROR("     FILE: {0}", p_file);
		ZYKLON_CORE_ERROR("     LINE: {0}", p_line);

		//        TODO: make this faster with the c api
		std::stringstream ss;
		ss << std::hex << error;
		std::string res(ss.str());
		std::string new_string = std::string(4 - res.length(), '0') + res;
		std::ifstream stream("lib/glad/include/glad/glad.h");
		std::string p_line;
		while (getline(stream, p_line)) {
			if (p_line.find(new_string) != std::string::npos)
				ZYKLON_CORE_ERROR("{0}", p_line);
		}

		return -1;
	}

	return 1;
}
