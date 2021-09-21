#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

namespace Physics {
	bool DetectCollisionAABB(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	bool DetectCollisionCircleAABB();
}

#endif
