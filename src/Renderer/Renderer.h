#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Zyklon {

enum class RendererAPI { None = 0, OpenGL = 1 };

class Renderer {
  public:
    static void SetRendererAPI(RendererAPI p_RendererAPI) { s_RendererAPI = p_RendererAPI; }
    inline static RendererAPI GetAPI() { return s_RendererAPI; }

  private:
    static RendererAPI s_RendererAPI;
};

} // namespace Zyklon

#endif // __RENDERER_H__