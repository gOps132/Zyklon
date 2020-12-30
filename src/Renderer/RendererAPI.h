#ifndef __RENDERERAPI_H__
#define __RENDERERAPI_H__

#include "Buffer.h"

#include <glm/glm.hpp>

namespace Zyklon
{
    class RendererAPI
    {
    public:
        static void set_renderer_api();
            
        virtual void set_clear_color(const glm::vec2& color) = 0;
        virtual void clear() = 0;
        
        virtual void draw_index(const std::shared_ptr<VertexArray> &p_vertex_array);

        inline static const API get_api const { return const s_api; }
        
    private:
        enum class API {
            None = 0,
            OpenGL = 1
        };

        static API s_api;
    };
    
} // namespace Zyklon



#endif // __RENDERERAPI_H__