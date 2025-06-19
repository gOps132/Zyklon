#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <zyklon_pch.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Core.h"
#include "UUID.H"
#include "Scene.h"
#include "Component.h"

namespace Zyklon {

class GameObject {
public:
	GameObject(const std::string& p_name = "GameObject");
	virtual ~GameObject() {};
	
	// --- IDENTIFICATION --- 
	const std::string& getName() const { return m_name; }
	void setName(const std::string& p_name) { m_name = p_name; }
	
	const UUID& getUUID() const { return m_uuid; }
	void setUUID(const UUID& p_uuid);

	void setScene(const std::weak_ptr<Scene> p_scene) { m_scene = p_scene; }
	Ref<Scene> getScene() const { return m_scene.lock(); }

	// --- ACTIVE STATUS ---
	virtual void setActive(bool p_active); 
	bool isActive() const { return m_active; }
	bool isActiveInHierarchy() const; // checks if the object and all its parents are active

	// --- TRANSFORMATION ---
	const glm::vec3& getLocalPosition() const { return m_local_position; }
	void setLocalPosition(const glm::vec3& p_position);

	const glm::quat& getLocalRotation() const { return m_local_rotation; }
	void setLocalRotation(const glm::quat& p_rotation);
	void setLocalRotation(const glm::vec3& p_euler_angle);

	const glm::vec3& getLocalScale() const { return m_local_scale; }
	void setLocalScale(const glm::vec3& p_scale);

	glm::mat4 getLocalTransformationMatrix() const;
	glm::mat4 getWorldTransformationMatrix() const;

	// --- HIERARCHY MANAGEMENT ---
	void setParent(const Ref<GameObject> p_parent);
	Ref<GameObject> getParent() const { return m_parent.lock(); }

	void addChild(const Ref<GameObject>& p_child);
	// remove child ownership, does not destroy the child
	void removeChild(const Ref<GameObject> &p_child);

	// --- COMPONENT MANAGEMENT ---
	// add, get, getall, remove specific
	template<typename T, typename... Args>
	Ref<T> addComponent(Argss&& ...args);

protected:
	// local transform
	glm::vec3 m_local_position;
	glm::quat m_local_rotation;
	glm::vec3 m_local_scale;
	mutable glm::mat4 m_local_transformation_matrix;
	bool m_is_local_transformation_dirty = true;

	// world transform
	mutable glm::mat4 m_world_transformation_matrix;
	bool m_is_world_transformation_dirty = true;

	// scene
	std::weak_ptr<Scene> m_scene;

	// hierarchy
	std::weak_ptr<GameObject> m_parent;
	std::vector<Ref<GameObject>> m_children;

	// components
	std::vector<Ref<Component>> m_components;
	
	std::string m_name;
	UUID m_uuid;
	bool m_active;
	uint32_t m_layer;

	// helper function to recalculate the world transformation matrix
	void invalidateWorldTransform();
};

}

#endif // __GAMEOBJECT_H__