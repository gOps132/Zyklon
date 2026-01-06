#include "AssetManager.h"
#include <assimp/matrix4x4.h>

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

#define ASSIMP_LOAD_FLAGS                                                      \
	(aiProcess_Triangulate | aiProcess_GenNormals |                            \
	 aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace |            \
	 aiProcess_LimitBoneWeights | aiProcess_ValidateDataStructure |            \
	 aiProcess_PopulateArmatureData |                                          \
	 aiProcess_FlipUVs) // FlipUVs might be needed for some formats
						// (OBJ, etc.)

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
	ShaderLibrary::getInstance().load(
		"ZyklonDefaultLit", "assets/Shaders/BasicLit.shader");
	m_default_shader = ShaderLibrary::getInstance().get("ZyklonDefaultLit");
	if (!m_default_shader) {
		ZYKLON_CORE_ERROR("AssetManager: Default lit shader 'ZyklonDefaultLit' "
						  "not found in ShaderLibrary!");
	}

	TextureSpecification fallback_spec;
	fallback_spec.width = 1;
	fallback_spec.height = 1;
	fallback_spec.format = ImageFormat::RGBA8;
	fallback_spec.generate_mips = false; // No mipmaps for a 1x1 texture
	m_default_texture = Texture2D::create(fallback_spec);
	// Provide 1x1 white pixel data (RGBA)
	unsigned char white_pixel_data[] = {255, 255, 255, 255};
	if (m_default_texture) {
		m_default_texture->setData(white_pixel_data, sizeof(white_pixel_data));
		ZYKLON_CORE_INFO("AssetManager: Fallback white texture created.");
	}
	else {
		ZYKLON_CORE_ERROR(
			"AssetManager: Failed to create fallback white texture!");
	}
}

AssetManager::~AssetManager()
{
	// assimp importer cleans its own data
}

bool AssetManager::loadModel(const std::filesystem::path &p_filepath)
{
	ZYKLON_CORE_INFO("{0}", p_filepath);
	if (m_model_asset_data_cache.count(p_filepath.string())) {
		ZYKLON_CORE_INFO("Model '{0}' already loaded and cached.",
						 p_filepath.string());
		return true;
	}

	const aiScene *ai_scene =
		m_assimp_importer->ReadFile(p_filepath.string(), ASSIMP_LOAD_FLAGS);
	if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
		!ai_scene->mRootNode) {
		ZYKLON_CORE_ERROR("ASSIMP: Failed to load model '{0}': {1}",
						  p_filepath.string(),
						  m_assimp_importer->GetErrorString());
		return false;
	}

	ZYKLON_CORE_INFO(
		"ASSIMP: Loaded model '{0}' with {1} meshes. {2} material.",
		p_filepath.string(), ai_scene->mNumMeshes, ai_scene->mNumMaterials);

	// Create a new ModelAssetData entry for this file
	ModelAssetData model_data(p_filepath);

	std::filesystem::path fs_filepath(p_filepath);
	std::string model_dir_path = fs_filepath.parent_path().string();

	// --- PROCESS MATERIALS ---
	for (uint64_t i = 0; i < ai_scene->mNumMaterials; ++i) {
		aiMaterial *ai_mat = ai_scene->mMaterials[i];
		ZYKLON_CORE_INFO("Processing material '{0}'",
						 ai_mat->GetName().C_Str());
		std::string material_name = ai_mat->GetName().C_Str();
		// if no material name, assign file name with index
		if (material_name.empty()) {
			material_name =
				fs_filepath.stem().string() + "_material_" + std::to_string(i);
		}
		// TODO: dont forget the default shader material
		Ref<Material> z_material =
			Zyklon::createRef<BasicLitMaterial>(m_default_shader);

		// stuff basic color properties for default shader
		aiColor3D color(0.0f, 0.0f, 0.0f);
		if (ai_mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
			z_material->setVec3("u_Color", {color.r, color.g, color.b});
		}
		else {
			z_material->setVec3("u_Color", {1.0f, 1.0f, 1.0f}); // white
		}

		ZYKLON_CORE_INFO("Looking for diffuse texture in material '{0}'",
						 material_name);
		aiString str;
		if (ai_mat->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS) {
			std::filesystem::path texture_full_path =
				std::filesystem::path(model_dir_path) / str.C_Str();
			Ref<Texture2D> z_texture = loadTexture(texture_full_path);
			ZYKLON_INFO("Loading texture {0}", p_filepath.string());
			if (z_texture) {
				static_cast<BasicLitMaterial *>(z_material.get())
					->setTexture(z_texture, 0);
			}
		}
		else {
			// Assign default white texture if no diffuse texture found
			static_cast<BasicLitMaterial *>(z_material.get())
				->setTexture(m_default_texture, 0);
			ZYKLON_WARN("Material '{0}' has no diffuse texture. Using default "
						"white texture.",
						material_name);
		}
		// handle other texture types (normal, metallic, roughness) similarly
		// for more advanced materials

		model_data.materials.push_back(z_material);
		m_materials[material_name] = z_material; // cache in assetshader map
	}

	// --- PROCESS THE MESHES ---
	for (uint64_t i = 0; i < ai_scene->mNumMeshes; ++i) {
		aiMesh *ai_mesh = ai_scene->mMeshes[i];
		std::string mesh_name = ai_mesh->mName.C_Str();
		if (mesh_name.empty()) {
			mesh_name =
				fs_filepath.stem().string() + "__mesh__" + std::to_string(i);
		}

		// should we instance zyklon mesh class here?
		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		for (uint64_t j = 0; j < ai_mesh->mNumVertices; ++j) {
			// vertices REQUIRED
			vertices.push_back(ai_mesh->mVertices[j].x);
			vertices.push_back(ai_mesh->mVertices[j].y);
			vertices.push_back(ai_mesh->mVertices[j].z);
			// normals
			if (ai_mesh->HasNormals()) {
				vertices.push_back(ai_mesh->mNormals[j].x);
				vertices.push_back(ai_mesh->mNormals[j].y);
				vertices.push_back(ai_mesh->mNormals[j].z);
			}
			else {
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);
			}
			// UV
			if (ai_mesh->HasTextureCoords(0)) {
				vertices.push_back(ai_mesh->mTextureCoords[0][j].x);
				vertices.push_back(ai_mesh->mTextureCoords[0][j].y);
			}
			else {
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);
			}
		}

		// indices
		for (uint64_t j = 0; j < ai_mesh->mNumFaces; ++j) {
			aiFace face = ai_mesh->mFaces[j];
			for (uint64_t k = 0; k < face.mNumIndices; ++k) {
				indices.push_back(face.mIndices[k]);
			}
		}

		Zyklon::BufferLayout mesh_layout = {
			{Zyklon::ShaderDataType::Float3, "a_position", false},
			{Zyklon::ShaderDataType::Float3, "a_normal", false},
			{Zyklon::ShaderDataType::Float2, "a_uv", false}};

		// finally create our mesh hehe
		Ref<Mesh> z_mesh = createRef<Mesh>(vertices, indices, mesh_layout);
		model_data.meshes.push_back(z_mesh);
		m_meshes[mesh_name] = z_mesh; // cache our mesh
	}

	// --- PROCESS THE ROOT NODE RECURSIVELY TO BUILD DATA HIERARCHY ---
	// see assimp docs
	processAssimpNode(model_data.root_node, ai_scene->mRootNode, ai_scene,
					  model_dir_path);

	m_model_asset_data_cache[p_filepath.string()] = model_data;
	return true;
}

void AssetManager::processAssimpNode(ModelNodeData &p_out_node_data,
									 aiNode *p_ai_node,
									 const aiScene *p_ai_scene,
									 const std::string &p_model_dir_path)
{
	p_out_node_data.name = p_ai_node->mName.C_Str();

	// Convert Assimp's aiMatrix4x4 to glm::mat4
	// Assimp matrices are row-major, GLM/OpenGL are column-major. Direct copy
	// needs transpose-like operation. Or, more reliably, copy element by
	// element:
	p_out_node_data.local_transform[0][0] = p_ai_node->mTransformation.a1;
	p_out_node_data.local_transform[1][0] = p_ai_node->mTransformation.a2;
	p_out_node_data.local_transform[2][0] = p_ai_node->mTransformation.a3;
	p_out_node_data.local_transform[3][0] = p_ai_node->mTransformation.a4;
	p_out_node_data.local_transform[0][1] = p_ai_node->mTransformation.b1;
	p_out_node_data.local_transform[1][1] = p_ai_node->mTransformation.b2;
	p_out_node_data.local_transform[2][1] = p_ai_node->mTransformation.b3;
	p_out_node_data.local_transform[3][1] = p_ai_node->mTransformation.b4;
	p_out_node_data.local_transform[0][2] = p_ai_node->mTransformation.c1;
	p_out_node_data.local_transform[1][2] = p_ai_node->mTransformation.c2;
	p_out_node_data.local_transform[2][2] = p_ai_node->mTransformation.c3;
	p_out_node_data.local_transform[3][2] = p_ai_node->mTransformation.c4;
	p_out_node_data.local_transform[0][3] = p_ai_node->mTransformation.d1;
	p_out_node_data.local_transform[1][3] = p_ai_node->mTransformation.d2;
	p_out_node_data.local_transform[2][3] = p_ai_node->mTransformation.d3;
	p_out_node_data.local_transform[3][3] = p_ai_node->mTransformation.d4;

	// TODO: There must be a simpler way to do the matrix transform instead of
	// the one above

	// const aiMatrix4x4& transform = p_ai_node->mTransformation;
	// glm::mat<4,4,float> local_transform(transform);
	// local_transform.transpose();
	// p_out_node_data.local_transform = local_transform;

	// Collect mesh indices for this node
	for (unsigned int i = 0; i < p_ai_node->mNumMeshes; ++i) {
		p_out_node_data.mesh_indices.push_back(p_ai_node->mMeshes[i]);
	}

	// Recursively process children
	for (unsigned int i = 0; i < p_ai_node->mNumChildren; ++i) {
		ModelNodeData child_data;
		processAssimpNode(child_data, p_ai_node->mChildren[i], p_ai_scene,
						  p_model_dir_path);
		p_out_node_data.children.push_back(child_data);
	}
}

// helper function to recursively instantiate GameObjects from ModelNodeData
// returns the root of the game object instantiated hierarchy
Ref<GameObject> instantiateNodeRecursive(const ModelNodeData &node_data,
										 const ModelAssetData &model_asset_data,
										 Ref<Scene> target_scene)
{
	Ref<GameObject> current_go = target_scene->createGameObject(node_data.name);
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(node_data.local_transform, scale, rotation, translation,
				   skew, perspective);

	current_go->setLocalPosition(translation);
	current_go->setLocalRotation(rotation);
	current_go->setLocalScale(scale);

	for (uint32_t mesh_idx : node_data.mesh_indices) {
		if (mesh_idx < model_asset_data.meshes.size()) {
			Ref<Mesh> mesh = model_asset_data.meshes[mesh_idx];
			Ref<Material> material_to_use = nullptr;

			// Proper material assignment: Use the material index from the
			// Assimp mesh. (Assumes you've stored aiMesh->mMaterialIndex
			// somewhere, or can retrieve it). For now, still simplified to
			// cycle or use the first if no direct mapping. If
			// model_asset_data.materials were loaded in the order of
			// ai_scene->mMaterials: unsigned int assimp_material_idx =
			// ai_scene->mMeshes[mesh_idx]->mMaterialIndex; // Need ai_scene
			// access or stored info if (assimp_material_idx <
			// model_asset_data.materials.size()) { material_to_use =
			// model_asset_data.materials[assimp_material_idx]; }

			// Current simple fallback:
			if (!model_asset_data.materials.empty()) {
				material_to_use =
					model_asset_data
						.materials[mesh_idx %
								   model_asset_data.materials.size()];
			}

			// If no material found from model data, fallback to a default
			// BasicLitMaterial
			if (!material_to_use) {
				if (AssetManager::getInstance().getDefaultShader()) {
					material_to_use = createRef<BasicLitMaterial>(
						AssetManager::getInstance().getDefaultShader());
					ZYKLON_CORE_WARN(
						"Model '{0}' has no specific material for mesh '{1}', "
						"using default BasicLitMaterial.",
						model_asset_data.filepath.string(), node_data.name);
				}
				else {
					ZYKLON_CORE_ERROR("No material found for mesh '{0}' and "
									  "default shader is null!",
									  node_data.name);
				}
			}

			if (mesh && material_to_use) {
				current_go->addComponent<MeshRendererComponent>(
					mesh, material_to_use);
			}
			else {
				ZYKLON_CORE_ERROR(
					"Failed to add MeshRendererComponent to GameObject '{0}': "
					"Mesh or Material is null (after fallback).",
					node_data.name);
			}
		}
	}

	for (const ModelNodeData &child_node : node_data.children) {
		Ref<GameObject> child_go = instantiateNodeRecursive(
			child_node, model_asset_data, target_scene);
		current_go->addChild(child_go);
	}
	return current_go;
}

Ref<GameObject>
AssetManager::instantiateModel(const std::filesystem::path &model_filepath,
							   Ref<Scene> target_scene)
{
	// Check if the model is already loaded and cached
	auto it = m_model_asset_data_cache.find(model_filepath);
	if (it == m_model_asset_data_cache.end()) {
		ZYKLON_CORE_ERROR("AssetManager: Model '{0}' not found in cache.",
						  model_filepath);
		return nullptr;
	}

	// Get the root node data and asset data
	const ModelAssetData &model_asset = it->second;

	// Instantiate the root game object for this model
	Ref<GameObject> root_go = instantiateNodeRecursive(
		model_asset.root_node, model_asset, target_scene);

	return root_go;
}

Ref<Texture2D> AssetManager::loadTexture(const std::filesystem::path &p_path)
{
	ZYKLON_CORE_INFO("Loading Texture {0}", p_path.string());

	Ref<Texture2D> texture = Texture2D::create(p_path.string());

	if (texture) {
		m_textures[p_path] = texture;
		ZYKLON_CORE_INFO("Successfully loaded and cached texture: {0}",
						 p_path.string());
	}
	else {
		ZYKLON_CORE_WARN(
			"Failed to load texture: {0}. Using fallback white texture.",
			p_path.string());
		texture = m_default_texture;
		if (texture) { // Ensure fallback itself was created
			m_textures[p_path.string()] =
				texture; // Cache the fallback for this path too
		}
		else {
			ZYKLON_CORE_ERROR(
				"AssetManager: No valid texture (even fallback) for path: {0}",
				p_path.string());
		}
	}

	return texture;
}

Ref<Material> AssetManager::loadMaterial(const std::string &p_name,
										 const Ref<Shader> &p_shader,
										 const Ref<Texture2D> p_texture)
{
	if (m_materials.count(p_name)) {
		ZYKLON_CORE_INFO("Material '{0}' already loaded and cached.", p_name);
		return m_materials.at(p_name);
	}

	Ref<Texture2D> actual_texture;
	Ref<Shader> actual_shader = p_shader ? p_shader : m_default_shader;
	if (p_texture) {
		ZYKLON_CORE_INFO("Using provided texture for material '{0}'", p_name);
		actual_texture = p_texture;
	}
	else {
		ZYKLON_CORE_WARN("No texture provided for material '{0}', using "
						 "default white texture.",
						 p_name);
		actual_texture = m_default_texture;
	}

	if (!actual_shader) {
		ZYKLON_CORE_ERROR("AssetManager: Cannot create material '{0}', no "
						  "shader provided and default shader is null!",
						  p_name);
		return nullptr;
	}
	Ref<Material> material =
		createRef<BasicLitMaterial>(actual_shader, actual_texture);

	m_materials[p_name] = material;
	ZYKLON_CORE_INFO("Successfully loaded and cached material: {0}", p_name);
	return material;
}

Ref<Mesh> AssetManager::loadMesh(const std::string &p_name,
								 const std::vector<float> &p_vertices,
								 const std::vector<uint32_t> &p_indices,
								 const BufferLayout &p_layout)
{
	if (m_meshes.count(p_name)) {
		ZYKLON_CORE_INFO("Mesh '{0}' already loaded", p_name);
		return m_meshes.at(p_name);
	}

	Ref<Mesh> mesh = createRef<Mesh>(p_vertices, p_indices, p_layout);

	m_meshes[p_name] = mesh;
	ZYKLON_CORE_INFO("Successfully loaded and cached mesh '{0}'", p_name);
	return mesh;
}

Ref<Texture2D> AssetManager::getTexture(const std::filesystem::path &p_filepath)
{
	ZYKLON_CORE_ASSERT(m_textures.count(p_filepath.string()),
					   "Texture '{0}' not found in asset cache!",
					   p_filepath.string());
	return m_textures.at(p_filepath.string());
}

Ref<Material> AssetManager::getMaterial(const std::string &p_name)
{
	ZYKLON_CORE_ASSERT(m_materials.count(p_name),
					   "Material '{0}' not found in asset cache!", p_name);
	return m_materials.at(p_name);
}

Ref<Mesh> AssetManager::getMesh(const std::string &p_mesh)
{
	ZYKLON_CORE_ASSERT(m_meshes.count(p_mesh),
					   "Mesh '{0}' not found in asset cache!", p_mesh);
	return m_meshes.at(p_mesh);
}

} // namespace Zyklon