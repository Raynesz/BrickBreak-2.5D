#pragma once

#include "../Core/Viewer.h"
#include "config.h"
#include "Bar.h"
#include "Ball.h"
#include "Brick.h"
#include "Wall.h"

class Game {
public:
	glm::vec4 clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
	Camera camera;
	std::vector<Entity*> entities = {};

	bool controlsActive;
	bool showAbout = false;
	bool showMetrics = true;
	bool showControls = false;

	void Setup(Viewer&);
	void Update(double);
	Entity* get(std::string);
	void Draw(Viewer&);
	void InitializeResources(Viewer&);
	void Inputs(Viewer&);
	void CleanUp();
	bool windowsOpen();
	void DrawUI(GLFWwindow*, ImGuiIO&, float);
	void DrawControls(bool*, ImGuiIO&);
	void DrawAbout(bool*, bool*, bool*, ImGuiIO&, GLFWwindow*);
	void DrawMetrics(bool*, double);
};
