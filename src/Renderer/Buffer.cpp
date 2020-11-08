#include "Zyklon/zyklon_pch.h"

#include "Buffer.h"

#include <glad/glad.h>

namespace Zyklon {

uint32_t ShaderDataTypeSize(ShaderDataType p_type)
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

    ZYKLON_CORE_ASSERT(false, "Unkown shader data Type");
    return 0;
}

BufferElement::BufferElement(ShaderDataType p_type, const std::string &p_name, bool p_normalized)
    : Name(p_name), Type(p_type), Offset(0), Size(0), Normalized(p_normalized)
{
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &p_element)
    : m_BufferElements(p_element)
{
    calculateOffsetsAndStrides();
}

uint32_t BufferElement::GetComponentCount() const
{
    switch (Type) 
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


void BufferLayout::calculateOffsetsAndStrides()
{
    uint32_t offset = 0;
    m_Stride = 0;
    for (auto &element : m_BufferElements) 
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}

} // namespace Zyklon
