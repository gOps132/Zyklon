#include "AssetManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp> // For glm::decompose
#include <glm/gtc/type_ptr.hpp>

#include <Zyklon/Renderer/Material/BasicLitMaterial.h>
#include <Zyklon/Renderer/ShaderLibrary.h>
#include <Zyklon/Renderer/Texture.h>
#include <Zyklon/Renderer/Mesh.h>
#include <Zyklon/Components/MeshRendererComponent.h>
#include <Zyklon/Core/GameObject.h>
#include <Zyklon/Core/Scene.h>

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

	const aiScene *ai_scene = m_assimp_importer->ReadFile(
		p_filepath,
		aiProcess_Triangulate | aiProcess_GenNormals |
			aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace |
			aiProcess_LimitBoneWeights | aiProcess_ValidateDataStructure |
			aiProcess_PopulateArmatureData |
			aiProcess_FlipUVs); // FlipUVs might be needed for some formats
								// (OBJ, etc.)

	if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
		!ai_scene->mRootNode) {
		ZYKLON_CORE_ERROR("ASSIMP: Failed to load model '{0}': {1}", p_filepath,
						  m_assimp_importer->GetErrorString());
		return false;
	}

	ZYKLON_CORE_INFO(
		"ASSIMP: Loaded model '{0}' with {1} meshes. {2} material.", p_filepath,
		ai_scene->mNumMaterials);

	// Create a new ModelAssetData entry for this file
	ModelAssetData model_data(p_filepath);

	std::filesystem::path fs_filepath(p_filepath);
	std::string model_dir_path = fs_filepath.parent_path().string();

	// Process material first
	for (uint64_t i = 0; i < ai_scene->mNumMaterials; ++i) {
		aiMaterial *ai_mat = ai_scene->mMaterials[i];
		std::string material_name = ai_mat->GetName().C_Str();
	}
}

Ref<GameObject>
AssetManager::instantiateModel(const std::filesystem::path &model_filepath,
							   Ref<Scene> target_scene)
{
}
} // namespace Zyklon
