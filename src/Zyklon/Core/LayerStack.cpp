#include "zyklon_pch.h"

#include "LayerStack.h"

namespace Zyklon {

LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
	for (Layer *layer : m_layers) {
		layer->onDetach();
		delete layer;
	}
}

void LayerStack::pushLayer(Layer *p_layer)
{
	m_layers.emplace(m_layers.begin() + m_layer_insert_index, p_layer);
	m_layer_insert_index++;

	p_layer->onAttach();
}

void LayerStack::pushOverlay(Layer *p_overlay)
{
	m_layers.emplace_back(p_overlay);

	p_overlay->onAttach();
}

void LayerStack::pop_layer(Layer *p_layer)
{
	auto it = std::find(m_layers.begin(),
						m_layers.begin() + m_layer_insert_index, p_layer);
	if (it != m_layers.begin() + m_layer_insert_index) {
		p_layer->onDetach();
		m_layers.erase(it);
		m_layer_insert_index--;
	}
}

void LayerStack::pop_overlay(Layer *p_overlay)
{
	auto it = std::find(m_layers.begin() + m_layer_insert_index, m_layers.end(),
						p_overlay);
	if (it != m_layers.end())
		p_overlay->onDetach();
	m_layers.erase(it);
}
} // namespace Zyklon