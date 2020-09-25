#ifndef __LINUXINPUT_H__
#define __LINUXINPUT_H__

#include "Zyklon/Input/Input.h"

namespace Zyklon
{

    class LinuxInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override; 

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
    
} // namespace Zyklon

#endif // __LINUXINPUT_H__