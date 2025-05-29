#ifndef __LAYER_H__
#define __LAYER_H__

#include <Zyklon/zyklon_exports.h>
#include "Core.h"
#include "Timestep.h"

#include <Zyklon/Events/Event.h>

namespace Zyklon {

class ZYKLON_EXPORT Layer {
public:
	Layer(const std::string &p_debug_name = "Layer");
	virtual ~Layer() {}

	virtual void onAttach() {}
	virtual void onDetach() {}

	virtual void onUpdate(Timestep ts) {}
	virtual void onEvent(Event &event) {}

	virtual void onImguiRender() {}

	inline const std::string &getName() const { return m_debug_name; }

protected:
	std::string m_debug_name;
};

} // namespace Zyklon
#endif // __LAYER_H__