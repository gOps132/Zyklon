#ifndef __SANDBOX_H__
#define __SANDBOX_H__

#include <Zyklon/Zyklon.h>

class ExampleLayer : public Zyklon::Layer {
public:
	ExampleLayer();

	virtual void on_update(Zyklon::Timestep ts) override;
	virtual void on_event(Zyklon::Event &event) override;
	virtual void on_imgui_render() override;
	void reset_state();
private:
	std::vector<float> m_vertices;
	std::vector<uint32_t> m_indices;
	void generate_uv_sphere(
		const float p_radius,
		const int p_stacks,
		const int p_slices
	);
	/*
	void generate_circle(
		const int p_segments,
		const float p_radius,
		const float p_center_x,
		const float p_center_y
	);
	*/
	float m_radius 			= 1.0f;
	int m_stacks			= 50;
	int m_slices 			= 50;

//	uniforms
	float m_color[3];
	float m_stretch[3] = {1.0f, 1.0f, 1.0f};

	std::shared_ptr<Zyklon::Shader> m_shader;
	std::shared_ptr<Zyklon::VertexBuffer> m_vertex_buffer;
	std::shared_ptr<Zyklon::IndexBuffer> m_index_buffer;
	std::shared_ptr<Zyklon::VertexArray> m_vertex_array;

	glm::mat4 m_model         	= glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::vec3 m_model_position 	= glm::vec3(0.0f, 0.0f, 0.0f);
	float m_scale = 0.5f;
	float m_model_rotation_speed = 0.5f;
	float m_scroll_state_x = 0.0f;
	float m_scroll_state_y = 0.0f;

	std::shared_ptr<Zyklon::OrbitControls> m_orbit;
	std::shared_ptr<Zyklon::Camera> m_camera;
	glm::vec3 m_camera_position;
	glm::vec3 m_camera_vertical_orientation = {0.0f, 1.0f, 0.0f};
	float m_camera_rotation = 0.0f;
	float m_fovy = 45.0f; // Field of view in the vertical direction
	float m_aspect_ratio =
		Zyklon::Application::get().get_window().get_width() / 
		Zyklon::Application::get().get_window().get_height(); // 1.5
	float m_near_plane = 0.1f;          // Near clipping plane distance
	float m_far_plane = 100.0f;         // Far clipping plane distance
	float m_camera_speed = 10.0f;
	float m_camera_rotation_speed = 1.5f;
};

class Sphere : public Zyklon::Application {
public:
	Sphere() { push_layer(new ExampleLayer()); }

	virtual ~Sphere() override { ZYKLON_INFO("Stopped application"); }
};


#endif // __SANDBOX_H__