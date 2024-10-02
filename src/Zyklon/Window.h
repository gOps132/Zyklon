#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Core.h"
#include "Events/Event.h"
#include "zyklon_exports.h"

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

	virtual void on_update() = 0;

	virtual unsigned int get_width() const = 0;
	virtual unsigned int get_height() const = 0;
	virtual float get_time() = 0;

	/* Window attributes */
	virtual void set_event_callback(const EventCallbackFn &callback) = 0;
	virtual void set_vsync(bool enabled) = 0;
	virtual bool vsync() const = 0;

	virtual void *get_native_window() const = 0;

	/* if don't specify windows properties it creates the default using windows
	 * props */
	static Window *create(const WindowProps &props = WindowProps());
};
} // namespace Zyklon

#endif // __WINDOW_H__