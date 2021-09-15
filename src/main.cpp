// Issue: Right cubemap texture is flipped after first useSkybox().
// TODO: Create game assets (walls, skyboxes).
// TODO: Implement game loops (InitializeResources, SetupScene, Update, Render).

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
#include "ui.h"

void SetupScene(Viewer&);
void InitializeResources(Viewer&);

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
int main() {
	Viewer viewer("BrickBreak 2.5D");
	ImGuiIO& io = InitializeUI(viewer);

	InitializeResources(viewer);
	SetupScene(viewer);

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		// INPUT
		// Take care of all GLFW events
		glfwPollEvents();

		if (!io.WantCaptureMouse) { // Game input is disabled if mouse is hovering over UI elements
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

		NewUIFrame();
		
		viewer.drawEntities();
		viewer.drawSkybox();

		if (viewer.showAbout) DrawUIAbout(&viewer.showAbout, &viewer.showMetrics, io, viewer.window);
		if (viewer.showMetrics) DrawUIMetrics(&viewer.showMetrics, viewer.dt);
		RenderUI();

		viewer.FpsCounter();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
	}

	TerminateUI();

	return 0;
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
