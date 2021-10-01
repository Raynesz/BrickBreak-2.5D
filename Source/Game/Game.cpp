#include "Game.h"

void Game::Update(double dt) {
	// Grab reference to entities
	Brick* jupiter = static_cast<Brick*>(get("jupiter"));
	Ball* ball = static_cast<Ball*>(get("ball"));
	Wall* leftWall = static_cast<Wall*>(get("leftWall"));
	Wall* rightWall = static_cast<Wall*>(get("rightWall"));
	Wall* topWall = static_cast<Wall*>(get("topWall"));
	Bar* bar = static_cast<Bar*>(get("bar"));

	jupiter->Rotate(0.0, 1.0, 0.0, glm::radians(dt * 45.0f));
	bar->Update(dt);
	ball->Update(dt);

	// Do Collisions
	//		Bar to left wall
	if ((bar->position.x - bar->length) < bar->border.left) bar->position.x = bar->border.left + bar->length;
	//		Bar to right wall
	if ((bar->position.x + bar->length) > bar->border.right) bar->position.x = bar->border.right - bar->length;
}

void Game::Setup(Viewer& viewer, int activeLevel) {
	CleanUp();
	srand(time(NULL));
	camera.Set(viewer.width, viewer.height, FREE_FPV, false, glm::vec3(0.0f, 5.0f, 35.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	viewer.useSkybox(RANDOM_SKYBOX);

	entities.push_back(new Brick("jupiter", "unused/jupiter", "default", viewer.models, viewer.shaders,
		glm::vec3(-30.0f, 0.0f, 60.0f), glm::vec3(0.2f, 0.2f, 0.2f)));

	entities.push_back(new Ball("ball", "ball", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.4));

	entities.push_back(new Wall("leftWall", "wall", "default", viewer.models, viewer.shaders,
		glm::vec3(-15.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0, 0.5));

	entities.push_back(new Wall("rightWall", "wall", "default", viewer.models, viewer.shaders,
		glm::vec3(15.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0, 0.5));

	entities.push_back(new Wall("topWall", "wall", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, 15.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 15.5, 0.5));

	entities.push_back(new Bar("bar", "bar", "default", viewer.models, viewer.shaders,
		glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 3.0, 0.5, 15.0f, 0.5f));

	static_cast<Wall*>(get("topWall"))->Rotate(0.0, 0.0, 1.0, glm::radians(90.0f));

	SelectLevel(activeLevel);
	PopulateGrid(viewer);
}

void Game::PopulateGrid(Viewer& viewer) {
	std::string type;
	int i = 0;
	int j;
	
	for (float y = 13.5f; y >= 3.5f; y -= 2.0f) {
		j = 0;
		for (float x = -13.0f; x <= 13.0f; x += 2.0f) {
			if (levelData.layout[i][j] == "1") type = "brick";
			else if (levelData.layout[i][j] == "2") type = "speedBrick";
			else if (levelData.layout[i][j] == "3") type = "armoredBrick";
			else if (levelData.layout[i][j] == "4") type = "laserBrick";
			else if (levelData.layout[i][j] == "5") type = "shrinkBrick";
			else if (levelData.layout[i][j] == "6") type = "splitBrick";
			else type = "";

			if (type != "") entities.push_back(new Brick("brick"+std::to_string(i)+ std::to_string(j), type, "default",
				viewer.models, viewer.shaders, glm::vec3(x, y, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
			j++;
		}
		i++;
	}
}

void Game::InitializeResources(Viewer& viewer) {
	std::vector<std::string> models = { "unused/airplane", "unused/jupiter", "ball", "bar", "crackedBrick",
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick", "wall"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default") };
	std::vector<std::string> skyboxes = { "skyfly", "space" };

	viewer.loadModels(models);
	viewer.loadShaders(shaders);
	viewer.loadSkyboxes(skyboxes);
}

void Game::SelectLevel(int levelNumber) {
	std::string file;
	bool random = false;
	switch (levelNumber) {
	case 1:
		file = "Resources/Levels/level1.csv";
		break;
	case 2:
		file = "Resources/Levels/level2.csv";
		break;
	case 3:
		file = "Resources/Levels/level3.csv";
		break;
	default:
		random = true;
	}

	if (random) {
		RandomizeLevelLayout();
	}
	else {
		levelData.layout = inputCSV(file);
		CountBricks();
	}
}

void Game::RandomizeLevelLayout() {
	for (int i = 0; i < levelData.layout.size(); i++) {
		for (int j = 0; j < levelData.layout[i].size(); j++) {
			levelData.layout[i][j] = std::to_string(random(0, 6));
			if (levelData.layout[i][j] != "0") levelData.totalBricks++;
		}
	}
}

void Game::CountBricks() {
	for (int i = 0; i < levelData.layout.size(); i++) {
		for (int j = 0; j < levelData.layout[i].size(); j++) {
			if (levelData.layout[i][j] != "0") levelData.totalBricks++;
		}
	}
}
