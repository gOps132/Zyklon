#include "Component.h"

namespace Zyklon {

Component::Component(const std::string &p_name) : m_name(p_name), m_uuid() {}

void Component::setActive(bool p_active)
{
#ifdef ZYKLON_DEBUG
	if (m_active == p_active) {
		ZYKLON_CORE_WARN(
			"Component {0} is already in the desired active state: {1}", m_name,
			p_active);
		return; // no change needed
	}
	m_active = p_active;
#else
	p_active = p_active;
#endif
}

} // namespace Zyklon