#ifndef __INPUT_H__
#define __INPUT_H__

#include <Zyklon/zyklon_exports.h>

namespace Zyklon {

class ZYKLON_EXPORT Input {
public:
	virtual ~Input() {}

	inline static bool keyPressed(int keycode)
	{
		return s_instance->keyPressedImpl(keycode);
	}

	inline static bool mouseBtnPressed(int button)
	{
		return s_instance->mouseBtnPressedImpl(button);
	}
	inline static std::pair<float, float> getMousePos()
	{
		return s_instance->getMousePosImpl();
	};
	inline static float get_mouse_x() { return s_instance->getMouseXImpl(); }
	inline static float get_mouse_y() { return s_instance->getMouseYImpl(); }

protected:
	virtual bool keyPressedImpl(int keycode) = 0;

	virtual bool mouseBtnPressedImpl(int button) = 0;
	virtual std::pair<float, float> getMousePosImpl() = 0;
	virtual float getMouseXImpl() = 0;
	virtual float getMouseYImpl() = 0;

private:
	static Input *s_instance;
};

} // namespace Zyklon

#endif // __INPUT_H__