#ifndef __MESHRENDERERCOMPONENT_H__
#define __MESHRENDERERCOMPONENT_H__

#include "Component.h"

#include <Zyklon/Core/Core.h>
#include <Zyklon/Renderer/Mesh.h>
#include <Zyklon/Renderer/Material/Material.h>

namespace Zyklon {

class MeshRendererComponent : public Component {
public:
	MeshRendererComponent(const Ref<Mesh> &p_mesh = nullptr,
						  const Ref<Material> &p_material = nullptr);
	virtual ~MeshRendererComponent() = default;

	Ref<Mesh> getMesh() { return m_mesh; }
	void setMesh(Ref<Mesh> &p_mesh) { m_mesh = p_mesh; }

	Ref<Material> getMaterial() { return m_material; }
	void setMaterial(Ref<Material> &p_material) { m_material = p_material; }

	virtual void onUpdate(float p_delta_time) override;

private:
	Ref<Mesh> m_mesh;
	Ref<Material> m_material;
};

} // namespace Zyklon

#endif // __MESHRENDERERCOMPONENT_H__