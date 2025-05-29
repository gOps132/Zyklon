#ifndef __GRID_H__
#define __GRID_H__

#include <Zyklon/Zyklon.h>

class ExampleLayer : public Zyklon::Layer {
public:
	ExampleLayer();

	virtual void onUpdate(Zyklon::Timestep ts) override;
	virtual void onEvent(Zyklon::Event &event) override;
	virtual void onImguiRender() override;
	void resetState();
private:
	std::shared_ptr<Zyklon::Shader> m_grid_shader;
	std::shared_ptr<Zyklon::VertexBuffer> m_grid_vertex_bfr;
	std::shared_ptr<Zyklon::IndexBuffer> m_grid_index_bfr;
	std::shared_ptr<Zyklon::VertexArray> m_grid_vertex_arr;

	glm::vec3 m_camera_position;
	float m_camera_rotation = 0.0f;

	float m_fovy = glm::radians(45.0f); // Field of view in the vertical direction
	float m_aspect_ratio =
		(float)Zyklon::Application::get().getWindow().getWidth() / 
		(float)Zyklon::Application::get().getWindow().getHeight(); // 1.5
	float m_near_plane = 0.1f;          // Near clipping plane distance
	float m_far_plane = 100.0f;         // Far clipping plane distance

	Zyklon::Camera* m_camera;

	glm::mat4 m_model			= glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::vec3 m_model_position;

	float* uniform_float_parameters = new float[2]();
};

class Grid : public Zyklon::Application {
public:
	Grid() { pushLayer(new ExampleLayer()); }

	virtual ~Grid() override { ZYKLON_INFO("Stopped grid application"); }
};


#endif // __GRID_H__