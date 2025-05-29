#ifndef __LAYERSTACK_H__
#define __LAYERSTACK_H__

#include <Zyklon/zyklon_exports.h>
#include "zyklon_pch.h"

#include "Core.h"
#include "Layer.h"

namespace Zyklon {

class ZYKLON_EXPORT LayerStack {
public:
	LayerStack();
	~LayerStack();

	void pushLayer(Layer *p_layer);
	void pushOverlay(Layer *p_overlay);
	void pop_layer(Layer *p_layer);
	void pop_overlay(Layer *p_overlay);

	std::vector<Layer *>::iterator begin() { return m_layers.begin(); }
	std::vector<Layer *>::iterator end() { return m_layers.end(); }

private:
	std::vector<Layer *> m_layers;
	unsigned int m_layer_insert_index = 0;
};

} // namespace Zyklon
#endif // __LAYERSTACK_H__