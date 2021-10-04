#pragma once

#include "../Core/Viewer.h"
#include "config.h"
#include "Bar.h"
#include "Ball.h"
#include "Brick.h"
#include "Wall.h"
#include "Laser.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct Level {
	std::vector<std::vector<std::string> > layout{ 6, std::vector<std::string>(14, "0") };
	int totalBricks;
};

enum MainObjects {MainBar, LeftWall, RightWall, TopWall, MainLaser, Jupiter, MainBall, Victory, GameOver};

class Game {
public:
	Viewer& viewer;
	glm::vec4 clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
	Camera camera;
	bool controlsActive;
	bool paused = false;
	bool start = false;
	bool end = false;
	int createBall = 0;
	bool showAbout = false;
	bool showControls = false;

	Game(Viewer& _viewer) : viewer(_viewer) {}
	void Setup(int);
	void Update();
	void InitializeResources();
	void Inputs();
	void CleanUp();
	bool windowsOpen();
	void DrawUI(ImGuiIO&);
	void DrawControls(bool*, ImGuiIO&);
	void DrawAbout(bool*, bool*, bool*, ImGuiIO&, GLFWwindow*);
	void DrawMetrics(bool*, double);
	void Draw();
	void ShootLaser();

private:
	std::vector<Entity*> entities = {};
	std::vector<int> balls = {};
	std::vector<int> bricks = {};
	Level levelData;

	bool showMetrics = true;

	void SelectLevel(int);
	Entity* get(std::string);
	void RandomizeLevelLayout();
	void CountBricks();
	void PopulateGrid();
	bool DoCollision(Ball*, int);
	void DestroyBrick(Ball*, int);
};
