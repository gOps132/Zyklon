#ifndef __APPLICATIONEVENT_H__
#define __APPLICATIONEVENT_H__

#include <Zyklon/zyklon_exports.h>

#include "Event.h"

namespace Zyklon {

class ZYKLON_EXPORT WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height)
	{
	}

	inline unsigned int getWidth() const { return m_Width; }
	inline unsigned int getHeight() const { return m_Height; }

	virtual std::string toString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	unsigned int m_Width, m_Height;
};

class ZYKLON_EXPORT WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ZYKLON_EXPORT AppTickEvent : public Event {
public:
	AppTickEvent() {}

	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ZYKLON_EXPORT AppUpdateEvent : public Event {
public:
	AppUpdateEvent() {}

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ZYKLON_EXPORT AppRenderEvent : public Event {
public:
	AppRenderEvent() {}

	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
} // namespace Zyklon
#endif // __APPLICATIONEVENT_H__