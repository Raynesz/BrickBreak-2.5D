#pragma once

#include "Viewer.h"
#include "Bar.h"
#include "Ball.h"
#include "Brick.h"

namespace Game {
	void InitializeResources(Viewer&);
	void SetupScene(Viewer&);
	void Update(Viewer&);
	void Draw(Viewer&);
	void Inputs(Viewer&);
}
