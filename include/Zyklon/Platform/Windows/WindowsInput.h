#ifndef __WINDOWSINPUT_H__
#define __WINDOWSINPUT_H__

#include "Zyklon/Input/Input.h"

namespace Zyklon
{

    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override; 

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
    
} // namespace Zyklon

#endif // __WINDOWSINPUT_H__