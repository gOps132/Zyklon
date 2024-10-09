#ifndef __KEYEVENT_H__
#define __KEYEVENT_H__

#include <Zyklon/zyklon_exports.h>

#include "Event.h"

namespace Zyklon {

class ZYKLON_EXPORT KeyEvent : public Event {
public:
	inline int GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(int keycode) : m_KeyCode(keycode) {}

	int m_KeyCode;
};

class ZYKLON_EXPORT KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount)
	{
	}

	inline int GetRepeatCount() const { return m_RepeatCount; }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
		   << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
private:
	int m_RepeatCount;
};

class ZYKLON_EXPORT KeyTypedEvent : public KeyEvent {
public:
	KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)
};

class ZYKLON_EXPORT KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyRelease)
};
} // namespace Zyklon
#endif // __KEYEVENT_H__