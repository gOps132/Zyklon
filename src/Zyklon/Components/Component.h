#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/UUID.h>
#include <Zyklon/Core/Core.h>

namespace Zyklon {

// forward declarations to avoid circular dependency
class GameObject;
class Scene;

class Component {
	friend class GameObject;

public:
	Component(const std::string &p_name = "Component");
	virtual ~Component() = default;

	bool isActive() const { return m_active; }
	void setActive(bool p_active);

	std::string &getName() { return m_name; }
	void setName(std::string &p_name) { m_name = p_name; }
	UUID &getUUID() { return m_uuid; }

	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate(float p_delta_time) {}
	virtual void onImguiRender() {}

	Ref<GameObject> getOwner() const { return m_owner.lock(); }
	Ref<Scene> getScene() const { return m_scene.lock(); }

protected:
	std::string m_name;
	UUID m_uuid;

	bool m_active = true;
	std::weak_ptr<GameObject> m_owner;
	// so we can interact with other game components and for
	// contextual information needed for each unique system
	std::weak_ptr<Scene> m_scene;
};

} // namespace Zyklon

#endif // __COMPONENT_H__