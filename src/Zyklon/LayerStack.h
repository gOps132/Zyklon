#ifndef __LAYERSTACK_H__
#define __LAYERSTACK_H__

#include "Core.h"
#include "zyklon_exports.h"
#include "Layer.h"

#include <vector>

namespace Zyklon {

	class ZYKLON_EXPORT LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

} 
#endif // __LAYERSTACK_H__