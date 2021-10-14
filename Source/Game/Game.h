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

struct PlayMusic {
	bool current = true;
	bool prev = true;
};

enum MainObjects {MainBar, LeftWall, RightWall, TopWall, MainLaser, J, MainBall, Victory, GameOver};

enum Sounds {Hit_S, Laser_S, Victory_S, Fail_S, Music_S};

class Game {
public:
	Viewer& viewer;
	glm::vec4 clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
	Camera camera;
	std::vector<Entity*> entities = {};
	std::vector<SoLoud::Wav*> sounds = {};
	int music;
	PlayMusic playMusic;
	bool controlsActive = true;
	bool paused = false;
	bool start = false;
	int end = 0;       // 0: Game hasn't ended, 1: Victory, 2: Defeat
	int createBall = 0;
	bool showAbout = false;
	bool showControls = false;
	bool splashScreen = true;
	float splashScreenDuration = 4.0f;

	Game(Viewer& _viewer);
	void SplashScreen();
	void Setup(int);
	void Update();
	void InitializeResources();
	void Inputs();
	void CleanUp();
	bool windowsOpen();
	void DrawUI(ImGuiIO&);
	void DrawText();
	void DrawControls(bool*, ImGuiIO&);
	void DrawAbout(bool*, bool*, bool*, bool*, ImGuiIO&, GLFWwindow*);
	void DrawMetrics(bool*, double);
	void Draw();
	void ShootLaser();

private:
	std::vector<int> balls = {};
	std::vector<int> bricks = {};
	Level levelData;

	bool showMetrics = false;

	void SelectLevel(int);
	Entity* get(std::string);
	void RandomizeLevelLayout();
	void CountBricks();
	void PopulateGrid();
	bool DoCollision(Ball*, int);
	void DestroyBrick(Ball*, int);
};
