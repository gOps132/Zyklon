#include "ShaderLibrary.h"

namespace Zyklon {

ShaderLibrary::ShaderLibrary()
{
	// default shaders are loaded here during initialization
}

ShaderLibrary &ShaderLibrary::getInstance()
{
	static ShaderLibrary s_instance;
	return s_instance;
}

void ShaderLibrary::add(const std::string &p_name, const Ref<Shader> &p_shader)
{
	ZYKLON_CORE_ASSERT(!exists(p_name), "Shader already exists!");
	m_shaders[p_name] = p_shader;
}

void ShaderLibrary::add(const Ref<Shader> &p_shader)
{
	std::string name =
		std::filesystem::path(p_shader->getName()).stem().string();
	add(name, p_shader);
}

Ref<Shader> ShaderLibrary::load(const std::filesystem::path &p_filepath)
{
	Ref<Shader> shader = Ref<Shader>(Shader::create(p_filepath));
	if (shader) {
		std::string name = std::filesystem::path(p_filepath).stem().string();
		add(name, shader);
	}
	return shader;
}

Ref<Shader> ShaderLibrary::load(const std::string &p_name,
								const std::filesystem::path &p_filepath)
{
	Ref<Shader> shader = Ref<Shader>(Shader::create(p_filepath));
	if (shader) {
		add(p_name, shader);
	}
	return shader;
}

Ref<Shader> ShaderLibrary::get(const std::string &p_name) const
{
	ZYKLON_CORE_ASSERT(exists(p_name), "Shader not found!");
	// return m_shaders[p_name] // non const
	return m_shaders.at(p_name); // const
}

bool ShaderLibrary::exists(const std::string &p_name) const
{
	return m_shaders.count(p_name);
}

} // namespace Zyklon
