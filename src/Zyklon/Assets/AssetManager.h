#ifndef __ASSSETMANAGER_H__
#define __ASSSETMANAGER_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>

namespace Zyklon {
class Mesh;
class Material;
class Shader;
class Texture2D;
class GameObject;
class Scene;
class BufferLayout;

// Assimp forward declarations
struct aiScene;
struct aiNode;
struct aiMaterial;
struct aiMesh;
struct aiMatrix4x4; // For node transforms

// helper struct to represent the node in an imported model's hierarchy which
// the asset manager will cache
typedef struct ModelNodeData {
	std::string name;
	glm::mat4 local_transform;
	std::vector<uint32_t> mesh_indices;
	std::vector<ModelNodeData> children;
} ModelNodeData;

// Represents a loaded model asset which contains all its meshes and materials
// this the cacheable unit for models
typedef struct ModelAssetData {
	std::filesystem::path filepath;
	std::vector<Ref<Mesh>> meshes;
	std::vector<Ref<Material>> materials;
	ModelNodeData root_node;

	// for map insertion
	ModelAssetData() = default;
	ModelAssetData(const std::filesystem::path &p_filepath)
		: filepath(p_filepath) {};
} ModelAssetData;

class ZYKLON_EXPORT AssetManager {
public:
	static AssetManager &getInstance();
	AssetManager(const AssetManager &) = delete;
	AssetManager &operator=(const AssetManager &) = delete;

private:
	AssetManager();	 // prevents new instances
	~AssetManager(); // cleans up the assimp importer
public:
	// loads a model from file (gltf, fbx, etc.) into internal cache
	bool loadModel(const std::filesystem::path &p_filepath);
	// instantiates cached model into a scene, returns root of the instantiate
	// model
	Ref<GameObject>
	instantiateModel(const std::filesystem::path &model_filepath,
					 Ref<Scene> target_scene);
	// --- direct asset loading (for assets not part of a model) ---
	Ref<Texture2D> loadTexture(const std::filesystem::path p_filepath);
	Ref<Material> loadMaterial(const std::string &p_name,
							   const Ref<Shader> &p_shader,
							   const Ref<Texture2D> p_texture);
	Ref<Mesh> loadMesh(const std::string &p_name,
					   const std::vector<float> &p_vertices,
					   const BufferLayout &p_layout);

	// --- Asset retrieval from cache ---
	Ref<Texture2D> getTexture(const std::filesystem::path &p_filepath);
	Ref<Material> getMaterial(const std::string &p_name);
	Ref<Mesh> getMesh(const std::string &p_mesh);
	/**
	 * we wouldn't typically retrieve a ModelAssetData directly, but instantiate
	 * it. However, we could have a getModelData() if a higher-level cache
	 * access is needed.
	 */
private:
	// internal helper for assimp processing
	void processAssimpNode(ModelNodeData &p_out_node_data, aiNode *p_ai_node,
						   const aiScene *ai_scene,
						   const std::filesystem::path &p_model_dir_path);

	// maps for caching various asset types
	std::unordered_map<std::string, Ref<Texture2D>> m_textures;
	std::unordered_map<std::string, Ref<Material>> m_materials;
	std::unordered_map<std::string, Ref<Mesh>>
		m_meshes; // meshes can be shared across models

	// cache for parsed model data (meshes, materials, node structure)
	std::unordered_map<std::string, ModelAssetData> m_model_asset_data_cache;

	// assimp importer instance, should be managed globally for parsing
	std::unique_ptr<Assimp::Importer> m_assimp_importer;

	// default shader, for materials that don't specify one
	Ref<Shader> m_default_shader;
};

} // namespace Zyklon

#endif // __ASSSETMANAGER_H__