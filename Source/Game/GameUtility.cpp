#include "Game.h"

// Keys in this function are activated once per key event
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)						// UP
	{
		if (!game->start) {
			Ball* ball = static_cast<Ball*>(game->entities[MainBall]);
			ball->speed = ball->normal;
		}
		game->start = true;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{

	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)						// DOWN
	{
		game->paused = !game->paused;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{

	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)						// 1
	{
		game->Setup(1);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)						// 2
	{
		game->Setup(2);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)						// 3
	{
		game->Setup(3);
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)						// 4
	{
		game->Setup(4);
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)					// Esc
	{
		game->showAbout = !game->showAbout;
		game->showControls = false;
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS)						// F
	{
		game->ShootLaser();
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)						// R
	{
		game->camera.Set(game->viewer.width, game->viewer.height, FREE_FPV, true, glm::vec3(0.0f, 5.0f, 35.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)						// C
	{
		if (game->camera.type == CLICK_FPV) game->camera.type = FREE_FPV;
		else game->camera.type = CLICK_FPV;
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)						// V
	{
		if (game->camera.locked == false) game->camera.locked = true;
		else game->camera.locked = false;
		game->camera.firstClick = true;
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS)						// J
	{
		game->viewer.useSkybox(NO_SKYBOX);
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS)						// K
	{
		game->viewer.useSkybox("skyfly");
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS)						// L
	{
		game->viewer.useSkybox("space");
	}
}

// Called every frame
void Game::Inputs() {
	if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_PRESS)						// LEFT
	{
		static_cast<Bar*>(entities[MainBar])->move.left = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		static_cast<Bar*>(entities[MainBar])->move.left = false;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_PRESS)					// RIGHT
	{
		static_cast<Bar*>(entities[MainBar])->move.right = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		static_cast<Bar*>(entities[MainBar])->move.right = false;
	}
}

Entity* Game::get(std::string entityName) {
	for (int i = 0; i < entities.size(); i++) {
		if (entityName == entities[i]->name) return entities[i];
	}
}

void Game::Draw() {
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

	balls.clear();
	bricks.clear();
	for (auto entity : entities) delete entity;
	entities.clear();
}
