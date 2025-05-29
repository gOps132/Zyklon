#ifndef __KEYEVENT_H__
#define __KEYEVENT_H__

#include <Zyklon/zyklon_exports.h>

#include "Event.h"

namespace Zyklon {

class ZYKLON_EXPORT KeyEvent : public Event {
public:
	inline int GetKeyCode() const { return m_key_code; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(int keycode) : m_key_code(keycode) {}

	int m_key_code;
};

class ZYKLON_EXPORT KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_repeat_count(repeatCount)
	{
	}

	inline int GetRepeatCount() const { return m_repeat_count; }

	virtual std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_key_code << " (" << m_repeat_count
		   << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
private:
	int m_repeat_count;
};

class ZYKLON_EXPORT KeyTypedEvent : public KeyEvent {
public:
	KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

	virtual std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_key_code << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)
};

class ZYKLON_EXPORT KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

	virtual std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_key_code;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyRelease)
};
} // namespace Zyklon
#endif // __KEYEVENT_H__