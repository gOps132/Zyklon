#include "SceneManager.h"

namespace Zyklon {

	void SceneManager::loadScene(const std::string &p_scene_name)
	{
		// potentially load the scene from a file or database
		auto it = m_loadedScenes.find(p_scene_name);
		if (it != m_loadedScenes.end())
		{
			setCurrentScene(it->second);
		}
		else
		{
			ZYKLON_CORE_ERROR("Scene {0} not found", p_scene_name);
		}
	}
	
	void SceneManager::saveScene(const std::string &p_scene_name)
	{
		// potentially save the current scene to a file or database
		auto it = m_loadedScenes.find(p_scene_name);
		if (it != m_loadedScenes.end())
		{
			it->second = m_current_scene; // update existing scene
		}
		else
		{
			m_loadedScenes[p_scene_name] = m_current_scene; // add new scene
		}
	}
	
	void SceneManager::resetScene()
	{
		if (m_current_scene)
		{
			m_current_scene->setName("New Scene");
			m_current_scene->clearAllGameObjects(); // clear all game objects
			m_current_scene->setActiveCamera(nullptr); // reset active camera
			m_current_scene = nullptr; // reset current scene
		}
		else
		{
			ZYKLON_CORE_ERROR("No current scene to reset");
		}
	}
	
	// NOTE: This function returns the name of the current scene, or an empty string if no scene is set
	const std::string& SceneManager::getCurrentSceneName() const	
	{
		if (m_current_scene)
			return m_current_scene->getName();
		else
			ZYKLON_CORE_ERROR("No current scene set");
		static const std::string empty = "";
		return empty;
	}

	void SceneManager::setCurrentScene(const Ref<Scene>& p_scene)
	{
		if (!p_scene)
		{
			ZYKLON_CORE_ERROR("Cannot set current scene to null");
			return;
		}
		m_current_scene = p_scene;
		ZYKLON_CORE_INFO("Current scene set to: {0}", m_current_scene->getName());
		if (m_current_scene)
		{
			// Set the active camera if it exists in the scene
			if (m_current_scene->getActiveCamera())
			{
				setActiveCamera(m_current_scene->getActiveCamera());
			}
			else
			{
				ZYKLON_CORE_WARN("No active camera set in scene {0}", m_current_scene->getName());
			}
		}
		else
		{
			ZYKLON_CORE_ERROR("Failed to set current scene: Scene is null");
		}
	}
	
	void SceneManager::addScene(const Ref<Scene>& scene)
	{
		if (!scene)
		{
			ZYKLON_CORE_ERROR("Cannot add null scene");
			return;
		}
		m_loadedScenes[scene->getName()] = scene;
		ZYKLON_CORE_INFO("Scene added: {0}", scene->getName());
	}
	
	Ref<Scene> SceneManager::getScene(const std::string& p_name) const
	{
		// find scene, convert name to lowercase for case-insensitive comparison
		std::string lower_name = p_name;
		std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
		auto it = m_loadedScenes.find(lower_name);
		if (it != m_loadedScenes.end()) // check whether scene exists
		{
			return it->second; // return the found scene
		}
		ZYKLON_CORE_ERROR("Scene {0} not found", p_name);
		return nullptr; // return null if scene not found
	}
	
	Ref<Scene> SceneManager::getSceneByUUID(const UUID& p_uuid) const
	{
		for (auto& pair : m_loadedScenes)
		{
			if (pair.second && pair.second->getUUID() == p_uuid) // compare UUID
			{
				return pair.second; // return the found scene
			}
		}
		ZYKLON_CORE_ERROR("Scene with UUID {0} not found", p_uuid);
		return nullptr; // return null if scene not found
	}

	void SceneManager::removeScene(const std::string& p_name)
	{
		// find scene, convert name to lowercase for case-insensitive comparison
		std::string lower_name = p_name;
		std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
		auto it = m_loadedScenes.find(lower_name);
		if (it != m_loadedScenes.end()) // check whether scene exists
		{
			if(m_current_scene && m_current_scene->getName() == lower_name)
			{
				m_current_scene = nullptr; // reset current scene if it matches
			}
			m_loadedScenes.erase(it); // remove scene from loaded scenes
		}
		else
		{
			ZYKLON_CORE_ERROR("Scene {0} not found", p_name);
			return;
		}
	}
	
	void SceneManager::removeScene(const UUID& p_uuid)
	{
		// find scene by UUID
		for (auto it = m_loadedScenes.begin(); it != m_loadedScenes.end(); ++it)
		{
			if (it->second && it->second->getUUID() == p_uuid) // compare UUIDs
			{
				if(m_current_scene && m_current_scene->getUUID() == p_uuid)
				{
					m_current_scene = nullptr; // reset current scene if it matches
				}
				m_loadedScenes.erase(it); // remove scene from loaded scenes
				return;
			}
		}
	}
	
	void SceneManager::clearScenes()
	{
		m_loadedScenes.clear(); // clear all loaded scenes
		if (m_current_scene)
		{
			m_current_scene->clearAllGameObjects(); // clear all game objects in current scene
			m_current_scene->setActiveCamera(nullptr); // reset active camera
			m_current_scene = nullptr; // reset current scene
		}
	}
	
	void SceneManager::setActiveCamera(const Ref<Camera>& p_camera)
	{
		if (m_current_scene)
		{
			m_current_scene->setActiveCamera(p_camera);
			ZYKLON_CORE_INFO("Active camera set to: {0}", p_camera->getName());
		}
		else
		{
			ZYKLON_CORE_ERROR("No current scene to set active camera");
		}
	}


	

} // namespace Zyklon

