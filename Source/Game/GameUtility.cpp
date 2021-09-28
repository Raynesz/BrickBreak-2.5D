#include "Game.h"

void Game::Inputs(Viewer& viewer) {
	if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_PRESS)						// UP
	{
		camera.type = FREE_FPV;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_RELEASE)
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_DOWN) == GLFW_PRESS)						// DOWN
	{
		camera.type = CLICK_FPV;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{

	}

	if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_PRESS)						// LEFT
	{
		static_cast<Bar*>(get("bar"))->move.left = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		static_cast<Bar*>(get("bar"))->move.left = false;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_PRESS)					// RIGHT
	{
		static_cast<Bar*>(get("bar"))->move.right = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		static_cast<Bar*>(get("bar"))->move.right = false;
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_1) == GLFW_PRESS)						// 1
	{
		Setup(viewer);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_2) == GLFW_PRESS)						// 2
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_3) == GLFW_PRESS)						// 3
	{

	}

	if (glfwGetKey(viewer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)					// Esc
	{
		showAbout = true;
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_C) == GLFW_PRESS)						// C
	{
		camera.Set(viewer.width, viewer.height, FREE_FPV, true, glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_V) == GLFW_PRESS)						// V
	{
		camera.locked = false;
		camera.firstClick = true;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_J) == GLFW_PRESS)						// J
	{
		viewer.useSkybox(NO_SKYBOX);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_K) == GLFW_PRESS)						// K
	{
		viewer.useSkybox("skyfly");
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_L) == GLFW_PRESS)						// L
	{
		viewer.useSkybox("space");
	}
}

Entity* Game::get(std::string entityName) {
	for (int i = 0; i < entities.size(); i++) {
		if (entityName == entities[i]->name) return entities[i];
	}
}

void Game::Draw(Viewer& viewer) {
	viewer.drawEntities(camera, entities);
	viewer.drawSkybox(camera);
}

bool Game::windowsOpen() {
	bool isOpen = showAbout || showControls;
	if (isOpen) camera.firstClick = true;
	return isOpen;
}

void Game::CleanUp() {
	for (auto entity : entities) {
		delete entity;
	}
	entities.clear();
}