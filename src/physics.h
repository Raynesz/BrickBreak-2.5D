#ifndef PHYSICS_H
#define PHYSICS_H

namespace Physics {
	bool DetectCollisionAABB(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	bool DetectCollisionCircleAABB();
}

#endif
