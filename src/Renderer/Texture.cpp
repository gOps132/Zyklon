#include <zyklon_pch.h>

#include <Zyklon/Core/Core.h>

#include "Texture.h"
#include "RendererAPI.h"
#include "Renderer.h"

#include "API/OpenGL/OpenGLTexture.h"

namespace Zyklon 
{
	Ref<Texture2D> Texture2D::create(const TextureSpecification& p_specification)
	{
		switch (Renderer::get_api())
		{
			case RendererAPI::API::None:	ZYKLON_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
			case RendererAPI::API::OpenGL:	return create_ref<OpenGLTexture2D>(p_specification);
		}
	}
	
	Ref<Texture2D> Texture2D::create(const std::string& p_path)
	{
		switch (Renderer::get_api())
		{
			case RendererAPI::API::None:	ZYKLON_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
			case RendererAPI::API::OpenGL:	return create_ref<OpenGLTexture2D>(p_path);
		}
	}
} // Zyklon