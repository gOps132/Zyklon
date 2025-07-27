
#include "Core.h"

#include "Scene.h"
#include "Log.h"
#include "GameObject.h"

#include <Zyklon/Renderer/Renderer.h>
#include <Zyklon/Renderer/Mesh.h>
#include <Zyklon/Renderer/Material/Material.h>

#include <Zyklon/Components/MeshRendererComponent.h>

namespace Zyklon {

Scene::Scene(const std::string &p_name) : m_name(p_name)
{
	m_uuid = UUID();		   // generate a new UUID for the scene
	m_active_camera = nullptr; // no active camera by default
	ZYKLON_CORE_INFO("Scene {0} created with UUID {1}", m_name, m_uuid);

	// initialize root game objects vector
	m_root_game_objects.reserve(10); // reserve space for 10 root game objects
	m_all_game_objects.reserve(100); // reserve space for 100 game objects
}

Scene::~Scene()
{
	// clear all game objects
	for (auto &pair : m_all_game_objects) {
		pair.second->setScene(
			std::weak_ptr<Scene>()); // reset scene reference in game object
	}
	m_all_game_objects.clear();
	m_root_game_objects.clear();
}

Ref<GameObject> Scene::createGameObject(const std::string &p_name)
{
	Ref<GameObject> new_game_object = createRef<GameObject>(p_name);

	// add to all objects map
	m_all_game_objects[new_game_object->getUUID()] = new_game_object;

	// add to root of all game objects if no object has a parent;
	if (!new_game_object->getParent()) {
		m_root_game_objects.push_back(new_game_object);
	}

	// set game object weak_ptr to this scene
	new_game_object->setScene(weak_from_this());

	new_game_object->setUUID(UUID());

	return new_game_object;
}

void Scene::destroyGameObject(Ref<GameObject> p_game_object)
{
	if (!p_game_object)
		return;
	destroyGameObject(
		p_game_object
			->getUUID()); // delegate to uuid destroy game object function
}

void Scene::destroyGameObject(const UUID &p_uuid)
{
	auto it = m_all_game_objects.find(p_uuid);
	if (it != m_all_game_objects.end()) {
		Ref<GameObject> game_object_to_destroy = it->second;

		// remove from root objects if it is a root object
		auto root_it =
			std::remove(m_root_game_objects.begin(), m_root_game_objects.end(),
						game_object_to_destroy);
		if (root_it != m_root_game_objects.end()) {
			m_root_game_objects.erase(root_it, m_root_game_objects.end());
		}

		// remove from parents children list
		Ref<GameObject> parent = game_object_to_destroy->getParent();
		if (parent) {
			parent->removeChild(game_object_to_destroy);
		}

		// the shared ptr in the map was the last strong reference
		// removing it will cause the game object and its components to be
		// destructed
		m_all_game_objects.erase(it);
	}
}

void Scene::removeGameObject(Ref<GameObject> p_game_object)
{
	if (!p_game_object)
		return;

	auto it = std::find_if(
		m_all_game_objects.begin(), m_all_game_objects.end(),
		[&](const auto &pair) { return pair.second == p_game_object; });

	if (it != m_all_game_objects.end()) {
		m_all_game_objects.erase(it);
	}
}

void Scene::removeGameObject(const UUID &p_uuid)
{
	auto it = m_all_game_objects.find(p_uuid);
	if (it != m_all_game_objects.end()) {
		m_all_game_objects.erase(it);
	}
}

Ref<GameObject> Scene::getGameObject(const UUID &p_uuid)
{
	auto it = m_all_game_objects.find(p_uuid);
	if (it != m_all_game_objects.end()) {
		return it->second;
	}
	return nullptr;
}

void Scene::addGameObject(const UUID &p_uuid, Ref<GameObject> p_game_object)
{
	m_all_game_objects[p_uuid] = p_game_object;
}

void Scene::clearAllGameObjects()
{
	m_all_game_objects.clear();
	m_root_game_objects.clear();
}

// iterate through the maps value and find the game object
void Scene::update(const float p_dt)
{
	for (auto &[uuid, gameObject] : m_all_game_objects) {
		for (auto &comp : gameObject->m_components) {
			if (comp->isActive())
				comp->onUpdate(p_dt);
		}
	}
}

void Scene::render()
{
	if (!m_active_camera) {
		ZYKLON_CORE_ERROR("NO CAMERA SET IN SCENE {0}", m_name);
		return;
	}

	// iterate through maps values and update objects
	Renderer::beginScene(*m_active_camera);

	for (auto &pair : m_all_game_objects) {
		Ref<GameObject> game_object = pair.second;
		if (game_object->isActiveInHierarchy()) {
			// renderer logic, typically handled by a renderer system or mesh
			// render component example:
			auto mesh_renderer =
				game_object->getComponent<MeshRendererComponent>();
			if (mesh_renderer && mesh_renderer->isActive()) {
				Ref<Mesh> mesh = mesh_renderer->getMesh();
				Ref<Material> material = mesh_renderer->getMaterial();

				if (mesh && material) {
					Ref<Shader> shader = material->get_shader();
					Ref<VertexArray> vertex_array = mesh->getVertexArray();

					if (shader && vertex_array) {
						glm::mat4 model_matrix =
							game_object->getWorldTransformationMatrix();

						Renderer::submit(shader, vertex_array, model_matrix);
					}
					else {
						ZYKLON_CORE_WARN(
							"MeshRendererComponent on GameObject '{0}' has "
							"missing Shader or VertexArray.",
							game_object->getName());
					}
				}
				else {
					ZYKLON_CORE_WARN("MeshRendererComponent on GameObject "
									 "'{0}' has missing Mesh or Material.",
									 game_object->getName());
				}
			}
		}
	}

	Renderer::endScene();
}

} // namespace Zyklon