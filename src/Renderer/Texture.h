#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <stb/stb_image.h>
#include <Zyklon/Core/Core.h>

namespace Zyklon
{
	enum class ImageFormat {
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	struct TextureSpecification {
		uint32_t width = 1;
		uint32_t height = 1;
		ImageFormat format = ImageFormat::RGBA8; // default?
		bool generate_mips = true;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual const TextureSpecification& get_specification() const = 0;
		
		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;
		virtual uint32_t get_renderer_id() const = 0;

		virtual const std::string& get_path() const = 0;

		virtual void set_data(void* p_data, uint32_t p_size) = 0;

		virtual void bind(uint32_t slot = 0) const = 0;

		virtual bool is_loaded() const = 0;

		virtual bool operator==(const Texture& p_other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> create(const TextureSpecification& p_specification);
		static Ref<Texture2D> create(const std::string& p_path);
	};
	
} // namespace Zyklon

#endif // __TEXTURE_H__