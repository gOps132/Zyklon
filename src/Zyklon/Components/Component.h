#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <zyklon_pch.h>

namespace Zyklon {

class GameObject; // forward declaration to avoid circular dependency
class Scene; // forward declaration to avoid circular dependency
class Component {
public:
	Component(const std::string& p_name = "Component");
	virtual ~Component() = default;

	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate(float p_delta_time) {}
protected:
	std::string m_name;
	bool m_active = true;
	std::weak_ptr<GameObject> m_owner;
	std::weak_ptr<Scene> m_scene; // does the component need the scene pointer?
};

} // namespace Zyklon

#endif // __COMPONENT_H__