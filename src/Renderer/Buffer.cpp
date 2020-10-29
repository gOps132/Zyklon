#include "Zyklon/zyklon_pch.h"

#include "Buffer.h"

#include <glad/glad.h>

namespace Zyklon {

uint32_t ShaderDataTypeSize(ShaderDataType pType)
{
    switch (pType) {
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

BufferElement::BufferElement(ShaderDataType pType, const std::string &pName)
    : Name(pName), Type(pType), Offset(0), Size(0)
{
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &element)
    : m_BufferElements(element)
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
    uint32_t l_offset = 0;
    m_Stride = 0;
    for (auto &element : m_BufferElements) 
    {
        element.Offset = l_offset;
        l_offset += element.Size;
        m_Stride += element.Size;
    }
}

} // namespace Zyklon
