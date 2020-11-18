#include "zyklon_pch.h"

#include "LayerStack.h"

namespace Zyklon {

LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
    for (Layer *layer : m_layers) {
        layer->on_detach();
        delete layer;
    }
}

void LayerStack::push_layer(Layer *p_layer)
{
    m_layers.emplace(m_layers.begin() + m_layer_insert_index, p_layer);
    m_layer_insert_index++;

    p_layer->on_attach();
}

void LayerStack::push_overlay(Layer *p_overlay)
{
    m_layers.emplace_back(p_overlay);

    p_overlay->on_attach();
}

void LayerStack::pop_layer(Layer *p_layer)
{
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_insert_index, p_layer);
    if (it != m_layers.begin() + m_layer_insert_index) {
        p_layer->on_detach();
        m_layers.erase(it);
        m_layer_insert_index--;
    }
}

void LayerStack::pop_overlay(Layer *p_overlay)
{
    auto it = std::find(m_layers.begin() + m_layer_insert_index, m_layers.end(), p_overlay);
    if (it != m_layers.end())
        p_overlay->on_detach();
    m_layers.erase(it);
}
} // namespace Zyklon