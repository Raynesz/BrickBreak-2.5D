#include "game.h"

void Bar::Update(float deltaTime, moveControl move) {
	if (move.forward)
		position += (deltaTime * speed) * direction;
	if (move.back)
		position += (deltaTime * speed) * -direction;
	if (!move.forward && !move.back)
		position += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
	if (move.left)
		position += (deltaTime * speed) * -glm::normalize(glm::cross(direction, up));
	if (move.right)
		position += (deltaTime * speed) * glm::normalize(glm::cross(direction, up));
	if (!move.left && !move.right)
		position += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
}

//Bar::Bar(std::string name, std::string modelID, std::string shaderID, glm::vec3 translation, glm::vec3 scale, float width)
//	: Entity{ name, modelID, shaderID, std::vector<shaderStruct>&, std::vector<modelStruct>&, translation, scale }, width{ width } {}
