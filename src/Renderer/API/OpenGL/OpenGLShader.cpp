#include "Zyklon/zyklon_pch.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

#include "Zyklon/Core.h"
#include <glad/glad.h>

#include "OpenGLErrorManager.h"
#include "OpenGLShader.h"

namespace Zyklon {

OpenGLShader::OpenGLShader(const std::string &vertexSource,
                           const std::string &fragmentSource)
{
    // Create an empty vertex shader handle
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const char *source = vertexSource.c_str();
    GLCall(glShaderSource(vertexShader, 1, &source, 0));

    // Compile the vertex shader
    GLCall(glCompileShader(vertexShader));

    int isCompiled = 0;
    GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));
    if (isCompiled == GL_FALSE) {
        int maxLength = 0;
        GLCall(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength));

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        GLCall(glGetShaderInfoLog(vertexShader, maxLength, &maxLength,
                                  &infoLog[0]));

        // We don't need the shader anymore.
        GLCall(glDeleteShader(vertexShader));

        ZYKLON_CORE_ERROR("{0}", infoLog.data());
        ZYKLON_CORE_ASSERT(false, "Vertex Shader Compilation Error")

        return;
    }

    // Create an empty fragment shader handle
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = fragmentSource.c_str();
    GLCall(glShaderSource(fragmentShader, 1, &source, 0));

    // Compile the fragment shader
    GLCall(glCompileShader(fragmentShader));

    GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));
    if (isCompiled == GL_FALSE) {
        int maxLength = 0;
        GLCall(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength));

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        GLCall(glGetShaderInfoLog(fragmentShader, maxLength, &maxLength,
                                  &infoLog[0]));

        // We don't need the shader anymore.
        GLCall(glDeleteShader(fragmentShader));
        // Either of them. Don't leak shaders.
        GLCall(glDeleteShader(vertexShader));

        ZYKLON_CORE_ERROR("{0}", infoLog.data());
        ZYKLON_CORE_ASSERT(false, "Fragment Shader Compilation Error")

        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    m_RendererID = glCreateProgram();

    // Attach our shaders to our program
    GLCall(glAttachShader(m_RendererID, vertexShader));
    GLCall(glAttachShader(m_RendererID, fragmentShader));

    // Link our program
    GLCall(glLinkProgram(m_RendererID));

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    int isLinked = 0;
    GLCall(glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked));
    if (isLinked == GL_FALSE) {
        int maxLength = 0;
        GLCall(glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength));

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        GLCall(glGetProgramInfoLog(m_RendererID, maxLength, &maxLength,
                                   &infoLog[0]));

        // We don't need the program anymore.
        GLCall(glDeleteProgram(m_RendererID));
        // Don't leak shaders either.
        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));

        ZYKLON_CORE_ERROR("{0}", infoLog.data());
        ZYKLON_CORE_ASSERT(false, "Shader Compilation Error")

        return;
    }

    // Always detach shaders after a successful link.
    GLCall(glDetachShader(m_RendererID, vertexShader));
    GLCall(glDetachShader(m_RendererID, fragmentShader));
}

OpenGLShader::~OpenGLShader() { GLCall(glDeleteProgram(m_RendererID)); }

void OpenGLShader::bind() { GLCall(glUseProgram(m_RendererID)); }

void OpenGLShader::unbind() { GLCall(glUseProgram(0)); }

} // namespace Zyklon
