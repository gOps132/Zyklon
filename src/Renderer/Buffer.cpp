#include "Zyklon/zyklon_pch.h"

#include "Buffer.h"

#include <glad/glad.h>

namespace Zyklon {

uint32_t shader_data_type_size(ShaderDataType p_type)
{
    switch (p_type) {
        case ShaderDataType::Float:     return 4;
        case ShaderDataType::Float2:    return 4 * 2;
        case ShaderDataType::Float3:    return 4 * 3;
        case ShaderDataType::Float4:    return 4 * 4;
        case ShaderDataType::Mat3:      return 4 * 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4 * 4;
        case ShaderDataType::Int:       return 4;
        case ShaderDataType::Int2:      return 4 * 2;
        case ShaderDataType::Int3:      return 4 * 3;
        case ShaderDataType::Int4:      return 4 * 4;
        case ShaderDataType::Bool:      return 1;
    }

    ZYKLON_CORE_ASSERT(false, "Unkown shader data type");
    return 0;
}

BufferElement::BufferElement(ShaderDataType p_type, const std::string &p_name)
    : name(p_name), type(p_type), offset(0), size(0), normalized(true)
{
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &p_element)
    : m_elements(p_element)
{
    calc_offsets_and_strides();
}

uint32_t BufferElement::get_component_count() const
{
    switch (type) 
    {
        case ShaderDataType::Float:     return 1;
        case ShaderDataType::Float2:    return 2;
        case ShaderDataType::Float3:    return 3;
        case ShaderDataType::Float4:    return 4;
        case ShaderDataType::Mat3:      return 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4;
        case ShaderDataType::Int:       return 1;
        case ShaderDataType::Int2:      return 2;
        case ShaderDataType::Int3:      return 3;
        case ShaderDataType::Int4:      return 4;
        case ShaderDataType::Bool:      return 1;
    }
    ZYKLON_CORE_ASSERT(false, "Unkown Shader type");
    return 0;
}

void BufferLayout::calc_offsets_and_strides()
{
    uint32_t offset = 0;
    m_stride = 0;
    for (auto &element : m_elements) 
    {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
    }
}

} // namespace Zyklon