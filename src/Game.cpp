#include "Game.h"

void Game::Update(double dt) {
	static_cast<Brick*>(get("jupiter"))->Rotate(0.0, 1.0, 0.0, degToRad(dt * 45.0f));
	static_cast<Bar*>(get("bar"))->Update(dt);
}

void Game::Setup(Viewer& viewer) {
	CleanUp();
	camera.Initialize(viewer.width, viewer.height, glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	viewer.useSkybox(RANDOM_SKYBOX);

	entities.push_back(new Bar("bar", "bar", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, -2.5f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), 3.0, 0.5));

	entities.push_back(new Brick("jupiter", "unused/jupiter", "default", viewer.models, viewer.shaders,
		glm::vec3(-30.0f, 0.0f, 60.0f), glm::vec3(0.2f, 0.2f, 0.2f)));

	entities.push_back(new Ball("ball", "ball", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.4));

	entities.push_back(new Wall("leftWall", "wall", "default", viewer.models, viewer.shaders,
		glm::vec3(-10.0f, 5.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0, 0.5));

	entities.push_back(new Wall("rightWall", "wall", "default", viewer.models, viewer.shaders,
		glm::vec3(10.0f, 5.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0, 0.5));

	entities.push_back(new Wall("topWall", "wall", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, 15.5f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.5, 0.5));

	entities.push_back(new Brick("laserBrick", "laserBrick", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, 5.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

	static_cast<Wall*>(get("topWall"))->Rotate(0.0, 0.0, 1.0, degToRad(90.0f));
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

void Game::Inputs(Viewer& viewer) {
	if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_PRESS)						//UP
	{
		Setup(viewer);
	}
	else if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		
	}
	if (glfwGetKey(viewer.window, GLFW_KEY_DOWN) == GLFW_PRESS)						//UP
	{
		
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

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_2) == GLFW_PRESS)
	{

	}
	if (glfwGetKey(viewer.window, GLFW_KEY_3) == GLFW_PRESS)
	{

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

void Game::InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = { "unused/airplane", "unused/jupiter", "ball", "bar", "crackedBrick",
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick", "wall"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default") };
	std::vector<std::string> skyboxes = { "space", "skyfly" };

	viewer.loadModels(models);
	viewer.loadShaders(shaders);
	viewer.loadSkyboxes(skyboxes);
}

void Game::CleanUp() {
	for (auto entity : entities) {
		delete entity;
	}
	entities.clear();
}
