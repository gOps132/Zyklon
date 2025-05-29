#include <zyklon_pch.h>

#include "Shader.h"

#include "Renderer.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Zyklon {

Shader *Shader::create(const std::string &p_filepath)
{
	switch (Renderer::getApi()) {
	case RendererAPI::API::None:
		ZYKLON_CORE_ASSERT(false, "No Shader is supported!");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return new OpenGLShader(p_filepath);
	}
	ZYKLON_CORE_ASSERT(false, "Unknown Shader!");
	return nullptr;
}

ShaderProgramSource Shader::parseShader(const std::string &p_filepath)
{
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::ifstream stream(p_filepath); // opens the file
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;

            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}



} // namespace Zyklon
