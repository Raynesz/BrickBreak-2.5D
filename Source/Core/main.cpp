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

#include "Game.h"

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
int main() {
	Viewer viewer(WINDOW_NAME);
	ImGuiIO& io = UI::Initialize(viewer.window);

	Game game;

	game.InitializeResources(viewer);
	game.Setup(viewer, 4);

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		// INPUT
		// Take care of all GLFW events
		glfwPollEvents();

		game.controlsActive = !game.windowsOpen() && glfwGetWindowAttrib(viewer.window, GLFW_FOCUSED);

		if (game.controlsActive) {
			if (!io.WantCaptureMouse) { // Game input is disabled if mouse is hovering over UI elements
				viewer.Inputs();
				// Handles camera inputs (delete this if you have disabled VSync)
				if (!game.camera.locked) game.camera.Inputs(viewer.window, viewer.dt);
				// Updates and exports the camera matrix to the Vertex Shader
				game.Inputs(viewer);
			}
		}
		game.camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		if (game.camera.type != CLICK_FPV) {
			if (game.controlsActive) glfwSetInputMode(viewer.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			else glfwSetInputMode(viewer.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		// UPDATE
		if (!game.paused) game.Update(viewer, viewer.dt);

		// RENDER
		// Specify the color of the background
		glClearColor(game.clearColor.r, game.clearColor.g, game.clearColor.b, game.clearColor.a);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		UI::NewFrame();
		
		game.Draw(viewer);

		game.DrawUI(viewer.window, io, viewer.dt);
		UI::Render();

		viewer.FpsCounter();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
	}

	game.CleanUp();
	UI::Terminate();

	return 0;
}
