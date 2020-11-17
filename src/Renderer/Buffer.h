#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Zyklon/zyklon_pch.h"
#include "Zyklon/Core.h"

namespace Zyklon {

enum class ShaderDataType : uint32_t {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool,
		Struct
};

static uint32_t shader_data_type_size(ShaderDataType p_type);

// Data Structure that holds vertex attributes. 
struct BufferElement {
		ShaderDataType type;
		std::string name;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferElement(ShaderDataType p_type, const std::string &p_name);
		
		uint32_t get_component_count() const;
};

class BufferLayout {
	public:
		BufferLayout(const std::initializer_list<BufferElement> &p_element);
		BufferLayout() = default;

		inline const std::vector<BufferElement> &get_elements() const { return m_elements; }

		void calc_offsets_and_strides();

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;
};

class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_layout(BufferLayout &layout) = 0;
		virtual const BufferLayout &get_layout() const = 0;

		static VertexBuffer *create(float *vertices, size_t size);
};

class IndexBuffer {
	public:
		virtual ~IndexBuffer(){};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		inline virtual uint32_t get_count() const = 0;

		static IndexBuffer *create(uint32_t *indices, size_t size);
};

} // namespace Zyklon

#endif // __BUFFER_H__