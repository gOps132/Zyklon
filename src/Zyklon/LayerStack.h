#ifndef __LAYERSTACK_H__
#define __LAYERSTACK_H__

#include "Core.h"
#include "Layer.h"
#include "zyklon_exports.h"

#include <vector>

namespace Zyklon {

class ZYKLON_EXPORT LayerStack {
  public:
    LayerStack();
    ~LayerStack();

    void ls_push_layer(Layer *layer);
    void ls_push_overlay(Layer *overlay);
    void ls_pop_layer(Layer *layer);
    void ls_pop_overlay(Layer *overlay);

    std::vector<Layer *>::iterator ls_begin() { return m_layers.begin(); }
    std::vector<Layer *>::iterator end() { return m_layers.end(); }

  private:
    std::vector<Layer *> m_layers;
    unsigned int m_layer_insert_index = 0;
};

} // namespace Zyklon
#endif // __LAYERSTACK_H__