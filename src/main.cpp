// Issue: Right cubemap texture is flipped after first useSkybox().
// TODO: Implement a basic ImGUI menu.
// TODO: Create game assets (walls, skyboxes).

// The app will use the main GPU installed on the system
#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) DWORD NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif

#include <iostream>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Viewer.h"

void SetupScene(Viewer&);
void InitializeResources(Viewer&);
void FpsCounter(Viewer&);

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
int main() {
	Viewer viewer("BrickBreak 2.5D");

	// Initialize Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(viewer.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	InitializeResources(viewer);
	SetupScene(viewer);

	float menuWidth = 100.f;
	float menuHeight = 200.f;

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		// INPUT
		// Take care of all GLFW events
		glfwPollEvents();

		if (!io.WantCaptureMouse) {
			viewer.Inputs();
			// Handles camera inputs (delete this if you have disabled VSync)
			viewer.camera.Inputs(viewer.window, viewer.dt);
			// Updates and exports the camera matrix to the Vertex Shader
		}
		viewer.camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		// UPDATE
		viewer.entities[viewer.g("jupiter")].Rotate(0.0, 1.0, 0.0, degToRad(viewer.dt * 45.0f));
		viewer.updateEntities();

		// RENDER
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		viewer.drawEntities();
		viewer.drawSkybox();
		FpsCounter(viewer);

		if (viewer.showMenu) {
			ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
			ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
			// ImGUI window creation
			ImGui::Begin("About", &viewer.showMenu, ImGuiWindowFlags_NoCollapse);
			ImGui::Text("BrickBreak 2.5D v0.1.0");
			ImGui::Text("Developed by github.com/raynesz");
			ImGui::Separator();
			ImGui::Text("This game is a remastered version of a project I made during my student years."
				"It now uses a modern OpenGL renderer and some of the in-game assets were made anew.");
			ImGui::Text("Textures for the wooden bar and ball provided for free by vecteezy.com and ambientcg.com respectively.");
			ImGui::Text("Libraries / Frameworks used: GLFW/glad, glm, Dear ImGui, stb image loader, nlohmann's json parser.");
			ImGui::Text("Additionally, Blender was used as the 3D modeling tool.");
			ImGui::Separator();
			ImGui::Checkbox("Show Metrics", &viewer.showMetrics);
			ImGui::Text("");
			ImGui::SameLine(ImGui::GetWindowWidth()/2 - 45);
			if (ImGui::Button("Quit Game", ImVec2(90, 30))) glfwSetWindowShouldClose(viewer.window, GL_TRUE);
			// Ends the window
			ImGui::End();
		}

		if (viewer.showMetrics) {
			ImGui::SetNextWindowPos(ImVec2(10, 10));
			ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
			if (ImGui::Begin("Metrics", &viewer.showMetrics, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize 
				| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove))
			{
				ImGui::Text("Metrics");
				ImGui::Separator();
				ImGui::Text("FPS: %.1f", 1.0f / viewer.dt);
				ImGui::Text("%.3f ms per frame", viewer.dt);
				ImGui::Separator();
				ImGui::Text("Press ESC for info.");
			}
			ImGui::End();
		}

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

void FpsCounter(Viewer& viewer) {
	viewer.currentTime = glfwGetTime();
	viewer.dt = viewer.currentTime - viewer.previousTime;

	/*
	// Creates new title
	std::string FPS = std::to_string(1.0/viewer.dt);
	std::string ms = std::to_string(viewer.dt);
	std::string newTitle = viewer.windowName + "   |   " + FPS + " FPS / " + ms + " ms";
	glfwSetWindowTitle(viewer.window, newTitle.c_str());
	*/

	viewer.previousTime = viewer.currentTime;
}

void SetupScene(Viewer& viewer) {
	viewer.useSkybox("skyfly");

	viewer.addEntity("crackedBrick", false, "crackedBrick", "default");
	viewer.addEntity("jupiter", false, "unused/jupiter", "default");
	viewer.addEntity("laserBrick", false, "laserBrick", "default");
	viewer.addEntity("shrinkBrick", false, "shrinkBrick", "default");
	viewer.addEntity("splitBrick", false, "splitBrick", "default");
	viewer.addEntity("armoredBrick", false, "armoredBrick", "default");
	viewer.addEntity("speedBrick", false, "speedBrick", "default");
	viewer.addEntity("brick", false, "brick", "default");
	viewer.addEntity("bar", true, "bar", "default");
	viewer.addEntity("ball", true, "ball", "default");

	viewer.entities[viewer.g("jupiter")].Scale(0.2f, 0.2f, 0.2f);
	viewer.entities[viewer.g("jupiter")].moveTo(glm::vec3(-30.0f, 0.0f, 0.0f));
	viewer.entities[viewer.g("crackedBrick")].moveTo(glm::vec3(1.0f, 5.0f, -30.0f));
	viewer.entities[viewer.g("laserBrick")].moveTo(glm::vec3(3.5f, 5.0f, -30.0f));
	viewer.entities[viewer.g("shrinkBrick")].moveTo(glm::vec3(6.0f, 5.0f, -30.0f));
	viewer.entities[viewer.g("splitBrick")].moveTo(glm::vec3(1.0f, 2.5f, -30.0f));
	viewer.entities[viewer.g("armoredBrick")].moveTo(glm::vec3(3.5f, 2.5f, -30.0f));
	viewer.entities[viewer.g("speedBrick")].moveTo(glm::vec3(6.0f, 2.5f, -30.0f));
	viewer.entities[viewer.g("brick")].moveTo(glm::vec3(1.0f, 0.0f, -30.0f));
	viewer.entities[viewer.g("bar")].Scale(0.6f, 0.5f, 0.5f);
	viewer.entities[viewer.g("bar")].moveTo(glm::vec3(0.0f, -2.5f, -30.0f));
	viewer.entities[viewer.g("ball")].Scale(0.4f, 0.4f, 0.4f);
	viewer.entities[viewer.g("ball")].moveTo(glm::vec3(0.0f, -1.0f, -30.0f));
}

void InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = {"unused/airplane", "unused/jupiter", "ball", "bar", "crackedBrick", 
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default")};

	viewer.LoadModel(models);
	viewer.loadShader(shaders);
}
