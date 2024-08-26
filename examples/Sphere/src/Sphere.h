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
	std::shared_ptr<Zyklon::Shader> m_shader;
	std::shared_ptr<Zyklon::VertexBuffer> m_vertex_buffer;
	// std::shared_ptr<IndexBuffer> m_cube_index_bfr;
	std::shared_ptr<Zyklon::VertexArray> m_vertex_array;

	glm::vec3 m_camera_position;
	float m_camera_rotation = 0.0f;

	float m_fovy = glm::radians(45.0f); // Field of view in the vertical direction
	float m_aspect_ratio =
		Zyklon::Application::get().get_window().get_width() / 
		Zyklon::Application::get().get_window().get_height(); // 1.5
	float m_near_plane = 0.1f;          // Near clipping plane distance
	float m_far_plane = 100.0f;         // Far clipping plane distance

	Zyklon::Camera* m_camera;

	glm::mat4 m_model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::vec3 m_model_position = glm::vec3(0.0f, 0.0f, 0.0f);

	float m_color[3];
	float m_model_pos[3];
};

class Sphere : public Zyklon::Application {
public:
	Sphere() { push_layer(new ExampleLayer()); }

	virtual ~Sphere() override { ZYKLON_INFO("Stopped application"); }
};


#endif // __SANDBOX_H__