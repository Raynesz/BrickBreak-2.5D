#include "Game.h"

void Game::DrawUI(ImGuiIO& io) {
	if (showAbout) DrawAbout(&showAbout, &showMetrics, &showControls, io, viewer.window);
	if (showMetrics) DrawMetrics(&showMetrics, viewer.dt);
	if (showControls) DrawControls(&showControls, io);
}

void Game::DrawControls(bool* show, ImGuiIO& io) {
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
	ImGui::Begin("Controls", show, ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Left arrow - Move player bar left.");
	ImGui::Text("Right arrow - Move player bar right.");
	ImGui::Text("Up arrow - Launch ball.");
	ImGui::Text("Down arrow - Pause game.");
	ImGui::Text("F - Fire laser when ready.");
	ImGui::Text("1, 2, 3 - Choose level.");
	ImGui::Text("4 - Play random level.");
	ImGui::TextWrapped("C - Switch between free to look and click to look camera.");
	ImGui::Text("V - Toggle lock/unlock camera.");
	ImGui::Text("R - Reset camera.");
	ImGui::Text("W - Move camera forward.");
	ImGui::Text("A - Move camera left.");
	ImGui::Text("S - Move camera backwards.");
	ImGui::Text("D - Move camera right.");
	ImGui::Text("Left Shift - Hold to increase camera speed.");
	ImGui::Text("Spacebar - Move camera up.");
	ImGui::Text("Left Control - Move camera down.");
	ImGui::Text("J - Do not use skybox.");
	ImGui::Text("K - Use Skyfly skybox.");
	ImGui::Text("L - Use Space skybox.");
	ImGui::Text("");
	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - 45);
	if (ImGui::Button("Close", ImVec2(90, 30))) *show = false;
	ImGui::End();
}

void Game::DrawAbout(bool* show, bool* showMetrics, bool* showControls, ImGuiIO& io, GLFWwindow* window) {
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
	// ImGUI window creation
	ImGui::Begin("About", show, ImGuiWindowFlags_NoCollapse);
	ImGui::Text("BrickBreak 2.5D v1.0.0");
	ImGui::Text("Developed by github.com/raynesz");
	ImGui::Separator();
	ImGui::Text("How to play:");
	ImGui::TextWrapped("Break every brick to win. Drop the main ball and you lose! Moving the bar, while the ball hits it, changes the ball's trajectory."
	" Edit the level files in the Resources folder to create your own 14x6 brick levels (numbers 0 to 6 for every brick type).");
	ImGui::Separator();
	ImGui::TextWrapped("This game is a remastered version of a project I made during my student years."
		"It now uses a modern OpenGL renderer based on tutorials by Victor Gordan and learnopengl.com and some of the in-game assets were made anew.");
	ImGui::TextWrapped("Textures for the wooden bar provided for free by vecteezy.com. Contains assets from ambientCG.com,"
		" licensed under CC0 1.0 Universal. Game winning sound created by Mativve from Freesound.org.");
	ImGui::Text("Libraries/Frameworks used: GLFW/glad, glm, Dear ImGui, stb image loader, nlohmann's json parser.");
	ImGui::Text("Additionally, Blender was used as the 3D modeling tool.");
	ImGui::Separator();
	ImGui::Checkbox("Show Metrics", showMetrics);
	ImGui::SameLine(150);
	if (ImGui::Button("Controls", ImVec2(90, 30))) *showControls = true;
	ImGui::Text("");
	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - 45);
	if (ImGui::Button("Quit Game", ImVec2(90, 30))) glfwSetWindowShouldClose(window, GL_TRUE);
	// Ends the window
	ImGui::End();
}

void Game::DrawMetrics(bool* show, double dt) {
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Metrics", show, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text("Metrics");
		ImGui::Separator();
		ImGui::Text("FPS: %.1f", 1.0f / dt);
		ImGui::Text("%.3f ms per frame", dt);
		ImGui::Separator();
		ImGui::Text("Press ESC for info.");
	}
	ImGui::End();
}
