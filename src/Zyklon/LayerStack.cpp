#include "zyklon_pch.h"

#include "LayerStack.h"

namespace Zyklon {

LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
    for (Layer *layer : m_layers) {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::ls_push_layer(Layer *layer)
{
    m_layers.emplace(m_layers.begin() + m_layer_insert_index, layer);
    m_layer_insert_index++;

    layer->OnAttach();
}

void LayerStack::ls_push_overlay(Layer *overlay)
{
    m_layers.emplace_back(overlay);

    overlay->OnAttach();
}

void LayerStack::ls_pop_layer(Layer *layer)
{
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_insert_index,
                        layer);
    if (it != m_layers.begin() + m_layer_insert_index) {
        layer->OnDetach();
        m_layers.erase(it);
        m_layer_insert_index--;
    }
}

void LayerStack::ls_pop_overlay(Layer *overlay)
{
    auto it = std::find(m_layers.begin() + m_layer_insert_index, m_layers.end(),
                        overlay);
    if (it != m_layers.end())
        overlay->OnDetach();
    m_layers.erase(it);
}
} // namespace Zyklon