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
	m_orbit = std::make_shared<Zyklon::OrbitControls>(m_camera);
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
		-100.0, 100.0); // Larger range for positions
	std::uniform_real_distribution<> dis_vel(
		-0.01, 0.01); // Smaller range for velocities

	int num_spheres = 2; // Example: Create 5 spheres

	for (int i = 0; i < num_spheres; i++) {
		float random_x_pos = static_cast<float>(dis_pos(gen));
		float random_y_pos = static_cast<float>(dis_pos(gen));
		float random_z_pos = static_cast<float>(dis_pos(gen));
		glm::vec3 initial_pos = {random_x_pos, random_y_pos, random_z_pos};
		// glm::vec3 initial_pos = {0.0f, 0.0f, 0.0f};

		float random_x_vel = static_cast<float>(dis_vel(gen));
		float random_y_vel = static_cast<float>(dis_vel(gen));
		float random_z_vel = static_cast<float>(dis_vel(gen));
		glm::vec3 initial_vel = {random_x_vel, random_y_vel, random_z_vel};

		float radius = 5.0f;
		float mass =
			200.0f + static_cast<float>(dis_pos(gen)); // Vary mass slightly

		auto p_object =
			std::make_shared<PObject>(mass, radius, initial_pos, initial_vel);
		m_planets->add_physical_object(p_object);
		m_physics_objects_map.push_back(p_object);

		// 2. Generate mesh data using UVSphere/HexagonalSphere
		// Note: UVSphere/HexagonalSphere are now primarily mesh data generators
		// They no longer manage their own shaders/textures or render themselves
		UVSphere temp_uv_sphere("temp_name", radius, mass, initial_pos,
								initial_vel);
		temp_uv_sphere.generate(radius, 50,
								50); // Generate vertices and indices

		Zyklon::BufferLayout uvSphereLayout = {
			{Zyklon::ShaderDataType::Float3, "a_position", false},
			{Zyklon::ShaderDataType::Float3, "a_normal", false},
			{Zyklon::ShaderDataType::Float2, "a_uv", false}};

		Zyklon::Ref<Zyklon::Mesh> mesh = Zyklon::createRef<Zyklon::Mesh>(
			temp_uv_sphere.getVertices(), temp_uv_sphere.getIndices(),
			uvSphereLayout);

		// 3. Create a GameObject for rendering
		Zyklon::Ref<Zyklon::GameObject> sphere_go =
			m_my_scene->createGameObject("Sphere_" + std::to_string(i));
		sphere_go->setLocalPosition(
			initial_pos); // Set initial position from physics object
		sphere_go->setLocalScale(
			{radius, radius, radius}); // Scale based on physics radius

		// 4. Attach a MeshRendererComponent to the GameObject
		sphere_go->addComponent<Zyklon::MeshRendererComponent>(mesh,
															   sphereMaterial);

		m_sphere_game_objects.push_back(sphere_go);
	}
}

void ExampleLayer::onUpdate(Zyklon::Timestep ts)
{
	m_orbit->onUpdate(ts); // Update orbit controls
	m_camera->update();	   // Update camera view matrix

	m_planets->update_system_state(ts);

	// Synchronize GameObject positions with PObject positions after physics
	// update
	for (size_t i = 0; i < m_physics_objects_map.size(); ++i) {
		const auto &p_obj = m_physics_objects_map[i];
		const auto &game_obj = m_sphere_game_objects[i];
		game_obj->setLocalPosition(p_obj->getPosition());
	}

	// Example: Look at a specific planet
	if (look_at && index < m_physics_objects_map.size()) {
		// Use the position of the PObject to set the target for orbit controls
		m_orbit->set_target(m_physics_objects_map[index]->getPosition());
	}
}

void ExampleLayer::onEvent(Zyklon::Event &event)
{
	if (!ImGui::IsAnyWindowFocused()) {

		m_orbit->onEvent(
			event); // Let orbit controls handle mouse/keyboard camera events
	}
	// Only handle these specific key presses directly in the layer
	if (event.getEventType() == Zyklon::EventType::KeyPressed &&
		Zyklon::Input::keyPressed(ZYKLON_KEY_Q)) {
		index = (index + 1) %
				m_sphere_game_objects.size(); // Cycle through game objects
	}

	if (event.getEventType() == Zyklon::EventType::KeyPressed &&
		Zyklon::Input::keyPressed(ZYKLON_KEY_SPACE)) {
		look_at = !look_at;
		ZYKLON_INFO("look at mode {0}", look_at);
	}

	// Mouse button release logic (if not fully handled by OrbitControls)
	if (event.getEventType() == Zyklon::EventType::MouseButtonRelease &&
		Zyklon::Input::mouseBtnPressed(ZYKLON_MOUSE_BUTTON_LEFT)) {
		is_mouse_down = false; // Reset mouse down state
	}
}

void ExampleLayer::onImguiRender()
{
	ImGui::Begin("Camera Uniforms");
	ImGui::Text("Camera options!");
	if (ImGui::SliderFloat("fov", &m_fovy, 20.0f, 120.0f, "%.2f", 5.0f))
		m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio,
												 m_near_plane, m_far_plane);
	if (ImGui::SliderFloat("near plane", &m_near_plane, 0.1f, 100.0f, "%.2f",
						   5.0f))
		m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio,
												 m_near_plane, m_far_plane);
	if (ImGui::SliderFloat("far plane", &m_far_plane, 100.0f, 2000.0f, "%.2f",
						   5.0f)) // Increased far plane range for larger scenes
		m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio,
												 m_near_plane, m_far_plane);
	if (ImGui::Button("reset camera"))
		resetState();
	ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("All States");
	if (ImGui::Button("reset all"))
		resetState(); // Call resetState for full system reset
	ImGui::End();

	m_sphere_game_objects[index]->onImGuiRender();
}

void ExampleLayer::resetState()
{
	// Reset camera perspective (aspect ratio updated by WindowResize event)
	m_camera->recalculate_perspective_matrix(
		glm::radians(m_fovy), m_aspect_ratio, 0.1f,
		1000.0f); // Reset to default near/far

	// Reset orbit controls/camera position
	// Assuming OrbitControls handles its own reset or is reset by setting
	// initial camera values
	m_camera->setPosition({0.0f, 0.0f, 5.0f}); // Default camera position
	m_orbit->reset();						   // Reset orbit controls state

	// Reset physics objects
	// m_planets->reset_all_physical_objects();

	// Synchronize GameObject positions with reset PObject positions
	for (size_t i = 0; i < m_physics_objects_map.size(); ++i) {
		const auto &p_obj = m_physics_objects_map[i];
		const auto &game_obj = m_sphere_game_objects[i];
		game_obj->setLocalPosition(p_obj->getPosition());
	}

	// Reset look_at and index
	look_at = false;
	index = 0;
}