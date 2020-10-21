#ifndef __OPENGLSHADER_H__
#define __OPENGLSHADER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Shader.h"

namespace Zyklon {
// TODO: this should be an openGL specific file andn should be renamed to
// shader.
class OpenGLShader : public Shader {
  public:
    OpenGLShader(const std::string &vertexSource,
                 const std::string &fragmentSource);
    ~OpenGLShader();

    virtual void bind() override;
    virtual void unbind() override;

  private:
    uint32_t m_RendererID;
};

} // namespace Zyklon

#endif // __OPENGLSHADER_H__