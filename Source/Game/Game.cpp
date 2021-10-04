#include "Game.h"

void Game::Update() {
	while (createBall > 0) {
		balls.push_back(entities.size());
		entities.push_back(new Ball("addBall", "addBall", "default", viewer.models, viewer.shaders,
			static_cast<Ball*>(entities[MainBall])->position, glm::vec3(1.0f, 1.0f, 1.0f), 0.4));
		createBall--;
	}

	Bar* bar = static_cast<Bar*>(entities[MainBar]);
	bar->Update(viewer.dt);

	// Do Collisions
	//		Bar to left wall
	if ((bar->position.x - bar->length) < bar->border.left) bar->position.x = bar->border.left + bar->length;
	entities[Jupiter]->Rotate(0.0, 1.0, 0.0, glm::radians(viewer.dt * 45.0f));
	//		Bar to right wall
	if ((bar->position.x + bar->length) > bar->border.right) bar->position.x = bar->border.right - bar->length;

	static_cast<Laser*>(entities[MainLaser])->Update(bar->position);

	for (int ballIndex : balls) {	
		Ball* ball = static_cast<Ball*>(entities[ballIndex]);
		if (!ball->destroyed && ball->position.y > bar->position.y - 3.0) {
			ball->Update(viewer.dt);
			for (int brickIndex : bricks) {
				if (DoCollision(ball, brickIndex)) DestroyBrick(ball, brickIndex);
			}
			DoCollision(ball, MainBar);
			DoCollision(ball, RightWall);
			DoCollision(ball, LeftWall);
			DoCollision(ball, TopWall);
		}
		else {
			ball->destroyed = true;
		}
	}

	// Check if player won
	if (levelData.totalBricks <= 0) {
		end = true;
		PlaySound(TEXT("Resources/Sounds/victory.wav"), NULL, SND_ASYNC);
		entities[Victory]->destroyed = false;
	}

	// Check if player lost
	if (static_cast<Ball*>(entities[MainBall])->position.y < bar->position.y) {
		end = true;
		PlaySound(TEXT("Resources/Sounds/fail.wav"), NULL, SND_ASYNC);
		entities[GameOver]->destroyed = false;
	}
}

void Game::ShootLaser() {
	if (!end && !paused) {
		Laser* laser = static_cast<Laser*>(entities[MainLaser]);
		if (laser->charges > 0) {
			PlaySound(TEXT("Resources/Sounds/laser.wav"), NULL, SND_ASYNC);
			for (int brick : bricks) {
				if (laser->position.x > entities[brick]->position.x - entities[brick]->scale.x &&
					laser->position.x < entities[brick]->position.x + entities[brick]->scale.x) {
					DestroyBrick(static_cast<Ball*>(entities[MainBall]), brick);
				}
			}
			laser->charges--;
		}
	}
}

bool Game::DoCollision(Ball* ball, int objectIndex) {
	Entity* object = entities[objectIndex];
	if (!object->destroyed) {
		glm::vec3 size = (object->name == "topWall") ? glm::vec3(object->scale.y, object->scale.x, object->scale.z) :
			glm::vec3(object->scale.x, object->scale.y, object->scale.z);
		Physics::Collision collision = Physics::CheckBallCollision(ball->position, ball->radius, object->position, size);
		if (std::get<0>(collision)) // if collision is true
		{
			PlaySound(TEXT("Resources/Sounds/hit.wav"), NULL, SND_ASYNC);
			Direction dir = std::get<1>(collision);
			glm::vec2 diff_vector = std::get<2>(collision);
			if (dir == LEFT || dir == RIGHT) // horizontal collision
			{
				ball->direction.x = -ball->direction.x; // reverse horizontal velocity
				// relocate
				float penetration = ball->radius - std::abs(diff_vector.x);
				if (dir == LEFT)
					ball->position.x += penetration; // move ball to right
				else
					ball->position.x -= penetration; // move ball to left;
			}
			else // vertical collision
			{
				ball->direction.y = -ball->direction.y; // reverse vertical velocity
				// relocate
				float penetration = ball->radius - std::abs(diff_vector.y);
				if (dir == UP)
					ball->position.y -= penetration; // move ball back up
				else
					ball->position.y += penetration; // move ball back down
			}
		}
		return std::get<0>(collision);
	}
	return false;
}

void Game::DestroyBrick(Ball* ball, int brickIndex) {
	Brick* brick = static_cast<Brick*>(entities[brickIndex]);
	brick->lives--;
	if (brick->lives == 0) {
		brick->destroyed = true;
		levelData.totalBricks--;
	}
	else brick->SetModel(viewer.models, "crackedBrick");
	if (brick->type == "laserBrick") {
		static_cast<Laser*>(entities[MainLaser])->charges++;
	}
	else if (brick->type == "splitBrick") {
		createBall++;
	}
	else if (brick->type == "speedBrick") {
		ball->adjustSpeed();
	}
	else if (brick->type == "shrinkBrick") {
		static_cast<Bar*>(entities[MainBar])->shrinkDuration += 5.0;
	}
}

void Game::Setup(int activeLevel) {
	CleanUp();
	start = false;
	end = false;
	camera.Set(viewer.width, viewer.height, FREE_FPV, false, glm::vec3(0.0f, 5.0f, 35.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	viewer.useSkybox(RANDOM_SKYBOX);

	entities.push_back(new Bar("bar", "bar", "default", viewer.models, viewer.shaders,						// Bar: 0
		glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 2.4, 0.5, 15.0f, 0.5f));

	entities.push_back(new Wall("leftWall", "wall", "default", viewer.models, viewer.shaders,				// LeftW: 1
		glm::vec3(-15.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0, 0.5));

	entities.push_back(new Wall("rightWall", "wall", "default", viewer.models, viewer.shaders,				// RightW: 2
		glm::vec3(15.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0, 0.5));

	entities.push_back(new Wall("topWall", "wall", "default", viewer.models, viewer.shaders,				// TopW: 3	
		glm::vec3(0.0f, 15.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 15.5, 0.5));

	entities.push_back(new Laser("laser", "laser", "baseColor", viewer.models, viewer.shaders,				// Laser: 4
		entities[MainBar]->position, glm::vec3(0.15f, 10.0f, 0.15f)));

	entities.push_back(new Entity("j", "unused/jupiter", "default", viewer.models, viewer.shaders,			// J: 5	
		glm::vec3(-30.0f, 0.0f, 60.0f), glm::vec3(0.2f, 0.2f, 0.2f)));

	balls.push_back(entities.size());
	entities.push_back(new Ball("ball", "ball", "default", viewer.models, viewer.shaders,					// Main Ball: 6
		glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.4));

	entities.push_back(new Entity("victory", "victory", "default", viewer.models, viewer.shaders,			// Victory Panel: 7	
		glm::vec3(0.0f, 6.0f, 1.1f), glm::vec3(9.0f, 1.0f, 9.0f)));

	entities.push_back(new Entity("gameOver", "gameOver", "default", viewer.models, viewer.shaders,			// GameOver Panel: 8	
		glm::vec3(0.0f, 6.0f, 1.1f), glm::vec3(9.0f, 1.0f, 9.0f)));

	entities[MainLaser]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));   // Paint laser red
	entities[TopWall]->Rotate(0.0, 0.0, 1.0, glm::radians(90.0f));
	entities[Victory]->Rotate(0.0, 0.0, 1.0, glm::radians(-90.0f));
	entities[Victory]->Rotate(1.0, 0.0, 0.0, glm::radians(-90.0f));
	entities[GameOver]->Rotate(0.0, 0.0, 1.0, glm::radians(-90.0f));
	entities[GameOver]->Rotate(1.0, 0.0, 0.0, glm::radians(-90.0f));
	entities[Victory]->destroyed = true;
	entities[GameOver]->destroyed = true;

	SelectLevel(activeLevel);
	PopulateGrid();
}

void Game::PopulateGrid() {
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

			if (type != "") {
				bricks.push_back(entities.size());
				entities.push_back(new Brick("brick" + std::to_string(i) + std::to_string(j), type, "default",
					viewer.models, viewer.shaders, glm::vec3(x, y, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
			}
			j++;
		}
		i++;
	}
}

void Game::InitializeResources() {
	std::vector<std::string> models = { "unused/airplane", "unused/jupiter", "ball", "addBall", "bar", "crackedBrick",
		"laserBrick", "shrinkBrick", "splitBrick", "armoredBrick", "speedBrick", "brick", "wall", "laser", "victory", "gameOver"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default"),
	shaderInput("baseColor", "default", "baseColor")};
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
			if (random(0, 100) >= 50) levelData.layout[i][j] = std::to_string(random(2, 6));
			else levelData.layout[i][j] = "1";
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
