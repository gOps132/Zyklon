#ifndef __IMGUILAYER_H__
#define __IMGUILAYER_H__

#include "Zyklon/zyklon_exports.h"
#include "Zyklon/Layer.h"

#include "Zyklon/Events/MouseEvent.h"
#include "Zyklon/Events/KeyEvent.h"
#include "Zyklon/Events/ApplicationEvent.h"

namespace Zyklon
{

    class ZYKLON_EXPORT ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnImGuiRender() override;
        
        /* Layers to do their own Imgui Rendering */
        /* Begin a new frame */
        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };


} // namespace Zyklon

#endif // __IMGUILAYER_H__