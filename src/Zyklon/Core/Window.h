#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <Zyklon/zyklon_exports.h>
#include "Core.h"
#include <Zyklon/Events/Event.h>

namespace Zyklon {
/* Default window parameters */
struct WindowProps {
	std::string title;
	unsigned int width;
	unsigned int height;

	WindowProps(const std::string &p_title = "Zyklon Engine",
				unsigned int p_width = 1280, unsigned int p_height = 720)
		: title(p_title), width(p_width), height(p_height)
	{
	}
};

/* This is just an interface to be implemented per DESKTOP platform */
class ZYKLON_EXPORT Window {
public:
	using EventCallbackFn = std::function<void(Event &)>;

	virtual ~Window() {}

	virtual void onUpdate() = 0;

	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;
	virtual float getTime() = 0;

	/* Window attributes */
	virtual void setEventCallback(const EventCallbackFn &callback) = 0;
	virtual void setVsync(bool enabled) = 0;
	virtual bool vsync() const = 0;

	virtual void *getNativeWindow() const = 0;

	/* if don't specify windows properties it creates the default using windows
	 * props */
	static Window *create(const WindowProps &props = WindowProps());
};
} // namespace Zyklon

#endif // __WINDOW_H__