#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <zyklon_pch.h>

#include "Core.h"
#include "Scene.h"

namespace Zyklon {

// scene manager is a singleton class that manages the current scene, loading and saving scenes, and resetting the scene
class SceneManager {
public:
	SceneManager(const SceneManager&) = delete; // prevent copying
	SceneManager() = default;
	~SceneManager() = default;
	
	SceneManager& operator=(const SceneManager&) = delete; // prevent assignment
	
	// Singleton pattern to ensure only one instance of SceneManager exists
	// also create a new instance if no insteance exists
	// this is a thread-safe singleton implementation
	static SceneManager& getInstance() {
		static SceneManager instance; // Guaranteed to be destroyed, instantiated on first use
		return instance;
	}

	void loadScene(const std::string &p_scene_name);

	void saveScene(const std::string &p_scene_name);

	// TODO: custom API for saving and loading scenes, potentially using serialization
	void resetScene();
	
	Ref<Scene> getCurrentScene() const { return m_current_scene; }
	
	const std::string& getCurrentSceneName() const;
	
	void setCurrentScene(const Ref<Scene>& p_scene);

	void addScene(const Ref<Scene>& scene);

	Ref<Scene> getScene(const std::string& p_name) const;

	Ref<Scene> getSceneByUUID(const UUID& p_uuid) const;

	void removeScene(const std::string& p_name);

	void removeScene(const UUID& p_uuid);

	void clearScenes();

	void setActiveCamera(const Ref<Camera>& p_camera);

	const Ref<Camera> getActiveCamera() const;
	
	void update(const float p_dt);
	
	void render();
private:
	// You can add private members to manage the current scene, scene history, etc.
	// For example, a map of loaded scenes or a stack for undo/redo functionality.
	Ref<Scene> m_current_scene; // current active scene
	std::unordered_map<std::string, Ref<Scene>> m_loadedScenes;
	// You might also want to keep track of scene history for undo/redo functionality
	// std::stack<Ref<Scene>> m_sceneHistory; // for undo/redo functionality
	// std::stack<Ref<Scene>> m_sceneRedoStack; // for redo functionality
};

}

#endif // __SCENE_MANAGER_H__