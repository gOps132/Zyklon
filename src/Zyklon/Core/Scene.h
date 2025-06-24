#ifndef __SCENE_H__
#define __SCENE_H__

#include <zyklon_pch.h>

#include <Renderer/Camera/Camera.h>

#include "Core.h"
#include "UUID.h"

namespace Zyklon {
	
class GameObject; // forward declaration of GameObject to avoid circular dependency

// TODO: make a scene tracking feature

class Scene : public std::enable_shared_from_this<Scene> {
	friend class GameObject; // allow GameObject to access private members
public:
	Scene(const std::string& p_name = "New Scene");
	~Scene();

	void setName(const std::string& p_name) { m_name = p_name; }
	const std::string& getName() const { return m_name; }

	Ref<GameObject> createGameObject(const std::string& p_name = "Game Object");
	void destroyGameObject(Ref<GameObject> p_game_object);
	void destroyGameObject(const UUID& p_uuid);
	
	Ref<GameObject> getGameObject(const UUID& p_uuid);
	const std::unordered_map<UUID, Ref<GameObject>>& getAllGameObjects() const { return m_all_game_objects; }

	void update(const float p_dt);
	void render();

	// camera management
	void setActiveCamera(const Ref<Camera> p_camera) { m_active_camera = p_camera; }
	const Ref<Camera> getActiveCamera() const { return m_active_camera; } 
private:
	std::string m_name;
	Ref<Camera> m_active_camera;
	std::vector<Ref<GameObject>> m_root_game_objects; // game objects without parents
	std::unordered_map<UUID, Ref<GameObject>> m_all_game_objects; // all game objects in the scene with mapped UUID S
};

}
#endif // __SCENE_H__