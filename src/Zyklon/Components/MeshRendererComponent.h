#ifndef __MESHRENDERERCOMPONENT_H__
#define __MESHRENDERERCOMPONENT_H__

#include "Component.h"
#include <Zyklon/Renderer/Mesh.h>
#include <Zyklon/Renderer/Material.h>

namespace Zyklon {

class MeshRendererComponent : public Component
{
public:
	MeshRendererComponent();
	virtual ~MeshRendererComponent() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(float p_delta_time) override;
private:
	
};

} // namespace Zyklon

#endif // __MESHRENDERERCOMPONENT_H__