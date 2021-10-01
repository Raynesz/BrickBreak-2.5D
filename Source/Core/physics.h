#pragma once

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

namespace Physics {
	typedef std::tuple<bool, Direction, glm::vec2> Collision;

	Direction VectorDirection(glm::vec2 target);
	Collision CheckBallCollision(glm::vec3 ballPos, float ballRadius, glm::vec3 objectPos, glm::vec3 objectSize);
}
