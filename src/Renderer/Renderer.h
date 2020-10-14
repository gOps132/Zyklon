#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Zyklon {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};

}
	

#endif // __RENDERER_H__