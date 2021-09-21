#include "game.h"

void Game::Update(Viewer& viewer) {
	viewer.entities[viewer.g("jupiter")].Rotate(0.0, 1.0, 0.0, degToRad(viewer.dt * 45.0f));
	//viewer.entities[viewer.g("wall")].Rotate(0.0, 1.0, 0.0, degToRad(viewer.dt * 45.0f));
	viewer.updateEntities();
}

void Game::SetupScene(Viewer& viewer) {
	viewer.useSkybox("space");

	viewer.addEntity("crackedBrick", false, "crackedBrick", "default");
	viewer.addEntity("jupiter", false, "unused/jupiter", "default");
	viewer.addEntity("laserBrick", false, "laserBrick", "default");
	viewer.addEntity("shrinkBrick", false, "shrinkBrick", "default");
	viewer.addEntity("splitBrick", false, "splitBrick", "default");
	viewer.addEntity("armoredBrick", false, "armoredBrick", "default");
	viewer.addEntity("speedBrick", false, "speedBrick", "default");
	viewer.addEntity("brick", false, "brick", "default");
	viewer.addEntity("bar", true, "bar", "default");
	viewer.addEntity("ball", true, "ball", "default");
	viewer.addEntity("wall", false, "wall", "default");

	
	//viewer.entities[viewer.g("wall")].Scale(0.7f, 0.7f, 0.7f);
	std::cout << glm::to_string(viewer.entities[viewer.g("wall")].rotation) << std::endl;
	viewer.entities[viewer.g("wall")].Rotate(0.0f, 1.0f, 0.0f, degToRad(90.0f));
	std::cout << glm::to_string(viewer.entities[viewer.g("wall")].rotation) << std::endl;
	viewer.entities[viewer.g("jupiter")].Scale(0.2f, 0.2f, 0.2f);
	viewer.entities[viewer.g("jupiter")].moveTo(glm::vec3(-30.0f, 0.0f, 0.0f));
	viewer.entities[viewer.g("crackedBrick")].moveTo(glm::vec3(1.0f, 5.0f, -30.0f));
	viewer.entities[viewer.g("laserBrick")].moveTo(glm::vec3(3.0f, 5.0f, -30.0f));
	viewer.entities[viewer.g("shrinkBrick")].moveTo(glm::vec3(6.0f, 5.0f, -30.0f));
	viewer.entities[viewer.g("splitBrick")].moveTo(glm::vec3(1.0f, 2.5f, -30.0f));
	viewer.entities[viewer.g("armoredBrick")].moveTo(glm::vec3(3.5f, 2.5f, -30.0f));
	viewer.entities[viewer.g("speedBrick")].moveTo(glm::vec3(6.0f, 2.5f, -30.0f));
	viewer.entities[viewer.g("brick")].moveTo(glm::vec3(1.0f, 0.0f, -30.0f));
	viewer.entities[viewer.g("bar")].Scale(0.6f, 0.5f, 0.5f);
	viewer.entities[viewer.g("bar")].moveTo(glm::vec3(0.0f, -2.5f, -30.0f));
	viewer.entities[viewer.g("ball")].Scale(0.5f, 0.5f, 0.5f);
	viewer.entities[viewer.g("ball")].moveTo(glm::vec3(0.0f, -1.0f, -30.0f));
}

void Game::InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = { "unused/airplane", "unused/jupiter", "ball", "bar", "crackedBrick",
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick", "wall"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default") };

	viewer.LoadModel(models);
	viewer.loadShader(shaders);
}

void Game::Draw(Viewer& viewer) {
	viewer.drawEntities();
	viewer.drawSkybox();
}
