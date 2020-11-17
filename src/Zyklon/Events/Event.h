#ifndef __EVENT_H__
#define __EVENT_H__

#include "Zyklon/zyklon_pch.h"

#include "Zyklon/Core.h"
#include "Zyklon/Log.h"
#include "Zyklon/zyklon_exports.h"

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

// TODO: Verify this
/* Event subclass helper macros for overriding member functions */
#define EVENT_CLASS_TYPE(type) \
    static EventType get_static_type() { return EventType::type; } \
    virtual EventType get_event_type() const override { return get_static_type(); } \
    virtual const char *get_name() const override { return #type; } 

#define EVENT_CLASS_CATEGORY(category)                                         \
    virtual int get_category_flags() const override { return category; }

/* Base Class For Events */
class ZYKLON_EXPORT Event {
    friend class EventDispatcher;

  public:
    bool handled = false;

    virtual EventType get_event_type() const = 0;
    virtual const char *get_name() const = 0;
    virtual int get_category_flags() const = 0;

    virtual std::string to_string() const { return get_name(); }

    inline bool is_in_category(EventCategory category)
    {
        return get_category_flags() & category;
    }
};

class EventDispatcher {
  private:
    Event &m_Event;

  private:
    template <typename T> using EventFn = std::function<bool(T &)>;

  public:
    EventDispatcher(Event &event) : m_Event(event) {}

    template <typename T> bool Dispatch(EventFn<T> func)
    {
        if (m_Event.get_event_type() == T::get_static_type()) {
            m_Event.handled = func(*(T *)&m_Event);
            return true;
        }
        return false;
    }
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.to_string();
}

} // namespace Zyklon
#endif // __EVENT_H__