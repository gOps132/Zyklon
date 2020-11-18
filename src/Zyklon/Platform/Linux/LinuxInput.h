#ifndef __LINUXINPUT_H__
#define __LINUXINPUT_H__

#include "Zyklon/Input/Input.h"

namespace Zyklon {

class LinuxInput : public Input {
  protected:
    virtual bool key_pressed_impl(int keycode) override;

    virtual bool mouse_btn_pressed_impl(int button) override;
    virtual std::pair<float, float> get_mouse_pos_impl() override;
    virtual float get_mouse_x_impl() override;
    virtual float get_mouse_y_impl() override;
};

} // namespace Zyklon

#endif // __LINUXINPUT_H__