#ifndef BAR_H
#define BAR_H

#include "Entity.h"

struct moveControl {
	bool forward = false, back = false, right = false, left = false;
};

class Bar : public Entity {
public:
	float width = 1.0f;
	moveControl move;

	void Update(float, moveControl);
};

#endif
