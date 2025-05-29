#ifndef __LINUXINPUT_H__
#define __LINUXINPUT_H__

#include <Zyklon/Input/Input.h>

namespace Zyklon {

class LinuxInput : public Input {
protected:
	virtual bool keyPressedImpl(int keycode) override;

	virtual bool mouseBtnPressedImpl(int button) override;
	virtual std::pair<float, float> getMousePosImpl() override;
	virtual float getMouseXImpl() override;
	virtual float getMouseYImpl() override;
};

} // namespace Zyklon

#endif // __LINUXINPUT_H__