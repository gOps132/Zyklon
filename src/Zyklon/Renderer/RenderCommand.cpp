#include "RenderCommand.h"

#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Zyklon {

RendererAPI *RenderCommand::s_renderer_api = new OpenGLRendererAPI;

} // namespace Zyklon