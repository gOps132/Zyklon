#include <zyklon_pch.h>

#include <imgui-test/imgui.h>

#include "GameObject.h"
#include "Core.h"

namespace Zyklon {

GameObject::GameObject(const std::string &p_name)
	: m_name(p_name), m_active(true), m_layer(0), m_local_position(0.0f),
	  m_local_rotation(1.0f, 0.0f, 0.0f, 0.0f), // identity quaternion
	  m_local_scale(1.0f, 1.0f, 1.0f),			// default scale
	  m_is_local_transformation_dirty(true),
	  m_is_world_transformation_dirty(true)
{
}

void GameObject::setUUID(const UUID &p_uuid)
{
	if (m_uuid == p_uuid) {
		ZYKLON_CORE_WARN("GameObject {0} already has UUID {1}, not changing",
						 m_name, p_uuid);
		return; // no change needed
	}
	// dont assign if UUID is default value
	if (p_uuid == UUID()) {
		ZYKLON_CORE_ERROR("Cannot set UUID to default value");
		return;
	}
	// if scene is not set, we cannot update the UUID in the scene
	if (!m_scene.lock()) {
		ZYKLON_CORE_ERROR(
			"Cannot set UUID, scene is not set for GameObject {0}", m_name);
		return;
	}
	m_uuid = p_uuid;
	if (auto scene = m_scene.lock()) {
		scene->removeGameObject(
			shared_from_this()); // remove old UUID from scene
		scene->addGameObject(p_uuid,
							 shared_from_this()); // add new UUID to scene
	}
}

void GameObject::setActive(bool p_active) { m_active = p_active; }

bool GameObject::isActiveInHierarchy() const
{
	if (!m_active)
		return false; // if the object is not active, return false
	Ref<GameObject> currentParent = m_parent.lock();
	while (currentParent) {
		if (!currentParent->isActive()) {
			return false; // if any parent is not active, return false
		}
		currentParent = currentParent->getParent(); // move to the next parent
	}
	return true; // if no parent, the object is active in hierarchy
}

void GameObject::setLocalPosition(const glm::vec3 &p_position)
{
	m_local_position = p_position;
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

void GameObject::setLocalRotation(const glm::quat &p_rotation)
{
	m_local_rotation = p_rotation;
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

void GameObject::setLocalRotation(const glm::vec3 &p_euler_angle)
{
	m_local_rotation = glm::quat(glm::radians(p_euler_angle));
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

void GameObject::setLocalScale(const glm::vec3 &p_scale)
{
	m_local_scale = p_scale;
	m_is_local_transformation_dirty = true;
	invalidateWorldTransform();
}

const glm::mat4 &GameObject::getLocalTransformationMatrix()
{
	if (m_is_local_transformation_dirty) {
		m_local_transformation_matrix =
			glm::translate(glm::mat4(1.0f), m_local_position) *
			glm::mat4_cast(m_local_rotation) *
			glm::scale(glm::mat4(1.0f), m_local_scale);
		m_is_local_transformation_dirty = false;
	}
	return m_local_transformation_matrix;
}

const glm::mat4 &GameObject::getWorldTransformationMatrix()
{
	if (m_is_world_transformation_dirty) {
		if (auto parent = m_parent.lock()) {
			m_world_transformation_matrix =
				parent->getWorldTransformationMatrix() *
				getLocalTransformationMatrix();
		}
		else {
			m_world_transformation_matrix =
				getLocalTransformationMatrix(); // no parent, use local matrix
		}
	}

	return m_world_transformation_matrix;
}

void GameObject::invalidateWorldTransform()
{
	m_is_world_transformation_dirty = true;
	for (const auto &child : m_children) {
		child->invalidateWorldTransform();
	}
}

void GameObject::setParent(const Ref<GameObject> p_parent)
{
	// if currently has parent remove self from old parent's children
	Ref<GameObject> currentParent = m_parent.lock();
	if (currentParent && currentParent != p_parent) {
		currentParent->removeChild(shared_from_this());
	}

	// set new parent weak_ptr
	m_parent = p_parent;

	// if new parent exists, add self to parents children
	if (p_parent) {
		p_parent->addChild(shared_from_this());
	}
	invalidateWorldTransform(); // parent changes world transform
}

void GameObject::addChild(const Ref<GameObject> &p_child)
{
	// check if child is arleady in the children list
	if (p_child && std::find(m_children.begin(), m_children.end(), p_child) ==
					   m_children.end()) {
		m_children.push_back(p_child);
		p_child->setParent(
			shared_from_this()); // set this object as the parent of the child
	}
}

void GameObject::removeChild(const Ref<GameObject> &p_child)
{
	if (!p_child) {
		ZYKLON_INFO("Child does not exist!");
		return;
	}

	auto it = std::remove(m_children.begin(), m_children.end(), p_child);
	if (it != m_children.end()) {
		// child handles removal, shared_ptr count to 0, child weak_ptr to
		// parent eventually expires
		m_children.erase(it, m_children.end());
	}
}

void GameObject::removeComponent(const Ref<Component> &p_component)
{
	if (!p_component) {
		ZYKLON_CORE_ERROR("Cannot remove null component from GameObject {0}",
						  m_name);
		return;
	}

	auto it = std::remove_if(m_components.begin(), m_components.end(),
							 [&](const Ref<Component> &comp) {
								 // Predicate returns true for elements to be
								 // removed
								 return comp == p_component;
							 });

	if (it != m_components.end()) {
		p_component->onDetach();
		m_components.erase(it, m_components.end());
		m_component_map.erase(std::type_index(
			typeid(*p_component))); // expression with sideeffects will evaluate
									// despite typeid
		ZYKLON_CORE_INFO("Removed component '{0}' from GameObject '{1}'",
						 p_component->getName(), m_name);
	}
	else {
		ZYKLON_CORE_INFO("Component not found in '{0}' from GameObject '{1}'. "
						 "No component removed",
						 p_component->getName(), m_name);
	}
}

void GameObject::onImGuiRender()
{
	ImGui::Begin(m_name.c_str());

	for (const auto &comp : m_components) {
		comp->onImguiRender();
	}

	ImGui::End();
}

} // namespace Zyklon