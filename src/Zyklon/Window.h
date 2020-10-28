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

    WindowProps(const std::string &title = "Zyklon Engine",
                unsigned int width = 1280, unsigned int height = 720)
        : title(title), width(width), height(height)
    {
    }
};

/* This is just an interface to be implemented per DESKTOP platform */
class ZYKLON_EXPORT Window {
  public:
    using EventCallbackFn = std::function<void(Event &)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    /* Window attributes */
    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
    virtual void SetVsync(bool enabled) = 0;
    virtual bool IsVsync() const = 0;

    virtual void *GetNativeWindow() const = 0;

    /* if don't specify windows properties it creates the default using windows
     * props */
    static Window *Create(const WindowProps &props = WindowProps());
};
} // namespace Zyklon

#endif // __WINDOW_H__