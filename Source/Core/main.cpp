/*// The app will use the main GPU installed on the system
#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) DWORD NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif*/

#include "Game.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
//int main() {
	SoLoud::Soloud* soloud = new SoLoud::Soloud();	// Sound Engine core
	soloud->init();	// Initialize SoLoud (automatic back-end selection)
	Viewer viewer(WINDOW_NAME, *soloud);	// Create viewer and attach sound engine
	ImGuiIO& io = UI::Initialize(viewer.window);

	srand(time(NULL));
	Game* game = new Game(viewer);	// Create game and attach it to the viewer

	glfwSetWindowUserPointer(viewer.window, game);
	glfwSetKeyCallback(viewer.window, key_callback);

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		// INPUT
		// Take care of all GLFW events
		glfwPollEvents();

		game->controlsActive = !game->windowsOpen() && glfwGetWindowAttrib(viewer.window, GLFW_FOCUSED);

		if (game->controlsActive && !game->splashScreen) {
			if (!io.WantCaptureMouse) { // Game input is disabled if mouse is hovering over UI elements
				viewer.Inputs();
				// Handles camera inputs (delete this if you have disabled VSync)
				if (!game->camera.locked) game->camera.Inputs(viewer.window, viewer.dt);
				// Updates and exports the camera matrix to the Vertex Shader
				game->Inputs();
			}
		}
		game->camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		if (game->camera.type != CLICK_FPV) {
			if (game->controlsActive) glfwSetInputMode(viewer.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			else glfwSetInputMode(viewer.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		// UPDATE
		game->Update();

		// RENDER
		// Specify the color of the background
		glClearColor(game->clearColor.r, game->clearColor.g, game->clearColor.b, game->clearColor.a);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw 3D Game Objects
		glFrontFace(GL_CCW);
		glDisable(GL_BLEND);
		game->Draw();

		// Draw Text
		glFrontFace(GL_CW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		game->DrawText();

		// Draw UI
		UI::NewFrame();
		game->DrawUI(io);
		UI::Render();

		viewer.FpsCounter();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
	}

	viewer.soloud.deinit();
	game->CleanUp();
	UI::Terminate();
	delete game;
	delete soloud;

	return 0;
}
