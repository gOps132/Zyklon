#include "Zyklon/Core.h"
#include "Zyklon/zyklon_pch.h"

#include <glad/glad.h>

#include "OpenGLErrorManager.h"

void GLClearError()
{
    //    infinite loop if it has errors
    while (glGetError() != GL_NO_ERROR)
        ;
}

int GLLogCall(const char *function, const char *file, int line)
{
    if (GLenum error = glGetError()) {

        ZYKLON_CORE_ERROR("OPENGL ERROR: ");
        ZYKLON_CORE_ERROR("     FUNCTION: {0}", function);
        ZYKLON_CORE_ERROR("     FILE: {0}", file);
        ZYKLON_CORE_ERROR("     LINE: {0}", line);

        //        TODO: make this faster with the c api
        std::stringstream ss;
        ss << std::hex << error;
        std::string res(ss.str());
        std::string new_string = std::string(4 - res.length(), '0') + res;
        std::ifstream stream("lib/glad/include/glad/glad.h");
        std::string line;
        while (getline(stream, line)) {
            if (line.find(new_string) != std::string::npos)
                std::cout << line << std::endl;
        }

        return -1;
    }

    return 1;
}
