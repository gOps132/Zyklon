#include <zyklon_pch.h>

#include "GameObject.h"

namespace Zyklon {
	
GameObject::GameObject(const std::string& p_name)
	:	m_name(p_name),
		m_active(true),
		m_layer(0),
		m_local_position(0.0f),
		m_local_rotation(1.0f, 0.0f, 0.0f, 0.0f), // identity quaternion
		m_local_scale(1.0f, 1.0f, 1.0f), // default scale
		m_is_local_transformation_dirty(true),
		m_is_world_transformation_dirty(true)
{
	setUUID(UUID()); // generate a new UUID for the game object
}

void GameObject::setUUID(const UUID& p_uuid)
{	
	m_uuid = p_uuid;
}

void GameObject::setActive(bool p_active)
{
	m_active = p_active;
}

bool GameObject::isActiveInHierarchy() const
{
	if (!m_active) return false; // if the object is not active, return false
	Ref<GameObject> currentParent = m_parent.lock();
	while (currentParent) {
		if (!currentParent->isActive()) {
			return false; // if any parent is not active, return false
		}
		currentParent = currentParent->getParent().lock(); // move to the next parent
	}
	return true; // if no parent, the object is active in hierarchy
}

void GameObject::setLocalPosition(const glm::vec3& p_position)
{
	m_local_position = p_position;
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

void GameObject::setLocalRotation(const glm::quat& p_rotation)
{
	m_local_rotation = p_rotation;
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

void GameObject::setLocalRotation(const glm::vec3& p_euler_angle)
{
	m_local_rotation = glm::quat(glm::radians(p_euler_angle));
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

void GameObject::setLocalScale(const glm::vec3& p_scale)
{
	m_local_scale = p_scale;
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

glm::mat4 GameObject::getLocalTransformationMatrix() const
{
	if (m_is_local_transformation_dirty) {
		m_local_transformation_matrix = glm::translate(glm::mat4(1.0f), m_local_position) *
			glm::mat4_cast(m_local_rotation) *
			glm::scale(glm::mat4(1.0f), m_local_scale);
		m_is_local_transformation_dirty = false;
	}
	return m_local_transformation_matrix;
}

glm::mat4 GameObject::getWorldTransformationMatrix() const
{
	if (m_is_world_transformation_dirty) {
		if (auto parent = m_parent.lock()) {
			m_world_transformation_matrix = parent->getWorldTransformationMatrix() * getLocalTransformationMatrix();
		} else {
			m_world_transformation_matrix = getLocalTransformationMatrix(); // no parent, use local matrix
}


void GameObject::invalidateWorldTransform()
{
	m_is_world_transformation_dirty = true; // mark the world transformation as dirty
	if (auto parent = m_parent.lock()) {
		parent->invalidateWorldTransform(); // also invalidate parent's world transform
	}
	m_local_transformation_matrix = glm::mat4(1.0f); // reset local transformation matrix
	m_is_local_transformation_dirty = true; // mark local transformation as dirty
}

void GameObject::setParent(const Ref<GameObject> p_parent)
{
	// if currently has parent remove self from old parent's children
	Ref<GameObject> currentParent = m_parent.lock();
	if (currentParent && currentParent != p_parent)
	{
		currentParent->removeChild(shared_from_this());
	}

	// set new parent weak_ptr
	m_parent = weak_parent;

	// if new parent exists, add self to parents children
	if (p_parent)
	{
		p_parent->addChild(shared_from_this());
	}
	invalidateWorldTransform(); // parent changes world transform
}

void GameObject::addChild(const Ref<GameObject>& p_child)
{
	// check if child is arleady in the children list
	if (p_child && std::find(m_children.begin(), m_children.end(), p_child) == m_children.end())
	{
		m_children.push_back(p_child);
		p_child->setParent(shared_from_this()); // set this object as the parent of the child
	}

}

void GameObject::removeChild(const Ref<GameObject>& p_child) 
{
	if (!p_child)
	{
		ZYKLON_INFO("Child does not exist!");
		return;
	}
	
	auto it = std::remove(m_children.begin(), m_children.end(), p_child);
	if (it != m_children.end())
	{
		// child handles removal, shared_ptr count to 0, child weak_ptr to parent
		// eventually expires
		m_children.erase(it, m_children.end());
	}
}

template<typename T, typename... Args>
Ref<T> GameObject::addComponent(Argss&& ...args)
{
	// create component
	Ref<T> new_component = create_ref<T>(...args);

	// attach to game object
	m_components.push_back(new_component);
	new_component->onAttach(shared_from_this());

	// set scene reference
	Ref<Scene> scene_ptr = m_scene.lock();
	if (scene_ptr)
	{
		new_component->m_scene = scene_ptr;
	}

	return new_component;
}

} // namespace Zyklon