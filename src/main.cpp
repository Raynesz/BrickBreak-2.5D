// Issue: Right cubemap texture is flipped after first useSkybox().
// TODO: Create game assets (walls, skyboxes).
// TODO: Add game object classes.

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
#include "game.h"

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
int main() {
	Viewer viewer("BrickBreak 2.5D");
	ImGuiIO& io = InitializeUI(viewer);

	Game::InitializeResources(viewer);
	Game::SetupScene(viewer);

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
		Game::Update(viewer);

		// RENDER
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		NewUIFrame();
		
		Game::Draw(viewer);

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
