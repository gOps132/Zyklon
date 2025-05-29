#ifndef __GRAPHICSCONTEXT_H__
#define __GRAPHICSCONTEXT_H__

#include <GLFW/glfw3.h>

#include "Renderer.h"

namespace Zyklon {

class GraphicsContext {
public:
	virtual ~GraphicsContext() {}

	virtual void init() = 0;
	virtual void swapBuffers() = 0;

	static GraphicsContext *create(GLFWwindow *p_window);
};
} // namespace Zyklon

#endif // __GRAPHICSCONTEXT_H__