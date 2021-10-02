#include "Game.h"

void Game::Inputs(Viewer& viewer) {
	if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_PRESS)						// UP
	{
		if (!start) {
			Ball* ball = static_cast<Ball*>(get("ball"));
			ball->speed = ball->normal;
		}
		start = true;
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
		Setup(viewer, 1);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_2) == GLFW_PRESS)						// 2
	{
		Setup(viewer, 2);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_3) == GLFW_PRESS)						// 3
	{
		Setup(viewer, 3);
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_4) == GLFW_PRESS)						// 4
	{
		Setup(viewer, 4);
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)					// Esc
	{
		showAbout = true;
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_C) == GLFW_PRESS)						// C
	{
		camera.Set(viewer.width, viewer.height, FREE_FPV, true, glm::vec3(0.0f, 5.0f, 35.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_V) == GLFW_PRESS)						// V
	{
		camera.locked = false;
		camera.firstClick = true;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_B) == GLFW_PRESS)						// B
	{
		static_cast<Brick*>(get("brick33"))->SetModel(viewer.models, "crackedBrick");
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_N) == GLFW_PRESS)						// N
	{
		static_cast<Brick*>(get("brick54"))->destroyed = true;
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
	if (glfwGetKey(viewer.window, GLFW_KEY_M) == GLFW_PRESS)						// L
	{
		camera.type = FREE_FPV;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_O) == GLFW_PRESS)						// O
	{
		paused = false;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_P) == GLFW_PRESS)						// P
	{
		paused = true;
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
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) levelData.layout[i][j] = "0";
	}
	levelData.totalBricks = 0;

	for (auto entity : entities) delete entity;
	entities.clear();
}
