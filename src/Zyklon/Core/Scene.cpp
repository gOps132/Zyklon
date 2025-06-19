#include "Scene.h"

#include <Renderer/Renderer.h>

#include "Log.h"

namespace Zyklon {

Scene::Scene(const std::string& p_name)
	: m_name(p_name)
{

}

Scene::~Scene()
{
	
}

Ref<GameObject> Scene::createGameObject(const std::string& p_name)
{
	Ref<GameObject> new_game_object = createRef<GameObject>(p_name);

	// add to all objects map
	m_all_game_objects[new_game_object->getUUID()] = new_game_object;

	// add to root of all game objects if no object has a parent;
	if (!new_game_object->getParent())
	{
		m_root_game_objects.push_back(new_game_object);
	}

	// set game object weak_ptr to this scene
	new_game_object->setScene(weak_from_this());
	
	return new_game_object;
}

void Scene::destroyGameObject(Ref<GameObject> p_game_object)
{
	if (!p_game_object) return;
	destroyGameObject(p_game_object->getUUID()); // delegate to uuid destroy game object function
}

void Scene::destroyGameObject(const UUID& p_uuid)
{
	auto it = m_all_game_objects.find(p_uuid);
	if (it != m_all_game_objects.end())
	{
		Ref<GameObject> game_object_to_destroy = it->second;

		// remove from root objects if it is a root object
		auto root_it = std::remove(m_root_game_objects.begin(), m_root_game_objects.end(), game_object_to_destroy);
		if (root_it != m_root_game_objects.end())
		{
			m_root_game_objects.erase(root_it, m_root_game_objects.end());
		}

		// remove from parents children list
		Ref<GameObject> parent = game_object_to_destroy->getParent();
		if (parent)
		{
			parent->removeChild(game_object_to_destroy);
		}

		// the shared ptr in the map was the last strong reference
		// removing it will cause the game object and its components to be destructed
		m_all_game_objects.erase(it);
 	}
}

Ref<GameObject> Scene::getGameObject(const UUID& p_uuid)
{
	auto it = m_all_game_objects.find(p_uuid);
	if (it != m_all_game_objects.end())
	{
		return it->second;
	}
	return nullptr;
}

// iterate through the maps value and find the game object
void Scene::update(const float p_dt)
{
	for (const auto& pair : m_all_game_objects)
	{
		Ref<GameObject> game_object = pair.second;
		if (game_object->isActiveInHierarchy())
		{
			// systems would typically handle updates here
			// example:
			// for (const auto& comp : game_object->getComponents)
			// {
			// 	if (comp->isActive())
			// 	{
			// 		comp->onUpdate(p_dt);
			// 	}
			// }
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

	for (auto& pair : m_all_game_objects)
	{
		Ref<GameObject> game_object = pair.second;
		if (game_object->isActiveInHierarchy())
		{
			// renderer logic, typically handled by a renderer system or mesh render component
			// example:
			// auto mesh_renderer = game_object->getComponent<MeshRendererComponent>();
			// if (mesh_renderer && mesh_renderer->isActive()) 
			// {
			// 	mesh_renderer->onRender();
			// }
		}
	}

	Renderer::endScene()
}





} // namespace Zyklon