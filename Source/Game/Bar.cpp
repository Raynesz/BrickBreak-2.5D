#include "Game.h"

void Bar::Update(float deltaTime) {
	if (shrinkDuration > 0.0) {
		setLength(BAR_LENGTH_SHRUNK);
		shrinkDuration -= deltaTime;
	}
	else setLength(BAR_LENGTH);

	if (move.left)
		position += (deltaTime * speed) * -glm::normalize(glm::cross(direction, up));
	if (move.right)
		position += (deltaTime * speed) * glm::normalize(glm::cross(direction, up));
	if (!move.left && !move.right)
		position += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
}

Bar::Bar(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale, float length, float height, float wallXoffset, float wallWidth)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	Bar::length = length;
	Bar::height = height;
	this->Scale(length, height, this->scale.z);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	speed = 14.0f;
	border.right = wallXoffset - wallWidth;
	border.left = -wallXoffset + wallWidth;
}

void Bar::setLength(float newLength) {
	length = newLength;
	this->Scale(newLength, this->scale.y, this->scale.z);
}
