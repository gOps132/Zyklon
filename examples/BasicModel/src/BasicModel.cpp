#include "BasicModel.h"
#include "Zyklon/Assets/AssetManager.h"

#include <filesystem>
#include <imgui-test/imgui.h>

#include <Zyklon/Renderer/Shader.h>
#include <Zyklon/Renderer/Texture.h>
#include <Zyklon/Renderer/Material/Material.h>
#include <Zyklon/Components/MeshRendererComponent.h>
#include <Zyklon/Renderer/ShaderLibrary.h>

Zyklon::Application *Zyklon::Application::createApplication()
{
	return new BasicModel();
}

ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_aspect_ratio =
		static_cast<float>(Zyklon::Application::get().getWindow().getWidth()) /
		static_cast<float>(Zyklon::Application::get().getWindow().getHeight());

	m_camera = std::make_shared<Zyklon::PerspectiveCamera>(
		glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	// Initialize camera position for OrbitControls
	m_camera->setPosition({0.0f, 0.0f, 3.0f}); // Initial distance for orbit

	m_orbit = std::make_shared<Zyklon::OrbitControls>(m_camera);
	m_panning = std::make_shared<Zyklon::PanningControls>(m_camera);

	m_my_scene = Zyklon::createRef<Zyklon::Scene>("BasicModel");
	m_my_scene->setActiveCamera(m_camera);

	Zyklon::SceneManager::getInstance().addScene(m_my_scene);
	Zyklon::SceneManager::getInstance().setCurrentScene(m_my_scene);

	std::filesystem::path bunny_model_path = "examples/BasicModel/Assets/Models/stanford_bunny/scene.gltf";
	if (!std::filesystem::exists(bunny_model_path)) {
		ZYKLON_CORE_ERROR("Model file not found: {0}", bunny_model_path.string());
		return;
	}
	
	Zyklon::Ref<Zyklon::Shader> custom_lit_shader =
    Zyklon::ShaderLibrary::getInstance().load(
		"BasicLitShader", "examples/BasicModel/Assets/Shaders/BasicLit.shader"
	);

	bool model_loaded = Zyklon::AssetManager::getInstance().loadModel(bunny_model_path);
    if (model_loaded) {
        ZYKLON_INFO("Successfully loaded model: {0}", bunny_model_path.string());
        m_bunny_model_root = Zyklon::AssetManager::getInstance().instantiateModel(bunny_model_path, m_my_scene);
        if (m_bunny_model_root) {
            m_bunny_model_root->setName("Stanford_Bunny"); // Give it a friendly name in scene
            m_bunny_model_root->setLocalPosition({0.0f, 0.0f, 0.0f});
            // m_bunny_model_root->setLocalScale({1.0f, 1.0f, 1.0f}); // Adjust scale if needed

            m_selected_game_object = m_bunny_model_root;

            // Adjust camera target if the model's position isn't at origin
            m_orbit->setTarget(m_bunny_model_root->getLocalPosition());
        } else {
            ZYKLON_CORE_ERROR("Failed to instantiate Stanford Bunny model from '{0}'", bunny_model_path.string());
        }
    } else {
        ZYKLON_CORE_ERROR("Failed to load Stanford Bunny model from '{0}'", bunny_model_path.string());
    }

}

void ExampleLayer::onUpdate(Zyklon::Timestep ts)
{
	if (m_is_orbit_mode) {
		if (m_bunny_model_root) {
			m_orbit->setTarget(m_bunny_model_root->getLocalPosition());
		}
		m_orbit->onUpdate(ts); // Update orbit controls
	} else {
		m_panning->onUpdate(ts); // Update panning controls
	}
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

	}
}

void ExampleLayer::onImguiRender()
{
	ImGui::Begin("Camera Uniforms");
	ImGui::Text("Camera options!");
	ImGui::Text("Current Mode: %s", m_is_orbit_mode ? "Orbit" : "Panning");

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
				static_cast<double>(1000.0f / ImGui::GetIO().Framerate), static_cast<double>(ImGui::GetIO().Framerate));
	ImGui::End();

	ImGui::Begin("All States");
	if (ImGui::Button("reset all"))
		resetState(); // Call resetState for full system reset
	ImGui::End();
}

void ExampleLayer::resetState()
{
	// Reset camera perspective (aspect ratio updated by WindowResize event)
	m_camera->recalculatePerspectiveMatrix(
		glm::radians(m_fovy), m_aspect_ratio, 0.1f,
		1000.0f); // Reset to default near/far

	// Reset look_at (now m_is_orbit_mode) and index
	m_is_orbit_mode = true; // Default to orbit mode on reset
	index = 0;
}