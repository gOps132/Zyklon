#include "RendererAPI.h"

namespace Zyklon {

RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

void RendererAPI::set_renderer_api(const RendererAPI::API &p_api) 
{
	RendererAPI::s_api = p_api;
}

} // namespace Zyklon
