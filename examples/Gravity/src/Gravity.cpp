#include "Gravity.h"
#include <imgui-test/imgui.h>

#define _USE_MATH_DEFINES
#include <math.h>

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Gravity();
}

ExampleLayer::ExampleLayer()
	: 	Layer("Example")
{
	m_aspect_ratio =
		static_cast<float>(Zyklon::Application::get().get_window().get_width()) / 
		static_cast<float>(Zyklon::Application::get().get_window().get_height());
	m_camera = std::make_shared<Zyklon::PerspectiveCamera>(glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	m_orbit = std::make_shared<Zyklon::OrbitControls>(m_camera);

	// name, radius, mass, og position, shader_path
	// m_sphere = std::make_shared<Sphere>(
	// 	"First Sphere", 1.0f,  30.0f, glm::vec3(0.0f, 0.0f, 0.0f), "examples/Gravity/src/Shaders/Polygon.shader"
	// );

	m_planets = std::make_shared<SystemState>();

	// TODO: maybe use reserved for later?
	// TODO: sphere transformation
	for (int i = 0; i < 2; i++)
	{
		auto sphere = std::make_shared<Sphere>(
			"sphere " + std::to_string(i+1),
			1.0f,  1.0f,
			glm::vec3(0.0f + (2.5f * i), 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			"examples/Gravity/src/Shaders/Polygon.shader"
		);
		m_sphere.push_back(sphere);
		m_planets->add_physical_object(sphere);
	}

	reset_state();
}

void ExampleLayer::reset_state()
{
	m_aspect_ratio =
		static_cast<float>(Zyklon::Application::get().get_window().get_width()) / 
		static_cast<float>(Zyklon::Application::get().get_window().get_height());
	m_camera->recalculate_perspective_matrix(glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);

	m_camera_position = glm::vec3(0.0f,0.0f,5.0f);
	m_camera_rotation = 0.0f;

	m_near_plane = 0.1f;          // Near clipping plane distance
	m_far_plane = 100.0f;         // Far clipping plane distance

	// m_sphere->reset();
}

void ExampleLayer::on_update(Zyklon::Timestep ts)
{
	float time = Zyklon::Application::get().get_window().get_time();
	float frequency = 0.4f; // Adjust for desired oscillation speed (higher = faster)
	float amplitude = 0.4f; // Adjust for desired oscillation range

	// if (Zyklon::Input::key_pressed(ZYKLON_KEY_W))
	// 	m_model_position.y -= m_camera_speed * ts;

	// if (Zyklon::Input::key_pressed(ZYKLON_KEY_S))
	// 	m_model_position.y += m_camera_speed * ts;
	// if (Zyklon::Input::key_pressed(ZYKLON_KEY_A))
	// 	m_model_position.x -= m_camera_speed * ts;
	// if (Zyklon::Input::key_pressed(ZYKLON_KEY_D))
	// 	m_model_position.x += m_camera_speed * ts;

	// TODO: MOVE THIS INTO CAMERA ORBIT CONTROLS
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_UP))
		m_camera_position.z += m_camera_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_DOWN))
		m_camera_position.z -= m_camera_speed * ts;

	if (Zyklon::Input::key_pressed(ZYKLON_KEY_LEFT))
		m_camera_rotation -= m_camera_rotation_speed * ts;
	if (Zyklon::Input::key_pressed(ZYKLON_KEY_RIGHT))
		m_camera_rotation += m_camera_rotation_speed * ts;
	
	// if (is_mouse_down)
	// {
	// 	m_model_position.x += m_mouse_moved_delta.x;
	// 	m_model_position.x += m_mouse_moved_delta.y;
	// }

	m_camera->set_position(m_camera_position);
	m_camera->set_rotation(m_camera_rotation);

	// m_camera->look_at(m_model_position, m_camera_vertical_orientation);

	// m_sphere->update_shader(time);
	for ( auto sphere : m_sphere )
	{
		sphere->update_shader(time);
	}

	Zyklon::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
	Zyklon::RenderCommand::clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));

	Zyklon::Renderer::begin_scene(*m_camera);
		// calculate gravitational phsyics
		m_planets->ode_solve_euler(ts);

		// translate object into world space
		float rotation_speed = 0.5f;
		// float rotation_angle = glm::radians(20.0f) * ts * rotation_speed;
		// double bob_val = std::cos(static_cast<double>(frequency) * static_cast<double>(time));

		// TODO: abstrat away the transformation matrix code
		for ( auto sphere : m_sphere )
		{
			// sphere->set_model_matrix(glm::rotate(sphere->get_model_matrix(), rotation_angle, glm::vec3(0.0f, 0.5f, 0.0f)));
			glm::mat4 transform = glm::translate(sphere->get_model_matrix(),
				// glm::vec3(0.0f, 0.3f * bob_val, 0.0f))
				sphere->get_position())
				 * scale;

			sphere->render(transform);
		}

		// m_sphere->render(transform);

	Zyklon::Renderer::end_scene();
}

void ExampleLayer::on_event(Zyklon::Event &event)
{
	// glm::vec2 mouse_current = {0.0f, 0.0f};
	// glm::vec2 mouse_previous = {0.0f, 0.0f}; 
	is_mouse_down = false;

	Zyklon::EventDispatcher dispatcher(event);
	if(event.get_event_type() == Zyklon::EventType::WindowResize)
	{
		m_aspect_ratio =
		static_cast<float>(Zyklon::Application::get().get_window().get_width()) / 
		static_cast<float>(Zyklon::Application::get().get_window().get_height());
		m_camera = std::make_shared<Zyklon::PerspectiveCamera>(glm::radians(m_fovy), m_aspect_ratio, m_near_plane, m_far_plane);
	}
	
	// TODO:
	// get the difference between the mouse current position and the mouse preivous position
	// normalize them between 0 and 1
	// multiply it by the transformation speed and delta time

	// if (event.get_event_type() == Zyklon::EventType::MouseButtonPressed)
	// {
	// 	dispatcher.Dispatch<Zyklon::MouseMovedEvent>([&](Zyklon::MouseMovedEvent& e) {
	// 		mouse_previous = {e.GetX(), e.GetY()};
	// 		ZYKLON_INFO("Mouse position previous: {0}, Y:{1}", e.GetX(), e.GetY());
	// 		return true;
	// 	});
	// }

	// if(dispatcher.Dispatch<Zyklon::MouseScrolledEvent>([&](Zyklon::MouseScrolledEvent& e) {
	// 		float x = e.GetXOffset();  // Access derived class methods
	// 		float y = e.GetYOffset();
	// 		// crude application
	// 		m_scroll_state_x = x;
	// 		m_scroll_state_y = y;
	// 		// ZYKLON_INFO("scrolled to: x: {0}, y: {1}",x,y); 
	// 		return true;  // Return true if the event was handled
	// }));
	// else {
	// 	m_scroll_state_x = 0;
	// 	m_scroll_state_y = 0;
	// }

}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Camera Uniforms");
		ImGui::Text("Camera options!");
		if(ImGui::SliderFloat("fov", &m_fovy, 20.0f, 120.0f, "%.2f", 5.0f))
			m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane);
		if(ImGui::SliderFloat("near plane", &m_near_plane, 0.1f, 100.0f, "%.2f", 5.0f))
			m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane);
		if(ImGui::SliderFloat("far plane", &m_far_plane, 100.0f, 200.0f, "%.2f", 5.0f))
			m_camera->recalculate_perspective_matrix(m_fovy, m_aspect_ratio, m_near_plane, m_far_plane);
		if (ImGui::Button("reset camera"))
			reset_state();
	ImGui::End();
	for ( auto sphere : m_sphere )
	{
		sphere->render_gui();
	}
}