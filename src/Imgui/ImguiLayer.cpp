/*
 * Using GLFW key codes for now
 */

#include <zyklon_pch.h>

#include <Zyklon/Core/Application.h>
#include <Zyklon/Core/Core.h>

#include <imgui.h>

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

// should not be including glfw3 here
#include <GLFW/glfw3.h>

#include "ImguiLayer.h"

namespace Zyklon {

ImGuiLayer::ImGuiLayer() : Layer("Imgui Layer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::on_attach()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
	// Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
														// / Platform Windows
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform
	// windows can look identical to regular ones.
	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	Application &app = Application::get();
	GLFWwindow *window =
		static_cast<GLFWwindow *>(app.get_window().get_native_window());

	// Setup Platform/Renderer bindingss
	ImGui_ImplGlfw_InitForOpenGL(window, true);

// local developement machine debug
//TODO: 
#ifdef __APPLE__
	ImGui_ImplOpenGL3_Init("#version 330");
#else
	ImGui_ImplOpenGL3_Init("#version 450 core");
#endif

}

void ImGuiLayer::on_detach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::end()
{
	ImGuiIO &io = ImGui::GetIO();

	Application &app = Application::get();
	io.DisplaySize =
		ImVec2(app.get_window().get_width(), app.get_window().get_width());

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow *backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void ImGuiLayer::on_imgui_render()
{
	// static bool show = false;
	// ImGui::ShowDemoWindow(&show);
}

} // namespace Zyklon
