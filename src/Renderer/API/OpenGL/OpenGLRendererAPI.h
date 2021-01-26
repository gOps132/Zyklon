#ifndef __OPENGLRENDERERAPI_H__
#define __OPENGLRENDERERAPI_H__

#include "Renderer/RendererAPI.h"

namespace Zyklon {
class OpenGLRendererAPI : public RendererAPI {
public:
	virtual void set_clear_color(const glm::vec4 &color) override;
	virtual void clear() override;

	virtual void
	draw_indexed(const std::shared_ptr<VertexArray> &vertexArray) override;
};

} // namespace Zyklon

#endif // __OPENGLRENDERERAPI_H__