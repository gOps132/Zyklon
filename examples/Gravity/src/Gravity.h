#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include <Zyklon/Zyklon.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Physics.h"
#include "UVSphere.h"
#include "HexagonalSphere.h"

#include <vector>
#include <memory>

class ExampleLayer : public Zyklon::Layer {
public:
	ExampleLayer();

	virtual void on_update(Zyklon::Timestep ts) override;
	virtual void on_event(Zyklon::Event &event) override;
	virtual void on_imgui_render() override;
	void reset_state();
private:
	std::shared_ptr<SystemState> m_planets;
	std::vector<std::shared_ptr<HexagonalSphere>> m_sphere;

	unsigned int index = 0;
	bool look_at = false;

	glm::vec2 mouse_current = {0.0f, 0.0f};
	glm::vec2 mouse_previous = {0.0f, 0.0f}; 
	glm::vec2 m_mouse_moved_delta = {0.0f, 0.0f};
	bool is_mouse_down = false;

	std::shared_ptr<Zyklon::OrbitControls> m_orbit;
	std::shared_ptr<Zyklon::Camera> m_camera;
	glm::vec3 m_camera_position;
	// glm::vec3 m_camera_vertical_orientation = {0.0f, 1.0f, 0.0f};
	float m_camera_rotation = 0.0f;
	float m_fovy = 45.0f; // Field of view in the vertical direction
	float m_aspect_ratio =
		Zyklon::Application::get().get_window().get_width() / 
		Zyklon::Application::get().get_window().get_height(); // 1.5
	float m_near_plane = 0.1f;          // Near clipping plane distance
	float m_far_plane = 100.0f;         // Far clipping plane distance
	float m_camera_speed = 10.0f;

	float m_scale = 0.5f;
};

class Gravity : public Zyklon::Application {
public:
	Gravity() { push_layer(new ExampleLayer()); }

	virtual ~Gravity() override { ZYKLON_INFO("Stopped application"); }
};

#endif // __GRAVITY_H__