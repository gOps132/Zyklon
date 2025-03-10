#include <zyklon_pch.h>

#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Zyklon
{
	namespace Utils {
		
		static GLenum image_format_to_gl_format(ImageFormat p_format)
		{
			switch (p_format)
			{
				case ImageFormat::R8: return GL_R8;
				case ImageFormat::RGB8: return GL_RGB8;
				case ImageFormat::RGBA8: return GL_RGBA8;
				case ImageFormat::RGBA32F: return GL_RGBA32F;
				default: return GL_NONE;
			}
		}
		
		static GLenum image_format_to_internal_format(ImageFormat p_format)
		{
			switch (p_format)
			{
				case ImageFormat::R8: return GL_R8;
				case ImageFormat::RGB8: return GL_RGB8;
				case ImageFormat::RGBA8: return GL_RGBA8;
				case ImageFormat::RGBA32F: return GL_RGBA32F;
				default: return GL_NONE;
			}
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& p_specification)
		: m_specification(p_specification), m_width(m_specification.width), m_height(m_specification.height)
	{
		m_internal_format = Utils::image_format_to_internal_format(m_specification.format);
		m_data_format = Utils::image_format_to_gl_format(m_specification.format);
		
        glGenTextures(1, &m_renderer_id);
        glBindTexture(GL_TEXTURE_2D, m_renderer_id);
        glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_data_format, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& p_string)
		: m_path(p_string)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		data = stbi_load(m_path.c_str(), &width, &height, &channels, 0);
		
		if (data)
		{
			m_isloaded = true;
			
			m_width = width;
			m_height = height;
			
			GLenum internal_format = 0, data_format = 0;
			if (channels == 4)
			{
				internal_format = GL_RGBA8;
				data_format = GL_RGBA;
			}
			else if (channels == 3)
			{
				internal_format = GL_RGB8;
				data_format = GL_RGB;
			}

			m_internal_format = internal_format;
			m_data_format = data_format;
			
			ZYKLON_CORE_ASSERT(internal_format & data_format, "Format is not supported!");

            glGenTextures(1, &m_renderer_id);
            glBindTexture(GL_TEXTURE_2D, m_renderer_id);
            glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_data_format, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);        

			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_renderer_id);
	}


	void OpenGLTexture2D::set_data(void* p_data, uint32_t p_size)
	{
        uint32_t bpp = m_data_format == GL_RGBA ? 4 : 3;
        ZYKLON_CORE_ASSERT(p_size == m_width * m_height * bpp, "Data must be entire texture!");
        glBindTexture(GL_TEXTURE_2D, m_renderer_id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, p_data);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_renderer_id);
	}

} // namespace Zyklon
