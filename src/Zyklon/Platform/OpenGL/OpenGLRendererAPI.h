#ifndef __OPENGLRENDERERAPI_H__
#define __OPENGLRENDERERAPI_H__

#include <Zyklon/Core/Core.h>

#include <Renderer/RendererAPI.h>

namespace Zyklon {
class OpenGLRendererAPI ZYKLON_OPENGL_FINAL : public RendererAPI {
public:
	virtual void setViewport(int p_x, int p_y, int p_width, int p_height) override;
	virtual void setClearColor(const glm::vec4 &color) override;
	virtual void clear() override;

	virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
	virtual void drawArrays(const std::shared_ptr<VertexArray> &p_vertex_array, uint32_t p_indices) override;
};

} // namespace Zyklon

#endif // __OPENGLRENDERERAPI_H__