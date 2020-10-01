#ifndef __OPENGLSHADER_H__
#define __OPENGLSHADER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Shader.h"

namespace Zyklon
{
    // TODO: this should be an openGL specific file andn should be renamed to shader.
    class OpenGLShader : public Shader
    {
    private:

    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        ~OpenGLShader();

        void bind();
        void unbind();
    private:
        uint32_t m_RendererID;
    };
    
} // namespace Zyklon

#endif // __OPENGLSHADER_H__