//
// Created by Gian Cedrick Epilan on 10/07/2020.
//

#include <Zyklon/Zyklon.h>
#include <imgui-test/imgui.h>

class ExampleLayer : public Zyklon::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	virtual void on_update() override
	{
		// if (Zyklon::Input::key_pressed(ZYKLON_KEY_TAB))
		//     ZYKLON_INFO("Tab Key is Pressed");
	}

	virtual void on_event(Zyklon::Event &event) override
	{
		// ZYKLON_TRACE("{0}", event);
	}

	virtual void on_imgui_render() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}
};

class Sandbox : public Zyklon::Application {
public:
	Sandbox() { push_layer(new ExampleLayer()); }

	virtual ~Sandbox() override { ZYKLON_INFO("Stopped sandbox application"); }
};

Zyklon::Application *Zyklon::Application::create_application()
{
	return new Sandbox();
}