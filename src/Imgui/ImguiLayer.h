#ifndef __IMGUILAYER_H__
#define __IMGUILAYER_H__

#include <Zyklon/zyklon_exports.h>

#include <Zyklon/Core/Layer.h>

#include <Zyklon/Events/ApplicationEvent.h>
#include <Zyklon/Events/KeyEvent.h>
#include <Zyklon/Events/MouseEvent.h>

namespace Zyklon {

class ZYKLON_EXPORT ImGuiLayer : public Layer {
public:
	ImGuiLayer();
	~ImGuiLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onImguiRender() override;

	/* Layers to do their own Imgui Rendering */
	/* Begin a new frame */
	void begin();
	void end();

private:
	float m_Time = 0.0f;
};

} // namespace Zyklon

#endif // __IMGUILAYER_H__