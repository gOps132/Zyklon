#ifndef __VERTEXBUFFERLAYOUT_H__
#define __VERTEXBUFFERLAYOUT_H__

#include "Zyklon/Core.h"

#include <glad/glad.h>

#include "OpenGLErrorManager.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        return 0;
    }
};

class VertexBufferLayout {
    // FIXME: Tmeplate error, may be a problem with c++ 14 standard
  public:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

    VertexBufferLayout() : m_Stride(0) {}

    template <typename T> void Push(int count)
    {
        const unsigned int type =
            (unsigned int[]){
                0, GL_FLOAT, GL_UNSIGNED_INT,
                GL_UNSIGNED_BYTE}[1 * std::is_same<T, float>::value +
                                  2 * std::is_same<T, unsigned int>::value +
                                  3 * std::is_same<T, unsigned char>::value];

        m_Elements.push_back(
            {type, static_cast<unsigned int>(count), GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(type);
    }

    inline const std::vector<VertexBufferElement> GetElement() const
    {
        return m_Elements;
    }
    inline unsigned int GetStride() const { return m_Stride; }
};

#endif // __VERTEXBUFFERLAYOUT_H__
