#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include <Zyklon/Zyklon.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Physics.h"
#include "UVSphere.h"

#include <vector>
#include <memory>

class ExampleLayer : public Zyklon::Layer {
public:
	ExampleLayer();

	virtual void onUpdate(Zyklon::Timestep ts) override;
	virtual void onEvent(Zyklon::Event &event) override;
	virtual void onImguiRender() override;
	void resetState();

	void drawGameObjectNode(Zyklon::Ref<Zyklon::GameObject> go);

private:
	Zyklon::Ref<Zyklon::Scene> m_my_scene;

	Zyklon::Ref<SystemState> m_planets;
	std::vector<Zyklon::Ref<Zyklon::GameObject>> m_sphere_game_objects;
	std::vector<Zyklon::Ref<PObject>> m_physics_objects_map;

	unsigned int index = 0;

	// Camera Controls
	Zyklon::Ref<Zyklon::OrbitControls> m_orbit;
	Zyklon::Ref<Zyklon::PanningControls>
		m_panning; // NEW: Panning controls instance
	Zyklon::Ref<Zyklon::Camera> m_camera;

	bool m_is_orbit_mode = true; // NEW: Toggle between modes

	float m_fovy = 45.0f;
	float m_aspect_ratio = Zyklon::Application::get().getWindow().getWidth() /
						   Zyklon::Application::get().getWindow().getHeight();
	float m_near_plane = 0.1f;
	float m_far_plane = 1000.0f;

	Zyklon::Ref<Zyklon::Shader> m_shader;
	Zyklon::Ref<Zyklon::Texture2D> m_texture;
};

class Gravity : public Zyklon::Application {
public:
	Gravity() { pushLayer(new ExampleLayer()); }

	virtual ~Gravity() override { ZYKLON_INFO("Stopped application"); }
};

#endif // __GRAVITY_H__