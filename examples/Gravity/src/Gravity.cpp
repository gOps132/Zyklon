#include "Gravity.h"
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>

Zyklon::Application *Zyklon::Application::createApplication()
{
	return new Gravity();
}

ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_aspect_ratio = static_cast<float>(
						 Zyklon::Application::get().getWindow().getWidth()) /
					 static_cast<float>(
						 Zyklon::Application::get().getWindow().getHeight());
	m_camera = std::make_shared<Zyklon::PerspectiveCamera>(
		glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	m_orbit = std::make_shared<Zyklon::OrbitControls>(m_camera);
	m_planets = std::make_shared<SystemState>();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-5.0, 5.0);

	std::vector<std::string> ball_textures = 
	{
		"d:\\pictures\\personal\\mog.png",
		// "d:\\dev\\projects\\Zyklon\\examples\\Gravity\\images\\earthpng.png", // warning: absolute directory
		// "d:\\pictures\\personal\\derfpng.png"
	};

	for (int i = 0; i < ball_textures.size(); i++)
	{
		float random_x = static_cast<float>(dis(gen));
		float random_y = static_cast<float>(dis(gen));
		auto sphere = std::make_shared<UVSphere>(
			"sphere " + std::to_string(i), 1.0f, 1.0f,
			glm::vec3(random_x, random_y, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
			"examples/Gravity/src/Shaders/Polygon.shader");
		sphere->setTexture(ball_textures[i], i);
		m_sphere.push_back(sphere);
		m_planets->add_physical_object(sphere);
	}
	
	resetState();
}

void ExampleLayer::resetState()
{
	m_aspect_ratio = static_cast<float>(
						 Zyklon::Application::get().getWindow().getWidth()) /
					 static_cast<float>(
						 Zyklon::Application::get().getWindow().getHeight());
	m_camera->recalculate_perspective_matrix(
		glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);

	m_camera_position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_camera_rotation = 0.0f;

	m_near_plane = 0.1f;  // Near clipping plane distance
	m_far_plane = 100.0f; // Far clipping plane distance
}

void ExampleLayer::onUpdate(Zyklon::Timestep ts)
{
	float time = Zyklon::Application::get().getWindow().getTime();
	// float frequency = 0.4f; // Adjust for desired oscillation speed (higher =
	// faster) float amplitude = 0.4f; // Adjust for desired oscillation range
																												
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_UP)) {
		m_camera_position.z += m_camera_speed * ts;
	}
	if (Zyklon::Input::keyPressed(ZYKLON_KEY_DOWN)) {
		m_camera_position.z -= m_camera_speed * ts;
	}

	if (look_at) {
		m_orbit->set_target(m_sphere[index]->getPosition());
		m_orbit->update();
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_UP)) {
			m_orbit->get_distance() -= m_camera_speed * ts;
		}
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_DOWN)) {
			m_orbit->get_distance() += m_camera_speed * ts;
		}
	}
	else {
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_W)) {
			m_camera_position.z += m_camera_speed * ts;
		}
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_S)) {
			m_camera_position.z -= m_camera_speed * ts;
		}
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_A)) {
			m_camera_position.x += m_camera_speed * ts;
		}
		if (Zyklon::Input::keyPressed(ZYKLON_KEY_D)) {
			m_camera_position.x -= m_camera_speed * ts;
		}
		m_camera->setPosition(m_camera_position);
		m_camera->update();
	}
	
	for (auto sphere : m_sphere) {
		sphere->updateShader(time);
	}

	Zyklon::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));

	// calculate gravitational phsyics
	m_planets->update_system_state(ts);

	Zyklon::Renderer::beginScene(*m_camera);
	// translate object into world space
	// float rotation_speed = 2.0f;
	// float rotation_angle = glm::radians(20.0f) * ts * rotation_speed;
	// double bob_val = std::cos(static_cast<double>(frequency) *
	// static_cast<double>(time));	

	for (auto sphere : m_sphere) {
		// sphere->setModelMatrix(glm::rotate(sphere->getModelMatrix(),
		// 									 rotation_angle,
		// 									 glm::vec3(0.0f, 0.5f, 0.0f)));
		glm::mat4 transform =
			glm::translate(sphere->getModelMatrix(),
						   // glm::vec3(0.0f, 0.3f * bob_val, 0.0f))
						   sphere->getPosition()) *
			scale;

		sphere->render(transform);
	}
	Zyklon::Renderer::endScene();
}

void ExampleLayer::onEvent(Zyklon::Event &event)
{
	// ZYKLON_INFO("Event: {0}", event.getName());

	// Handle window resize events
	if (event.getEventType() == Zyklon::EventType::WindowResize) {
		m_aspect_ratio =
			static_cast<float>(
				Zyklon::Application::get().getWindow().getWidth()) /
			static_cast<float>(
				Zyklon::Application::get().getWindow().getHeight());
		m_camera->recalculate_perspective_matrix(
			glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
		int width = Zyklon::Application::get().getWindow().getWidth();
		int height = Zyklon::Application::get().getWindow().getHeight();
		Zyklon::RenderCommand::setViewport(0, 0, width, height);
	}

	// Handles events when main window is active
	if (!ImGui::IsAnyWindowFocused()) {
		if (event.getEventType() == Zyklon::EventType::MouseButtonPressed) {
			is_mouse_down = true;
			mouse_previous = mouse_current;
		}

		Zyklon::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Zyklon::MouseMovedEvent>(
			[&](Zyklon::MouseMovedEvent &e) {
				// is_moving = true;
				mouse_current = {e.getX(), e.getY()};
				if(is_mouse_down) {
					if (look_at) {
						glm::vec2 delta = mouse_current - mouse_previous;
						m_orbit->update(delta.x, delta.y); // probably need to adjust sensitivity
					} else {
						glm::vec2 delta = mouse_current - mouse_previous;
						m_camera_position.x += static_cast<float>(delta.x) * 0.10; // Adjust sensitivity as needed
						m_camera_position.y -= static_cast<float>(delta.y) * 0.10; // Adjust sensitivity as needed
						m_camera->setPosition(m_camera_position);
						m_camera->update();
					}
				}
				mouse_previous = mouse_current;
				// ZYKLON_INFO("Mouse current: {0}, Y:{1}", mouse_current.x,
				// mouse_current.y);
				return true;
			});

		dispatcher.Dispatch<Zyklon::MouseScrolledEvent>(
			[&](Zyklon::MouseScrolledEvent &e) {
				float x = e.getXOffset(); // Access derived class methods
				float y = e.getYOffset();
				// ZYKLON_INFO("scrolled to: x: {0}, y: {1}", x, y);
				if (look_at) {
					m_orbit->get_distance() -= static_cast<float>(y) * 0.10; // Adjust sensitivity as needed
				} else {
					m_camera_position.z -= static_cast<float>(y) * 0.10f; // Adjust sensitivity as needed
				}

				m_camera->setPosition(m_camera_position);
				m_camera->update();

				return true; // Return true if the event was handled
		});

		if (event.getEventType() == Zyklon::EventType::KeyPressed &&
			Zyklon::Input::keyPressed(ZYKLON_KEY_Q)) {
			index = (index + 1) % m_sphere.size();
		}

		if (event.getEventType() == Zyklon::EventType::KeyPressed &&
			Zyklon::Input::keyPressed(ZYKLON_KEY_SPACE)) {
			look_at = !look_at;
			ZYKLON_INFO("look at mode {0}", look_at);
		}

		if (event.getEventType() == Zyklon::EventType::MouseButtonRelease) {
			is_mouse_down = false;
		}
		
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
	if (ImGui::SliderFloat("far plane", &m_far_plane, 100.0f, 200.0f, "%.2f",
						   5.0f))
		m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio,
												 m_near_plane, m_far_plane);
	if (ImGui::Button("reset camera"))
		resetState();
	ImGui::End();
	ImGui::Begin("All States");
	if (ImGui::Button("reset all"))
		for (auto sphere : m_sphere) {
			sphere->reset();
		}
	ImGui::End();

	m_sphere[index]->renderGUI();
}