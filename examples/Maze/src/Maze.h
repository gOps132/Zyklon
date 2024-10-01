#ifndef __MAZE_H__
#define __MAZE_H__

#include <Zyklon/Zyklon.h>

class ExampleLayer : public Zyklon::Layer {
public:
	ExampleLayer();

	virtual void on_update(Zyklon::Timestep ts) override;
	virtual void on_event(Zyklon::Event &event) override;
	virtual void on_imgui_render() override;
	void reset_state();
private:
	std::shared_ptr<Zyklon::Shader> m_square_shader;
	std::shared_ptr<Zyklon::VertexBuffer> m_square_vertex_buffer;
	std::shared_ptr<Zyklon::IndexBuffer> m_square_index_buffer;
	std::shared_ptr<Zyklon::VertexArray> m_square_vertex_array;

	float m_color[3];

	glm::vec3 m_camera_position;
	float m_camera_rotation = 0.0f;

	float m_fovy = glm::radians(45.0f); // Field of view in the vertical direction
	float m_aspect_ratio =
		Zyklon::Application::get().get_window().get_width() / 
		Zyklon::Application::get().get_window().get_height(); // 1.5
	
	float m_near_plane = 0.1f;          // Near clipping plane distance
	float m_far_plane = 100.0f;         // Far clipping plane distance
	float m_camera_speed = 10.0f;
	float m_camera_rotation_speed = 1.5f;

	Zyklon::Camera* m_camera;

	glm::mat4 m_model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::vec3 m_model_position;
	// glm::mat4 view          = glm::mat4(1.0f);
	// glm::mat4 projection    = glm::mat4(1.0f);
};

class Maze : public Zyklon::Application {
public:
	Maze() { push_layer(new ExampleLayer()); }

	virtual ~Maze() override { ZYKLON_INFO("Stopped maze application"); }
};


#endif // __MAZE_H__