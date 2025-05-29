#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <zyklon_pch.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "UUID.H"

namespace Zyklon {

class GameObject {
public:
	GameObject(const std::string& p_name = "GameObject");
	virtual ~GameObject() {};
	
	// --- IDENTIFICATION --- 
	const std::string& getName() const { return m_name; }
	void setName(const std::string& p_name) { m_name = p_name; }
	
	const UUID& getUUID() const { return m_uuid; }
	void setUUID(const UUID& p_uuid);

	// --- ACTIVE STATUS ---
	virtual void setActive(bool p_active); 
	bool isActive() const { return m_active; }
	// TODO: is active in hierarchy

	// --- TRANSFORMATION ---
	const glm::vec3& getLocalPosition() const { return m_local_position; }
	void setLocalPosition(const glm::vec3& p_position);

	const glm::quat& getLocalRotation() const { return m_local_rotation; }
	void setLocalRotation(const glm::quat& p_rotation);
	void setLocalRotation(const glm::vec3& p_euler_angle);

	const glm::vec3& getLocalScale() const { return m_local_scale; }
	void setLocalScale(const glm::vec3& p_scale);
	
protected:
	// LOCAL TRANSFORM
	glm::vec3 m_local_position;
	glm::quat m_local_rotation;
	glm::vec3 m_local_scale;
	mutable glm::mat4 m_local_transformation_matrix;

	std::string m_name;
	UUID m_uuid;
	bool m_active;
	uint32_t m_layer;
	
};

}

#endif // __GAMEOBJECT_H__