#include "game.h"

void Game::Update(Viewer& viewer) {
	viewer.entities[viewer.get("jupiter")].Rotate(0.0, 1.0, 0.0, degToRad(viewer.dt * 45.0f));
	viewer.updateEntities();
}

void Game::SetupScene(Viewer& viewer) {
	viewer.useSkybox(RANDOM_SKYBOX);

	viewer.addEntity("bar", "bar", "default", glm::vec3(0.0f, -2.5f, -30.0f), glm::vec3(0.6f, 0.5f, 0.5f));
	viewer.addEntity("ball", "ball", "default", glm::vec3(0.0f, -1.0f, -30.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	viewer.addEntity("leftWall", "wall", "default", glm::vec3(-10.0f, 4.0f, -30.0f), glm::vec3(1.0f, 0.5f, 10.0f));
	viewer.addEntity("rightWall", "wall", "default", glm::vec3(10.0f, 4.0f, -30.0f), glm::vec3(1.0f, 0.5f, 10.0f));
	viewer.addEntity("topWall", "wall", "default", glm::vec3(0.0f, 14.5f, -30.0f), glm::vec3(1.0f, 0.5f, 10.5f));
	viewer.addEntity("jupiter", "unused/jupiter", "default", glm::vec3(-30.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));

	viewer.entities[viewer.get("leftWall")].Rotate(1.0f, 0.0f, 0.0f, degToRad(90.0f));
	viewer.entities[viewer.get("leftWall")].Rotate(0.0f, 0.0f, 1.0f, degToRad(90.0f));

	viewer.entities[viewer.get("rightWall")].Rotate(1.0f, 0.0f, 0.0f, degToRad(90.0f));
	viewer.entities[viewer.get("rightWall")].Rotate(0.0f, 0.0f, 1.0f, degToRad(90.0f));

	viewer.entities[viewer.get("topWall")].Rotate(0.0f, 1.0f, 0.0f, degToRad(90.0f));
}

void Game::Inputs(Viewer& viewer) {
	if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_PRESS)						//UP
	{
		//playerMove.forward = true;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_PRESS)						//UP
	{
		viewer.playerMove.back = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		viewer.playerMove.back = false;
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_PRESS)					//DOWN
	{
		viewer.playerMove.forward = true;
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		viewer.playerMove.forward = false;
	}

	if (glfwGetKey(viewer.window, GLFW_KEY_1) == GLFW_PRESS)
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_2) == GLFW_PRESS)
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_3) == GLFW_PRESS)
	{

	}

	if (glfwGetKey(viewer.window, GLFW_KEY_J) == GLFW_PRESS)
	{
		viewer.useSkybox(RANDOM_SKYBOX);
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

void Game::InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = { "unused/airplane", "unused/jupiter", "ball", "bar", "crackedBrick",
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick", "wall"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default") };
	std::vector<std::string> skyboxes = { "space", "skyfly" };

	viewer.loadModels(models);
	viewer.loadShaders(shaders);
	viewer.loadSkyboxes(skyboxes);
}

void Game::Draw(Viewer& viewer) {
	viewer.drawEntities();
	viewer.drawSkybox();
}
