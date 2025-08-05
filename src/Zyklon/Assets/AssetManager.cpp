#include "AssetManager.h"

#include <Zyklon/Renderer/ShaderLibrary.h>

namespace Zyklon {

AssetManager &AssetManager::getInstance()
{
	static AssetManager instance;
	return instance;
}

AssetManager::AssetManager()
{
	m_assimp_importer = std::make_unique<Assimp::Importer>();
	// get default shader that materials can use if not explicitely defined by
	// the model
	m_default_shader = ShaderLibrary::getInstance().get("ZyklonDefaultLit");
	if (!m_default_shader) {
		ZYKLON_CORE_ERROR("AssetManager: Default lit shader 'ZyklonDefaultLit' "
						  "not found in ShaderLibrary!");
	}
}

AssetManager::~AssetManager()
{
	// assimp importer cleans its own data
}

bool AssetManager::loadModel(const std::filesystem::path &p_filepath)
{
	if (m_model_asset_data_cache.count(p_filepath)) {
		ZYKLON_CORE_INFO("Model '{0}' already loaded and cached.", p_filepath);
		return true;
	}

	// const aiScene *ai_scene = m_assimp_importer->ReadFile(p_filepath, );
}

Ref<GameObject> AssetManager::instantiateModel(const std::filesystem::path &model_filepath,
									Ref<Scene> target_scene)
{

}
} // namespace Zyklon
