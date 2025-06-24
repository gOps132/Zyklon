#include <zyklon_pch.h>

#include <glad/glad.h>

#include "Renderer.h"

#include <Platform/OpenGL/OpenGLBuffer.h>

#include "Buffer.h"


namespace Zyklon {

VertexBuffer *VertexBuffer::create(float *p_vertices, size_t p_size)
{
	switch (RendererAPI::getAPI()) {
	case RendererAPI::API::None:
		ZYKLON_CORE_ASSERT(false, "No Renderer API is supported. !");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return new OpenGLVertexBuffer(p_vertices, p_size);
	}
	ZYKLON_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

IndexBuffer *IndexBuffer::create(uint32_t *p_indices, size_t p_size)
{
	switch (Renderer::getAPI()) {
	case RendererAPI::API::None:
		ZYKLON_CORE_ASSERT(false, "No Renderer API is supported!");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return new OpenGLIndexBuffer(p_indices, p_size);
	}
	ZYKLON_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

uint32_t shaderDataTypeSize(ShaderDataType p_type)
{
	switch (p_type) {
	case ShaderDataType::Float:
		return 4;
	case ShaderDataType::Float2:
		return 4 * 2;
	case ShaderDataType::Float3:
		return 4 * 3;
	case ShaderDataType::Float4:
		return 4 * 4;
	case ShaderDataType::Mat3:
		return 4 * 3 * 3;
	case ShaderDataType::Mat4:
		return 4 * 4 * 4;
	case ShaderDataType::Int:
		return 4;
	case ShaderDataType::Int2:
		return 4 * 2;
	case ShaderDataType::Int3:
		return 4 * 3;
	case ShaderDataType::Int4:
		return 4 * 4;
	case ShaderDataType::Bool:
		return 1;
	}

	ZYKLON_CORE_ASSERT(false, "Unkown shader data type");
	return 0;
}

BufferElement::BufferElement(ShaderDataType p_type, const std::string &p_name,
							 bool p_normalized = false)
	: name(p_name), type(p_type), offset(0),
	  size(shaderDataTypeSize(p_type)), normalized(p_normalized)
{
}

BufferLayout::BufferLayout(
	const std::initializer_list<BufferElement> &p_element)
	: m_elements(p_element)
{
	calcOffsetsAndStrides();
}

uint32_t BufferElement::getComponentCount() const
{
	switch (type) {
	case ShaderDataType::Float:
		return 1;
	case ShaderDataType::Float2:
		return 2;
	case ShaderDataType::Float3:
		return 3;
	case ShaderDataType::Float4:
		return 4;
	case ShaderDataType::Mat3:
		return 3 * 3;
	case ShaderDataType::Mat4:
		return 4 * 4;
	case ShaderDataType::Int:
		return 1;
	case ShaderDataType::Int2:
		return 2;
	case ShaderDataType::Int3:
		return 3;
	case ShaderDataType::Int4:
		return 4;
	case ShaderDataType::Bool:
		return 1;
	}
	ZYKLON_CORE_ASSERT(false, "Unkown Shader type");
	return 0;
}

void BufferLayout::calcOffsetsAndStrides()
{
	uint32_t offset = 0;
	m_stride = 0;
	for (BufferElement &element : m_elements) {
		element.offset = offset;
		offset += element.size;
		m_stride += element.size;
	}
}

} // namespace Zyklon