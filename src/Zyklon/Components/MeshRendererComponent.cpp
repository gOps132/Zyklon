#include "MeshRendererComponent.h"

#include <Zyklon/Core/GameObject.h>
#include <Zyklon/Core/Scene.h>

#include <imgui-test/imgui.h>

namespace Zyklon {
MeshRendererComponent::MeshRendererComponent(const Ref<Mesh> &p_mesh,
											 const Ref<Material> &p_material)
	: Component("Mesh Renderer Component"), m_mesh(p_mesh),
	  m_material(p_material)
{
}

void MeshRendererComponent::onUpdate(float p_delta_time) {}

void MeshRendererComponent::onImguiRender()
{
	if (m_material)
		m_material->renderGUI();
}

} // namespace Zyklon
