#ifndef __MODELLOADER_H__
#define __MODELLOADER_H__

#include <zyklon_pch.h>
#include <Zyklon/Core/Core.h>
#include "Renderer/Mesh.h"
#include "Material/Material.h"

namespace Zyklon {
class ModelLoader {
public:
	ModelLoader(std::string &p_filepath);
	~ModelLoader();

private:
	Ref<Mesh> m_mesh;
	Ref<Material> m_material;
};

} // namespace Zyklon

#endif // __MODELLOADER_H__