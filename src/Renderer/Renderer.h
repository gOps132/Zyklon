#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Zyklon {

enum RendererAPI {
   None = 0, 
   OpenGL = 1 
};

class Renderer {
  public:
	/**
	 *  Static Function to set the renderer API 
	 *  Default RendererAPI::OpenGL 
	 */
    static void set_renderer_api(RendererAPI p_renderer_api = OpenGL)
    {
        s_RendererAPI = p_renderer_api;
    }
	
    inline static RendererAPI get_api() { return s_RendererAPI; }

  private:
    static RendererAPI s_RendererAPI;
};

} // namespace Zyklon

#endif // __RENDERER_H__