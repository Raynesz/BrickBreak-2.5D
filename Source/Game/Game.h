#pragma once

#include "../Core/Viewer.h"
#include "config.h"
#include "Bar.h"
#include "Ball.h"
#include "Brick.h"
#include "Wall.h"
#include "Laser.h"

struct Level {
	std::vector<std::vector<std::string> > layout{ 6, std::vector<std::string>(14, "0") };
	int totalBricks;
};

enum MainObjects {MainBar, LeftWall, RightWall, TopWall, MainLaser, Jupiter, MainBall};

class Game {
public:
	glm::vec4 clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
	Camera camera;
	bool controlsActive;
	bool paused = false;
	bool start = false;
	bool end = false;
	int createBall = 0;

	void Setup(Viewer&, int);
	void Update(Viewer&, double);
	void InitializeResources(Viewer&);
	void Inputs(Viewer&);
	void CleanUp();
	bool windowsOpen();
	void DrawUI(GLFWwindow*, ImGuiIO&, float);
	void DrawControls(bool*, ImGuiIO&);
	void DrawAbout(bool*, bool*, bool*, ImGuiIO&, GLFWwindow*);
	void DrawMetrics(bool*, double);
	void Draw(Viewer&);

private:
	std::vector<Entity*> entities = {};
	std::vector<int> balls = {};
	std::vector<int> bricks = {};
	Level levelData;

	bool showAbout = false;
	bool showMetrics = true;
	bool showControls = false;

	void SelectLevel(int);
	Entity* get(std::string);
	void RandomizeLevelLayout();
	void CountBricks();
	void PopulateGrid(Viewer&);
};
