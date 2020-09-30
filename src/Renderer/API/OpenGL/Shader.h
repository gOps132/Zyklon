#ifndef __SHADER_H__
#define __SHADER_H__

#include "Zyklon/zyklon_pch.h"

namespace Zyklon
{
    // TODO: this should be an openGL specific file andn should be renamed to shader.
    class Shader
    {
    private:

    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void bind();
        void unbind();
    private:
        uint32_t m_RendererID;
    };
    
} // namespace Zyklon


#endif // __SHADER_H__