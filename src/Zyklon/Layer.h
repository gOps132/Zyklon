#ifndef __LAYER_H__
#define __LAYER_H__

#include "Events/Event.h"
#include "Zyklon/Core.h"

#include "zyklon_exports.h"

namespace Zyklon {

class ZYKLON_EXPORT Layer {
  public:
    Layer(const std::string &p_debug_name = "Layer");
    virtual ~Layer() {}

    virtual void on_attach() {}
    virtual void on_detach() {}

    virtual void on_update() {}
    virtual void on_event(Event &event) {}

    virtual void on_imgui_render() {}

    inline const std::string &get_name() const { return m_debug_name; }

  protected:
    std::string m_debug_name;
};

} // namespace Zyklon
#endif // __LAYER_H__