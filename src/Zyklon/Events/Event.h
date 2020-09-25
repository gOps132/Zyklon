#ifndef __EVENT_H__
#define __EVENT_H__

#include "Zyklon/zyklon_pch.h"

#include "Zyklon/zyklon_exports.h"
#include "Zyklon/Core.h"
#include "Zyklon/Log.h"

namespace Zyklon
{

    // Events here are blocking
    // In the future buffer events will be most likely used

    /* Class that describes the event type */
    enum class EventType
    {
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

    enum EventCategory
    {
        NONE = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryButton = BIT(4)
    };

    // if MSVC compiler replace return EventType::type with return Event::##type
#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    /* Base Class For Events */
    class ZYKLON_EXPORT Event
    {
        friend class EventDispatcher;

    public:
        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char *GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
    private:
        Event &m_Event;
    private:
        template <typename T>
        using EventFn = std::function<bool(T &)>;
    public:
        EventDispatcher(Event &event)
            : m_Event(event)
        {
        }

        template <typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(*(T *)&m_Event);
                return true;
            }
            return false;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        return os << e.ToString();
    }

} // namespace Zyklon
#endif // __EVENT_H__