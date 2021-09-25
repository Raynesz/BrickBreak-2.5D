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
	Viewer viewer("BrickBreak 2.5D");
	ImGuiIO& io = UI::Initialize(viewer.window);

	Game game;

	game.InitializeResources(viewer);
	game.Setup(viewer);

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		// INPUT
		// Take care of all GLFW events
		glfwPollEvents();

		if (!io.WantCaptureMouse) { // Game input is disabled if mouse is hovering over UI elements
			viewer.Inputs();
			// Handles camera inputs (delete this if you have disabled VSync)
			game.camera.Inputs(viewer.window, viewer.dt);
			// Updates and exports the camera matrix to the Vertex Shader
			game.Inputs(viewer);
		}
		game.camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		// UPDATE
		game.Update(viewer.dt);

		// RENDER
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		UI::NewFrame();
		
		game.Draw(viewer);

		if (viewer.showEscUI) UI::DrawAbout(&viewer.showEscUI, &viewer.showMetrics, &viewer.showControls, io, viewer.window);
		if (viewer.showMetrics) UI::DrawMetrics(&viewer.showMetrics, viewer.dt);
		if (viewer.showControls) UI::DrawControls(&viewer.showControls, io);
		UI::Render();

		viewer.FpsCounter();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
	}

	game.CleanUp();
	UI::Terminate();

	return 0;
}
