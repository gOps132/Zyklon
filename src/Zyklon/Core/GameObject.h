#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <zyklon_pch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Core.h"
#include "UUID.h"
#include "Scene.h"

#include <Zyklon/Components/Component.h>

namespace Zyklon {

class GameObject : public std::enable_shared_from_this<GameObject> {
	friend class Scene; // allow Scene to access private members

public:
	GameObject(const std::string &p_name = "GameObject");
	virtual ~GameObject() {};

	// --- IDENTIFICATION ---
	const std::string &getName() const { return m_name; }
	void setName(const std::string &p_name) { m_name = p_name; }

	const UUID &getUUID() const { return m_uuid; }
	void setUUID(const UUID &p_uuid);

	void setScene(const std::weak_ptr<Scene> p_scene) { m_scene = p_scene; }
	Ref<Scene> getScene() const { return m_scene.lock(); }

	// --- ACTIVE STATUS ---
	virtual void setActive(bool p_active);
	bool isActive() const { return m_active; }
	bool isActiveInHierarchy()
		const; // checks if the object and all its parents are active

	// --- TRANSFORMATION ---
	const glm::vec3 &getLocalPosition() const { return m_local_position; }
	void setLocalPosition(const glm::vec3 &p_position);

	const glm::quat &getLocalRotation() const { return m_local_rotation; }
	void setLocalRotation(const glm::quat &p_rotation);
	void setLocalRotation(const glm::vec3 &p_euler_angle);

	const glm::vec3 &getLocalScale() const { return m_local_scale; }
	void setLocalScale(const glm::vec3 &p_scale);

	const glm::mat4 &getLocalTransformationMatrix();
	const glm::mat4 &getWorldTransformationMatrix();

	// --- HIERARCHY MANAGEMENT ---
	void setParent(const Ref<GameObject> p_parent);
	Ref<GameObject> getParent() const { return m_parent.lock(); }
	void addChild(const Ref<GameObject> &p_child);
	void removeChild(const Ref<GameObject> &p_child);

	// --- COMPONENT MANAGEMENT ---
	template <typename T, typename... Args> Ref<T> addComponent(Args &&...args)
	{
		// check if a component of this type already exists
		if (getComponent<T>() != nullptr) {
			ZYKLON_CORE_WARN(
				"GameObject '{0}' already has component of type '{1}",
				m_name.c_str(), typeid(T).name());
			return getComponent<T>();
		}

		auto comp = createRef<T>(args...);
		comp->m_owner = shared_from_this();
		comp->m_scene = m_scene;

		m_components.push_back(comp);

		// store component by its type for quick lookup
		m_component_map[std::type_index(typeid(T))] = comp;

		comp->onAttach();

		return comp;
	}

	template <typename T> Ref<T> getComponent()
	{
		// for (const auto &comp : m_components) {
		// 	auto casted = std::dynamic_pointer_cast<T>(comp);
		// 	if (casted)
		// 		return casted; // return the first component of type T
		// }
		auto it = m_component_map.find(std::type_index(typeid(T)));
		if (it != m_component_map.end()) {
			// static_pointer_cast is safe here because we stored it with
			// typeid(T)
			// and we are retrieving it with the same typeid(T).
			return std::static_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	void removeComponent(const Ref<Component> &p_component);

	void onImGuiRender();

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
	std::unordered_map<std::type_index, Ref<Component>> m_component_map;

	std::string m_name;
	UUID m_uuid;
	bool m_active;
	uint32_t m_layer;

	// helper function to recalculate the world transformation matrix
	void invalidateWorldTransform();
};

} // namespace Zyklon

#endif // __GAMEOBJECT_H__