#ifndef __SHADER_H__
#define __SHADER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon
{
    // TODO: this should be an openGL specific file andn should be renamed to shader.
    class Shader
    {
    public:
        Shader() {}
        virtual ~Shader() {}

        virtual void bind() = 0;
        virtual void unbind() = 0;
    private:
        uint32_t m_RendererID;
    };
    
} // namespace Zyklon


#endif // __SHADER_H__