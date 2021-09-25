#pragma once

#include "Viewer.h"
#include "Bar.h"
#include "Ball.h"
#include "Brick.h"
#include "Wall.h"

class Game {
public:
	std::vector<Entity*> entities = {};

	void Setup(Viewer&);
	void Update(double);
	Entity* get(std::string);
	void Draw(Viewer&);
	void InitializeResources(Viewer&);
	void Inputs(Viewer&);
	void CleanUp();
};
