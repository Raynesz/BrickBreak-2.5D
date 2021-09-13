// Issue: Right cubemap texture is flipped after first useSkybox().
// TODO: Create game assets in blender (bricks, ball, bar, walls).
//       - A single brick model can use many textures.

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
#include "Viewer.h"

void SetupScene(Viewer&);
void InitializeResources(Viewer&);
void FpsCounter(Viewer&);

int main() {
	Viewer viewer("BrickBreak 2.5D");
	InitializeResources(viewer);
	SetupScene(viewer);

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		// INPUT
		// Take care of all GLFW events
		glfwPollEvents();
		viewer.Inputs();
		// Handles camera inputs (delete this if you have disabled VSync)
		viewer.camera.Inputs(viewer.window, viewer.dt);
		// Updates and exports the camera matrix to the Vertex Shader
		viewer.camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		// UPDATE	
		viewer.entities[viewer.g("jupiter")].Rotate(0.0, 1.0, 0.0, degToRad(viewer.dt * 45.0f));
		viewer.entities[viewer.g("brick")].Rotate(0.0, 1.0, 0.0, degToRad(viewer.dt * 45.0f));
		viewer.updateEntities();

		// RENDER
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		viewer.drawEntities();
		viewer.drawSkybox();
		FpsCounter(viewer);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
	}

	return 0;
}

void FpsCounter(Viewer& viewer) {
	viewer.currentTime = glfwGetTime();
	viewer.dt = viewer.currentTime - viewer.previousTime;

	// Creates new title
	std::string FPS = std::to_string(1.0/viewer.dt);
	std::string ms = std::to_string(viewer.dt);
	std::string newTitle = viewer.windowName + "   |   " + FPS + " FPS / " + ms + " ms";
	glfwSetWindowTitle(viewer.window, newTitle.c_str());
	viewer.previousTime = viewer.currentTime;
}

void SetupScene(Viewer& viewer) {
	viewer.useSkybox("skyfly");

	viewer.addEntity("brick", true, "crackedBrick", "default");
	viewer.addEntity("jupiter", false, "jupiter", "default");

	viewer.entities[viewer.g("jupiter")].Scale(0.2f, 0.2f, 0.2f);
	viewer.entities[viewer.g("jupiter")].moveTo(glm::vec3(-30.0f, 0.0f, 0.0f));
}

void InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = {"airplane", "jupiter", "crackedBrick"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default"), shaderInput("asteroid", "asteroid", "default")};

	viewer.LoadModel(models);
	viewer.loadShader(shaders);
}
