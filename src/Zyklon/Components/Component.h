#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <zyklon_pch>

namespace Zyklon {

class Component {
public:
	Component(const std::string& p_name = "Component");
	virtual ~Component() = default;

	virtual void onAttach() {}
protected:	
	std::string m_name;
	bool m_active = true;
	std::weak_ptr<GameObject> m_owner;
	std::weak_ptr<Scene> m_scene; // does the component need the scene pointer?
}

} // namespace Zyklon

#endif // __COMPONENT_H__