#ifndef __SHADER_H__
#define __SHADER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon
{
    // TODO: this should be an openGL specific file andn should be renamed to shader.
    class Shader
    {
    public:
        virtual Shader(const std::string& vertexSource, const std::string& fragmentSource) = 0;
        virtual ~Shader() = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    private:
        uint32_t m_RendererID;
    };
    
} // namespace Zyklon


#endif // __SHADER_H__