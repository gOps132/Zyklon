#ifndef __INPUT_H__
#define __INPUT_H__

#include "Zyklon/zyklon_exports.h"

namespace Zyklon {

class ZYKLON_EXPORT Input {
  public:
    inline static bool key_pressed(int keycode)
    {
        return s_instance->key_pressed_impl(keycode);
    }

    inline static bool mouse_btn_pressed(int button)
    {
        return s_instance->mouse_btn_pressed_impl(button);
    }
    inline static std::pair<float, float> get_mouse_pos()
    {
        return s_instance->get_mouse_pos_impl();
    };
    inline static float get_mouse_x() { return s_instance->get_mouse_x_impl(); }
    inline static float get_mouse_y() { return s_instance->get_mouse_y_impl(); }

  protected:
    virtual bool key_pressed_impl(int keycode) = 0;

    virtual bool mouse_btn_pressed_impl(int button) = 0;
    virtual std::pair<float, float> get_mouse_pos_impl() = 0;
    virtual float get_mouse_x_impl() = 0;
    virtual float get_mouse_y_impl() = 0;

  private:
    static Input *s_instance;
};

} // namespace Zyklon

#endif // __INPUT_H__