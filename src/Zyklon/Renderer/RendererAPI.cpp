#include "RendererAPI.h"

namespace Zyklon {

RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

void RendererAPI::setRendererAPI(const RendererAPI::API &p_api) 
{
	RendererAPI::s_api = p_api;
}

} // namespace Zyklon
