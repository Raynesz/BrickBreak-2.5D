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

struct Text {
	std::string text;
	float w;
	float h;
	float scale;
};

enum MainObjectsEnum {MainBar, LeftWall, RightWall, TopWall, MainLaser, J, MainBall, Victory, GameOver};

enum SoundsEnum {Hit_S, Laser_S, Victory_S, Defeat_S, Music_S};

enum TextsEnum {Name_T, Hint_T, Pause_T, Victory_T, Defeat_T};

class Game {
public:
	Viewer& viewer;
	glm::vec4 clearColor = glm::vec4(0.0f, 0.13f, 0.25f, 1.0f);
	Camera camera;
	std::vector<Entity*> entities = {};
	std::vector<SoLoud::Wav*> sounds = {};
	std::vector<Text> texts = {};
	int music;
	PlayMusic playMusic;
	bool controlsActive = true;
	bool paused = false;
	bool start = false;
	int end = 0;       // 0: Game hasn't ended, 1: Victory, 2: Defeat
	int createBall = 0;
	bool showAbout = false;
	bool showControls = false;
	bool showText = true;
	bool showHint = true;
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
	void DrawAbout(bool*, bool*, bool*, bool*, bool*, ImGuiIO&, GLFWwindow*);
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
