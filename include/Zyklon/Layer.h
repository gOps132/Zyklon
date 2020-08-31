#ifndef __LAYER_H__
#define __LAYER_H__

#include "Zyklon/Core.h"
#include "Events/Event.h"
#include "zyklon_exports.h"

namespace Zyklon {

	class ZYKLON_EXPORT Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
#endif // __LAYER_H__