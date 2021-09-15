#include "ui.h"

ImGuiIO& InitializeUI(Viewer& viewer) {
	// Initialize Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(viewer.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	return io;
}

void NewUIFrame() {
	// Tell OpenGL a new frame is about to begin
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void DrawUIAbout(bool* show, bool* showMetrics, ImGuiIO& io, GLFWwindow* window) {
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
	// ImGUI window creation
	ImGui::Begin("About", show, ImGuiWindowFlags_NoCollapse);
	ImGui::Text("BrickBreak 2.5D v0.1.0");
	ImGui::Text("Developed by github.com/raynesz");
	ImGui::Separator();
	ImGui::Text("This game is a remastered version of a project I made during my student years."
		"It now uses a modern OpenGL renderer and some of the in-game assets were made anew.");
	ImGui::Text("Textures for the wooden bar and ball provided for free by vecteezy.com and ambientcg.com respectively.");
	ImGui::Text("Libraries / Frameworks used: GLFW/glad, glm, Dear ImGui, stb image loader, nlohmann's json parser.");
	ImGui::Text("Additionally, Blender was used as the 3D modeling tool.");
	ImGui::Separator();
	ImGui::Checkbox("Show Metrics", showMetrics);
	ImGui::Text("");
	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - 45);
	if (ImGui::Button("Quit Game", ImVec2(90, 30))) glfwSetWindowShouldClose(window, GL_TRUE);
	// Ends the window
	ImGui::End();
}

void DrawUIMetrics(bool* show, double dt) {
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Metrics", show, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text("Metrics");
		ImGui::Separator();
		ImGui::Text("FPS: %.1f", 1.0f /dt);
		ImGui::Text("%.3f ms per frame", dt);
		ImGui::Separator();
		ImGui::Text("Press ESC for info.");
	}
	ImGui::End();
}

void RenderUI() {
	// Renders the ImGUI elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void TerminateUI() {
	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
