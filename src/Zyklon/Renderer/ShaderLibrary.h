#ifndef __SHADERLIBRARY_H__
#define __SHADERLIBRARY_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include "Shader.h"

namespace Zyklon {
/**
 * A singleton class to store, retrieve, and manage all the engine's compiled
 * shader objects by name. It acts as a cache and registry.
 */
class ShaderLibrary {
public:
	static ShaderLibrary &getInstance();
	ShaderLibrary(const ShaderLibrary &) = delete;			  // no copying
	ShaderLibrary &operator=(const ShaderLibrary &) = delete; // no assignment

private: // private consructor for singleton
	ShaderLibrary();
	~ShaderLibrary() = default;

public:
	// adds existing shader ref
	void add(const std::string &p_name, const Ref<Shader> &p_shader);
	void add(const Ref<Shader> &p_shader); // uses shaders internal filepath

	// load and adds based on filename
	Ref<Shader> load(const std::filesystem::path &p_filepath);
	Ref<Shader> load(const std::string &p_name,
					 const std::filesystem::path &p_filepath);

	Ref<Shader> get(const std::string &p_name) const;

	bool exists(const std::string &p_name) const;

private:
	std::unordered_map<std::string, Ref<Shader>> m_shaders;
};

} // namespace Zyklon

#endif // __SHADERLIBRARY_H__