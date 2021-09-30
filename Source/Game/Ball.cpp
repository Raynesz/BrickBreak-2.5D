#include "Game.h"

Ball::Ball(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale, float radius)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	Ball::radius = radius;
	this->Scale(radius, radius, radius);
	direction = up;
}

void Ball::Update(float deltaTime) {
	position += (deltaTime * speed) * direction;
}
