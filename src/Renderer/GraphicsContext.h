#ifndef __GRAPHICSCONTEXT_H__
#define __GRAPHICSCONTEXT_H__

namespace Zyklon
{

    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

} // namespace Zyklon

#endif // __GRAPHICSCONTEXT_H__