#ifndef __EVENT_H__
#define __EVENT_H__

#include <zyklon_pch.h>

#include <Zyklon/zyklon_exports.h>
#include <Zyklon/Core/Core.h>

namespace Zyklon {

// Events here are blocking
// In the future buffer events will be most likely used

/* Class that describes the event type */
enum class EventType {
	NONE = 0,

	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,

	AppTick,
	AppUpdate,
	AppRender,

	KeyPressed,
	KeyRelease,
	KeyTyped,

	MouseButtonPressed,
	MouseButtonRelease,
	MouseMoved,
	MouseScrolled
};

enum EventCategory {
	NONE = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryButton = BIT(4)
};

/* Event subclass helper macros for overriding member functions */
#define EVENT_CLASS_TYPE(type)                                                 \
	static EventType getStaticType() { return EventType::type; }             \
	virtual EventType getEventType() const override                          \
	{                                                                          \
		return getStaticType();                                              \
	}                                                                          \
	virtual const char *getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
	virtual int getCategoryFlags() const override { return category; }

/* Base Class For Events */
class ZYKLON_EXPORT Event {
	friend class EventDispatcher;

public:
	virtual ~Event(){};

	bool handled = false;

	virtual EventType getEventType() const = 0;
	virtual const char *getName() const = 0;
	virtual int getCategoryFlags() const = 0;

	virtual std::string toString() const { return getName(); }

	inline bool isInCategory(EventCategory category)
	{
		return getCategoryFlags() & category;
	}
};

class EventDispatcher {
private:
	Event &m_event;

private:
	template <typename T> using EventFn = std::function<bool(T &)>;

public:
	EventDispatcher(Event &event) : m_event(event) {}

	template <typename T> bool Dispatch(EventFn<T> func)
	{
		if (m_event.getEventType() == T::getStaticType()) {
			m_event.handled = func(*static_cast<T *>(&m_event));
			return true;
		}
		return false;
	}
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
	return os << e.toString();
}

} // namespace Zyklon

#endif // __EVENT_H__