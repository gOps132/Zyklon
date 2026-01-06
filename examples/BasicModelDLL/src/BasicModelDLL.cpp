#include <Zyklon/Zyklon.h>
#include <imgui-test/imgui.h>

class DLLExampleLayer : public Zyklon::Layer {
public:
	DLLExampleLayer() : Layer("DLL Example")
	{
		ZYKLON_INFO("DLL Example Layer created - using shared Zyklon library!");

		// Test basic engine functionality
		auto &assetManager = Zyklon::AssetManager::getInstance();
		ZYKLON_INFO("AssetManager singleton accessed successfully from DLL");

		auto &sceneManager = Zyklon::SceneManager::getInstance();
		ZYKLON_INFO("SceneManager singleton accessed successfully from DLL");
	}

	virtual void onUpdate(Zyklon::Timestep ts) override
	{
		// Basic update logic
	}

	virtual void onEvent(Zyklon::Event &event) override
	{
		// Handle events
	}

	virtual void onImguiRender() override
	{
		// Simple ImGui window to prove DLL exports work
		ImGui::Begin("DLL Test");
		ImGui::Text("This window proves DLL exports are working!");
		ImGui::Text("Engine running from shared library (.dll/.so)");
		ImGui::End();
	}
};

class BasicModelDLL : public Zyklon::Application {
public:
	BasicModelDLL()
	{
		ZYKLON_INFO("BasicModelDLL application started with shared library");
		pushLayer(new DLLExampleLayer());
	}

	virtual ~BasicModelDLL() override
	{
		ZYKLON_INFO("BasicModelDLL application stopped");
	}
};

// Entry point - this function is exported from the DLL
Zyklon::Application *Zyklon::Application::createApplication()
{
	return new BasicModelDLL();
}