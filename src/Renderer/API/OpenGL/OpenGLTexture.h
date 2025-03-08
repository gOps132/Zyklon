#ifndef __OPENGLTEXTURE_H__
#define __OPENGLTEXTURE_H__

#include <Zyklon/Core/Core.h>

#include <Renderer/Texture.h>

#include <glad/glad.h>

namespace Zyklon
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureSpecification& p_specification);
		OpenGLTexture2D(const std::string& p_path);
		virtual ~OpenGLTexture2D();

		virtual const TextureSpecification& get_specification() const override { return m_specification; }
		virtual uint32_t get_width() const override { return m_width; }
		virtual uint32_t get_height() const override { return m_height; }
		virtual uint32_t get_renderer_id() const override { return m_renderer_id; }

		virtual const std::string& get_path() const override { return m_path; }

		virtual void set_data(void* p_data, uint32_t p_size);

		virtual void bind(uint32_t slot = 0) const override;

		virtual bool is_loaded() const override { return m_isloaded; }

		virtual bool operator==(const Texture& p_other) const
		{
			return m_renderer_id == p_other.get_renderer_id();
		}

	private:
		TextureSpecification m_specification;

		std::string m_path;
		bool m_isloaded = false;
		uint32_t m_width, m_height;
		uint32_t m_renderer_id;
		GLenum m_internal_format, m_data_format;
	};
} // namespace Zyklon

#endif // __OPENGLTEXTURE_H__