#include "Gravity.h"
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Zyklon/Renderer/Shader.h>
#include <Zyklon/Renderer/Texture.h>
#include <Zyklon/Renderer/Material/Material.h>
#include <Zyklon/Components/MeshRendererComponent.h>

Zyklon::Application *Zyklon::Application::createApplication()
{
	return new Gravity();
}

ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_aspect_ratio =
		static_cast<float>(Zyklon::Application::get().getWindow().getWidth()) /
		static_cast<float>(Zyklon::Application::get().getWindow().getHeight());

	m_camera = std::make_shared<Zyklon::PerspectiveCamera>(
		glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	// Initialize camera position for OrbitControls
	m_camera->setPosition({0.0f, 0.0f, 00.0f}); // Initial distance for orbit

	m_orbit = std::make_shared<Zyklon::OrbitControls>(m_camera);
	m_panning = std::make_shared<Zyklon::PanningControls>(
		m_camera); // NEW: Initialize PanningControls
	m_planets = std::make_shared<SystemState>();

	m_my_scene = Zyklon::createRef<Zyklon::Scene>("GravityScene");
	m_my_scene->setActiveCamera(m_camera);

	Zyklon::SceneManager::getInstance().addScene(m_my_scene);
	Zyklon::SceneManager::getInstance().setCurrentScene(m_my_scene);

	m_shader = Zyklon::Ref<Zyklon::Shader>(
		Zyklon::Shader::create("examples/Gravity/src/Shaders/Polygon.shader"));
	m_texture = Zyklon::Ref<Zyklon::Texture2D>(
		Zyklon::Texture2D::create("examples/Gravity/images/earthpng.png"));

	Zyklon::Ref<Zyklon::Material> sphereMaterial =
		Zyklon::createRef<Zyklon::BasicLitMaterial>(m_shader, m_texture);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_pos(
		-10.0, 10.0); // Larger range for positions
	std::uniform_real_distribution<> dis_vel(
		-0.01, 0.01); // Smaller range for velocities

	int num_spheres = 3; // Example: Create 5 spheres

	for (int i = 0; i < num_spheres; i++) {
		float random_x_pos = static_cast<float>(dis_pos(gen));
		float random_y_pos = static_cast<float>(dis_pos(gen));
		float random_z_pos = static_cast<float>(dis_pos(gen));
		glm::vec3 initial_pos = {random_x_pos, random_y_pos, random_z_pos};
		// glm::vec3 initial_pos = {0.0f, 0.0f, 0.0f};

		float random_x_vel = static_cast<float>(dis_vel(gen));
		float random_y_vel = static_cast<float>(dis_vel(gen));
		float random_z_vel = static_cast<float>(dis_vel(gen));
		// glm::vec3 initial_vel = initial_pos;
		glm::vec3 initial_vel = {random_x_vel, random_y_vel, random_z_vel};

		float radius = 1.0f;
		float mass =
			200.0f + static_cast<float>(dis_pos(gen)); // Vary mass slightly

		// PObject and UVSphere decoupling (as discussed in review)
		auto p_object =
			std::make_shared<PObject>(mass, radius, initial_pos, initial_vel);
		m_planets->add_physical_object(p_object);
		m_physics_objects_map.push_back(p_object);

		UVSphere temp_uv_sphere(
			"temp_name"); // UVSphere no longer inherits PObject
		temp_uv_sphere.generate(radius, 50, 50);

		Zyklon::BufferLayout uvSphereLayout = {
			{Zyklon::ShaderDataType::Float3, "a_position", false},
			{Zyklon::ShaderDataType::Float3, "a_normal", false},
			{Zyklon::ShaderDataType::Float2, "a_uv", false}};

		Zyklon::Ref<Zyklon::Mesh> mesh = Zyklon::createRef<Zyklon::Mesh>(
			temp_uv_sphere.getVertices(), temp_uv_sphere.getIndices(),
			uvSphereLayout);

		Zyklon::Ref<Zyklon::GameObject> sphere_go =
			m_my_scene->createGameObject("Sphere_" + std::to_string(i));
		sphere_go->setLocalPosition(
			initial_pos); // Set initial position from physics object
		sphere_go->setLocalScale(
			{radius, radius, radius}); // Scale based on physics radius

		sphere_go->addComponent<Zyklon::MeshRendererComponent>(mesh,
															   sphereMaterial);
		m_sphere_game_objects.push_back(sphere_go);
	}
}

void ExampleLayer::onUpdate(Zyklon::Timestep ts)
{
	m_planets->update_system_state(ts);

	// Synchronize GameObject positions with PObject positions after physics
	// update
	for (size_t i = 0; i < m_physics_objects_map.size(); ++i) {
		const auto &p_obj = m_physics_objects_map[i];
		const auto &game_obj = m_sphere_game_objects[i];
		game_obj->setLocalPosition(p_obj->getPosition());
	}

	// Update active camera control
	if (m_is_orbit_mode) {
		// Use the position of the PObject to set the target for orbit controls
		m_orbit->setTarget(m_physics_objects_map[index]->getPosition());
		m_orbit->onUpdate(ts); // Update orbit controls
	}
	else {
		m_panning->onUpdate(ts); // Update panning controls
	}
	m_camera->update(); // Always update the camera's view matrix (if dirty)
}

void ExampleLayer::onEvent(Zyklon::Event &event)
{
	// Important: Only process camera events if ImGui isn't handling input
	if (!ImGui::IsAnyWindowFocused() && !ImGui::IsAnyItemHovered() &&
		!ImGui::IsAnyItemActive()) {
		// Let the currently active controls handle events
		if (m_is_orbit_mode) {
			m_orbit->onEvent(event);
		}
		else {
			m_panning->onEvent(event);
		}
	}

	// Global key presses for mode switching and cycling target
	if (event.getEventType() == Zyklon::EventType::KeyPressed) {
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_Q)) {
			index = (index + 1) %
					m_sphere_game_objects.size(); // Cycle through game objects
		}
		// Toggle camera mode
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_SPACE)) {
			m_is_orbit_mode = !m_is_orbit_mode;
			ZYKLON_INFO("Camera Mode: {0}",
						m_is_orbit_mode ? "Orbit" : "Panning");
			if (m_is_orbit_mode) {
				m_orbit->reset();
				m_orbit->setTarget(m_physics_objects_map[index]->getPosition());
			}
			else {
				m_panning->reset();
			}
		}
	}
}

void ExampleLayer::onImguiRender()
{
	ImGui::Begin("Camera Uniforms");
	ImGui::Text("Camera options!");
	ImGui::Text("Current Mode: %s", m_is_orbit_mode ? "Orbit" : "Panning");
	if (ImGui::Button("Toggle Camera Mode (Space)")) {
		m_is_orbit_mode = !m_is_orbit_mode;
		ZYKLON_INFO("Camera Mode: {0}", m_is_orbit_mode ? "Orbit" : "Panning");
		if (m_is_orbit_mode) {
			m_orbit->reset();
			m_orbit->setTarget(m_physics_objects_map[index]->getPosition());
		}
		else {
			m_panning->reset();
		}
	}

	if (ImGui::SliderFloat("fov", &m_fovy, 20.0f, 120.0f, "%.2f", 5.0f))
		m_camera->recalculatePerspectiveMatrix(
			glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	if (ImGui::SliderFloat("near plane", &m_near_plane, 0.1f, 100.0f, "%.2f",
						   5.0f))
		m_camera->recalculatePerspectiveMatrix(
			glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	if (ImGui::SliderFloat("far plane", &m_far_plane, 100.0f, 2000.0f, "%.2f",
						   5.0f))
		m_camera->recalculatePerspectiveMatrix(
			glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	if (!m_is_orbit_mode) {
		float current_pan_speed = m_panning->getPanSpeed();
		if (ImGui::SliderFloat("Panning Speed", &current_pan_speed, 0.001f,
							   0.1f, "%.3f")) {
			m_panning->setPanSpeed(current_pan_speed);
		}
	}

	if (ImGui::Button("reset camera"))
		resetState();
	ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("All States");
	if (ImGui::Button("reset all"))
		resetState(); // Call resetState for full system reset
	ImGui::End();

	ImGui::Begin("Objects");
	for (auto &go : m_sphere_game_objects) {
		ImGui::PushID(go.get()); // Use pointer address as a unique ID
		if (ImGui::CollapsingHeader(go->getName().c_str(),
									ImGuiTreeNodeFlags_NoTreePushOnOpen)) {
			ImGui::Indent();
			go->onImGuiRender();
			ImGui::Unindent();
		}
		ImGui::PopID();
	}
	ImGui::End();
}

void ExampleLayer::resetState()
{
	// Reset camera perspective (aspect ratio updated by WindowResize event)
	m_camera->recalculatePerspectiveMatrix(
		glm::radians(m_fovy), m_aspect_ratio, 0.1f,
		1000.0f); // Reset to default near/far

	// Reset orbit controls/camera position based on current mode
	if (m_is_orbit_mode) {
		m_camera->setPosition(
			{0.0f, 0.0f, 00.0f}); // Default camera position for orbit
		m_orbit->reset();		  // Reset orbit controls state
		m_orbit->setTarget(
			m_physics_objects_map[index]->getPosition()); // Set initial target
	}
	else {
		m_camera->setPosition(
			{0.0f, 0.0f,
			 200.0f}); // Default camera position for panning (adjust as needed)
		m_panning->reset(); // Reset panning controls state
	}

	// Synchronize GameObject positions with reset PObject positions
	for (size_t i = 0; i < m_physics_objects_map.size(); ++i) {
		const auto &p_obj = m_physics_objects_map[i];
		const auto &game_obj = m_sphere_game_objects[i];
		game_obj->setLocalPosition(p_obj->getPosition());
	}

	// Reset look_at (now m_is_orbit_mode) and index
	m_is_orbit_mode = true; // Default to orbit mode on reset
	index = 0;
}