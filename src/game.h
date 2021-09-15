#ifndef GAME_H
#define GAME_H

#include "Viewer.h"

namespace Game {
	void InitializeResources(Viewer&);
	void SetupScene(Viewer&);
	void Update(Viewer&);
	void Draw(Viewer&);
}

#endif
