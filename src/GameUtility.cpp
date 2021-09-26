#include "Game.h"

void Game::Inputs(Viewer& viewer) {
	if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_PRESS)						//UP
	{
		camera.type = FREE_FPV;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_RELEASE)
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_DOWN) == GLFW_PRESS)						//UP
	{
		camera.type = CLICK_FPV;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{

	}

	if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_PRESS)						//UP
	{
		static_cast<Bar*>(get("bar"))->move.left = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		static_cast<Bar*>(get("bar"))->move.left = false;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_PRESS)					//DOWN
	{
		static_cast<Bar*>(get("bar"))->move.right = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		static_cast<Bar*>(get("bar"))->move.right = false;
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_1) == GLFW_PRESS)
	{
		Setup(viewer);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_2) == GLFW_PRESS)
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_3) == GLFW_PRESS)
	{

	}

	if (glfwGetKey(viewer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		showAbout = true;
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera.Set(viewer.width, viewer.height, FREE_FPV, true, glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_V) == GLFW_PRESS)
	{
		camera.locked = false;
		camera.firstClick = true;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_J) == GLFW_PRESS)
	{
		viewer.useSkybox(NO_SKYBOX);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_K) == GLFW_PRESS)
	{
		viewer.useSkybox("skyfly");
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_L) == GLFW_PRESS)
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
