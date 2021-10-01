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
}
