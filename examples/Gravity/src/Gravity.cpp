#include "Gravity.h"
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Gravity();
}

ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_aspect_ratio = static_cast<float>(
						 Zyklon::Application::get().get_window().get_width()) /
					 static_cast<float>(
						 Zyklon::Application::get().get_window().get_height());
	m_camera = std::make_shared<Zyklon::PerspectiveCamera>(
		glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	m_orbit = std::make_shared<Zyklon::OrbitControls>(m_camera);
	m_planets = std::make_shared<SystemState>();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-5.0, 5.0);
	// instantiate them balls
	// Instantiate spheres at random positions
	for (int i = 0; i < 5; i++) {
		float random_x = dis(gen);
		float random_y = dis(gen);
		auto sphere = std::make_shared<Sphere>(
			"sphere " + std::to_string(i), 0.5f, 1.0f,
			glm::vec3(random_x, random_y, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
			"examples/Gravity/src/Shaders/Polygon.shader");
		m_sphere.push_back(sphere);
		m_planets->add_physical_object(sphere);
	}
	// {
	// 	auto sphere = std::make_shared<Sphere>(
	// 		"sphere " + std::to_string(2),
	// 		0.5f,  0.001f,
	// 		glm::vec3(1.0f, 0.0f, 0.0f),
	// 		glm::vec3(0.0f, 1.0f, 0.0f),
	// 		"examples/Gravity/src/Shaders/_wood.shader"
	// 	);
	// 	m_sphere.push_back(sphere);
	// 	m_planets->add_physical_object(sphere);
	// }
	reset_state();
}

void ExampleLayer::reset_state()
{
	m_aspect_ratio = static_cast<float>(
						 Zyklon::Application::get().get_window().get_width()) /
					 static_cast<float>(
						 Zyklon::Application::get().get_window().get_height());
	m_camera->recalculate_perspective_matrix(
		glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);

	m_camera_position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_camera_rotation = 0.0f;

	m_near_plane = 0.1f;  // Near clipping plane distance
	m_far_plane = 100.0f; // Far clipping plane distance
}

void ExampleLayer::on_update(Zyklon::Timestep ts)
{
	float time = Zyklon::Application::get().get_window().get_time();
	// float frequency = 0.4f; // Adjust for desired oscillation speed (higher =
	// faster) float amplitude = 0.4f; // Adjust for desired oscillation range

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_UP)) {
		m_camera_position.z += m_camera_speed * ts;
	}
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_DOWN)) {
		m_camera_position.z -= m_camera_speed * ts;
	}

	if (look_at) {
		m_orbit->set_target(m_sphere[index]->get_position());
		m_orbit->update();
		if (Zyklon::Input::key_pressed(ZYKLON_KEY_UP)) {
			m_orbit->get_distance() += m_camera_speed * ts;
		}
		if (Zyklon::Input::key_pressed(ZYKLON_KEY_DOWN)) {
			m_orbit->get_distance() -= m_camera_speed * ts;
		}
	}
	else {
		m_camera->set_position(m_camera_position);
		m_camera->update();
	}

	// m_sphere->update_shader(time);
	for (auto sphere : m_sphere) {
		sphere->update_shader(time);
	}

	Zyklon::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));

	// calculate gravitational phsyics
	m_planets->update_system_state(ts);

	Zyklon::Renderer::begin_scene(*m_camera);
	// translate object into world space
	// float rotation_speed = 2.0f;
	// float rotation_angle = glm::radians(20.0f) * ts * rotation_speed;
	// double bob_val = std::cos(static_cast<double>(frequency) *
	// static_cast<double>(time));

	for (auto sphere : m_sphere) {
		// sphere->set_model_matrix(glm::rotate(sphere->get_model_matrix(),
		// 									 rotation_angle,
		// 									 glm::vec3(0.0f, 0.5f, 0.0f)));
		glm::mat4 transform =
			glm::translate(sphere->get_model_matrix(),
						   // glm::vec3(0.0f, 0.3f * bob_val, 0.0f))
						   sphere->get_position()) *
			scale;

		sphere->render(transform);
	}
	Zyklon::Renderer::end_scene();
}

void ExampleLayer::on_event(Zyklon::Event &event)
{
	// ZYKLON_INFO("Event: {0}", event.get_name());

	// Handle window resize events
	if (event.get_event_type() == Zyklon::EventType::WindowResize) {
		m_aspect_ratio =
			static_cast<float>(
				Zyklon::Application::get().get_window().get_width()) /
			static_cast<float>(
				Zyklon::Application::get().get_window().get_height());
		m_camera->recalculate_perspective_matrix(
			glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	}

	// Handles events when main window is active
	if (!ImGui::IsAnyWindowFocused()) {		
		if (event.get_event_type() == Zyklon::EventType::MouseButtonPressed) {
			is_mouse_down = true;
			mouse_previous = mouse_current;
		}

		Zyklon::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Zyklon::MouseMovedEvent>(
			[&](Zyklon::MouseMovedEvent &e) {
				// is_moving = true;
				mouse_current = {e.GetX(), e.GetY()};
				if(is_mouse_down) {
					glm::vec2 delta = mouse_current - mouse_previous;
					m_camera_position.x += delta.x * 0.01f; // Adjust sensitivity as needed
                    m_camera_position.y -= delta.y * 0.01f; // Adjust sensitivity as needed
                    m_camera->set_position(m_camera_position);
                    m_camera->update();
				}
				mouse_previous = mouse_current;
				// ZYKLON_INFO("Mouse current: {0}, Y:{1}", mouse_current.x,
				// mouse_current.y);
				return true;
			});

		dispatcher.Dispatch<Zyklon::MouseScrolledEvent>(
			[&](Zyklon::MouseScrolledEvent &e) {
				float x = e.GetXOffset(); // Access derived class methods
				float y = e.GetYOffset();
				// ZYKLON_INFO("scrolled to: x: {0}, y: {1}",x,y);
				if (look_at)
					m_orbit->update(x, y);
				else {
					m_camera_position.x += x;
					m_camera_position.y -= y;
				}

				return true; // Return true if the event was handled
		});

		if (event.get_event_type() == Zyklon::EventType::KeyPressed &&
			Zyklon::Input::key_pressed(ZYKLON_KEY_A)) {
			index = (index + 1) % m_sphere.size();
			// auto tmp = m_sphere[index]->get_position();
			// ZYKLON_INFO("Index: {0}, pos, x: {1}, y: {2}, z:{3}", index,
			// tmp.x, tmp.y, tmp.z);
		}

		if (event.get_event_type() == Zyklon::EventType::KeyPressed &&
			Zyklon::Input::key_pressed(ZYKLON_KEY_SPACE)) {
			look_at = !look_at;
			ZYKLON_INFO("look at mode {0}", look_at);
		}

		if (event.get_event_type() == Zyklon::EventType::MouseButtonRelease) {
			is_mouse_down = false;
			// m_mouse_moved_delta = mouse_current - mouse_previous;
			// ZYKLON_INFO("Mouse delta: x:{0}, y:{1}", m_mouse_moved_delta.x,
			// m_mouse_moved_delta.y);
		}
		
	}
}

void ExampleLayer::on_imgui_render()
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
		reset_state();
	ImGui::End();
	ImGui::Begin("All States");
	if (ImGui::Button("reset all"))
		for (auto sphere : m_sphere) {
			sphere->reset();
		}
	ImGui::End();

	m_sphere[index]->render_gui();
}