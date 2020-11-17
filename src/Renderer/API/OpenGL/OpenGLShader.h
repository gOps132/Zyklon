#ifndef __OPENGLSHADER_H__
#define __OPENGLSHADER_H__

#include "Zyklon/zyklon_pch.h"

#include "Renderer/Shader.h"

namespace Zyklon {
// TODO: this should be an openGL specific file andn should be renamed to
// shader.
class OpenGLShader : public Shader {
  public:
    OpenGLShader(const std::string &p_filepath);
    ~OpenGLShader();

    virtual void bind() override;
    virtual void unbind() override;

  private:
    ShaderProgramSource m_shader_source;
    uint32_t m_renderer_id;
};

} // namespace Zyklon

#endif // __OPENGLSHADER_H__