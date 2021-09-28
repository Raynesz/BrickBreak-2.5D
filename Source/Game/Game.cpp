#include "Game.h"

void Game::Update(double dt) {
	static_cast<Brick*>(get("jupiter"))->Rotate(0.0, 1.0, 0.0, degToRad(dt * 45.0f));
	static_cast<Bar*>(get("bar"))->Update(dt);
}

void Game::Setup(Viewer& viewer) {
	CleanUp();
	camera.Set(viewer.width, viewer.height, FREE_FPV, false, glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, -1.0f));
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

void Game::InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = { "unused/airplane", "unused/jupiter", "ball", "bar", "crackedBrick",
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick", "wall"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default") };
	std::vector<std::string> skyboxes = { "space", "skyfly" };

	viewer.loadModels(models);
	viewer.loadShaders(shaders);
	viewer.loadSkyboxes(skyboxes);
}

void Game::LoadLevel() {

}
